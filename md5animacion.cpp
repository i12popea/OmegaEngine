#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cmath>
#include <assert.h>
#include "md5animacion.hpp"

using namespace std;
using namespace ed;

namespace ed{

void EliminarSobrante( string& str )
{
	size_t n;
	while ( ( n = str.find('\"') ) != std::string::npos ) str.erase(n,1);
}

int LongitudFichero( istream& file )
{
	int pos = file.tellg();
	file.seekg(0, std::ios::end );
	int length = file.tellg();
	// Restore the position of the get pointer
	file.seekg(pos);

	return length;
}

Weight& Weight::operator = (const Weight &w)
{
	if(this != &w)
	{
		setJoint(w.getJoint());
		setBias(w.getBias());
		setPosicion(w.getPosicion());
	}
	return *this;
}

Animacion& Animacion::operator = (const Animacion &anim)
{
	if(this != &anim)
	{
		_num_frames = anim._num_frames;
		_num_joints = anim._num_joints;
		_frameRate = anim._frameRate;
		_curr_frame = anim._curr_frame;
		_next_frame = anim._next_frame;
		_last_time = anim._last_time;
		_max_time = anim._max_time;
		_jointInfo = anim._jointInfo;
		_bboxes = anim._bboxes;
		_baseFrame = anim._baseFrame;
		_frames = anim._frames;
		_skelFrames = anim._skelFrames;
		_animSkeleton = anim._animSkeleton;
		_matrizWeight = anim._matrizWeight;
		_matrizCoordAnim = anim._matrizCoordAnim;
		_matrizStart = anim._matrizStart;
		_matrizCount = anim._matrizCount;
		_matrizIndiceVertices = anim._matrizIndiceVertices;	
	}
	return *this;
}

/**
 * Build skeleton for a given frame data.
 */
void Animacion::BuildFrameSkeleton(const vector<JointInfo> &jointInfos, const vector<BaseframeJoint> &baseFrame, const FrameData &animFrameData, vector< vector<skeletonJoint> > &skelFrame)
{
	vector<skeletonJoint> skeleton;

	for ( unsigned int i = 0; i < jointInfos.size(); ++i )
	{
		unsigned int j = 0;

		const JointInfo& jointInfo = jointInfos[i];
		// Start with the base frame position and orientation.
		skeletonJoint animatedJoint = baseFrame[i];
		vector3d posicion = baseFrame[i].getPosicion();
		quaternion orientacion = baseFrame[i].getOrientacion();

		animatedJoint.setParent(jointInfo.getParent());

		if ( jointInfo.getFlags() & 1 ) // Pos.x
		{
			posicion.setX(animFrameData.getFrameData(jointInfo.getStartIndex() + j++));
			//animatedJoint._pos.setX(animFrameData.getFrameData(jointInfo.getStartIndex() + j++));
		}
		if ( jointInfo.getFlags() & 2 ) // Pos.y
		{
			posicion.setY(animFrameData.getFrameData(jointInfo.getStartIndex() + j++));
			//animatedJoint._pos.setY(animFrameData.getFrameData(jointInfo.getStartIndex() + j++));
		}
		if ( jointInfo.getFlags() & 4 ) // Pos.x
		{
			posicion.setZ(animFrameData.getFrameData(jointInfo.getStartIndex() + j++));
			//animatedJoint._pos.setZ(animFrameData.getFrameData(jointInfo.getStartIndex() + j++));
		}
		if ( jointInfo.getFlags() & 8 ) // Orient.x
		{
			orientacion.setX(animFrameData.getFrameData(jointInfo.getStartIndex() + j++));
			//animatedJoint._orient.setX(animFrameData.getFrameData(jointInfo.getStartIndex() + j++));
		}
		if ( jointInfo.getFlags() & 16 ) // Orient.y
		{
			orientacion.setY(animFrameData.getFrameData(jointInfo.getStartIndex() + j++));
			//animatedJoint._orient.setY(animFrameData.getFrameData(jointInfo.getStartIndex() + j++));
		}
		if ( jointInfo.getFlags() & 32 ) // Orient.z
		{
			orientacion.setZ(animFrameData.getFrameData(jointInfo.getStartIndex() + j++));
			//animatedJoint._orient.setZ(animFrameData.getFrameData(jointInfo.getStartIndex() + j++));
		}
		//Quat_computeW( animatedJoint.orient );
		//animatedJoint._orient.Quat_computeW();
		orientacion.Quat_computeW();
		animatedJoint.setPosicion(posicion);
		animatedJoint.setOrientacion(orientacion);

		if ( animatedJoint.getParent() >= 0 ) // Has a parent joint
		{
			skeletonJoint& parentJoint = skeleton[animatedJoint.getParent()];
			vector3d rotPos;
			//Quat_rotatePoint(parentJoint.orient, animatedJoint.pos, rotPos);
			rotPos = Quat_rotatePoint(parentJoint.getOrientacion(), animatedJoint.getPosicion());

			animatedJoint.setPosicion(parentJoint.getPosicion() + rotPos);
			//Quat_multQuat(parentJoint.orient, animatedJoint.orient, animatedJoint.orient);
			animatedJoint.setOrientacion(Quat_multQuat(parentJoint.getOrientacion(), animatedJoint.getOrientacion()));

			//Quat_normalize(animatedJoint.orient);
			//animatedJoint._orient.Quat_normalize();
			quaternion orientacion = animatedJoint.getOrientacion();
			orientacion.Quat_normalize();
			animatedJoint.setOrientacion(orientacion);
		}
		skeleton.push_back(animatedJoint);
	}

	skelFrame.push_back(vector<skeletonJoint>());
	skelFrame[skelFrame.size() - 1] = skeleton;
}

/**
 * Load an MD5 animation from file.
 */
int Animacion::ReadMD5Anim (string filename)
{
	std::string param;
	std::string junk;   // Read junk from the file

	std::ifstream file(filename.c_str());
	if(!file)
	{
		cout << "No se pudo cargar la animacion\n";
		file.close();
		return 0;
	}
	int fileLength = LongitudFichero( file );   
	assert( fileLength > 0 );

	int version;
	int numAnimatedComponents;
	int numVerts, numTris, numWeights;

	file >> param;

	while( !file.eof() )
	{
		if ( param == "MD5Version" )
		{
			file >> version;
			assert( version == 10 );
		}
		else if ( param == "commandline" )
		{
			file.ignore( fileLength, '\n' ); // Ignore everything else on the line
		}
		else if ( param == "numFrames" )
		{
			file >> _num_frames;
			file.ignore( fileLength, '\n' );
		}
		else if ( param == "numJoints" )
		{
			file >> _num_joints;
			file.ignore( fileLength, '\n' );
		}
		else if ( param == "frameRate" )
		{
			file >> _frameRate;
			file.ignore( fileLength, '\n' );
		}
		else if ( param == "numAnimatedComponents" )
		{
			file >> numAnimatedComponents;
			file.ignore( fileLength, '\n' );
		}
		else if ( param == "numverts" )
		{
			int start, count;
			string posX, posY;
			file >> numVerts;
			_matrizCoordAnim.push_back(vector<vector2d>());
			_matrizStart.push_back(vector<int>());
			_matrizCount.push_back(vector<int>());
			file.ignore( fileLength, '\n' );
			for(int i = 0; i < numVerts; i++)
			{
				file >> junk >> posX >> posY >> start >> count;
				vector2d coordenadas(strtof(posX.c_str(), NULL), strtof(posY.c_str(), NULL));
				_matrizCoordAnim[_matrizCoordAnim.size() - 1].push_back(coordenadas);
				_matrizStart[_matrizStart.size() - 1].push_back(start);
				_matrizCount[_matrizCount.size() - 1].push_back(count);
				file.ignore( fileLength, '\n' );
			}
		}
		else if ( param == "numweights" )
		{
			file >> numWeights;
			_matrizWeight.push_back(vector<Weight>());
			file.ignore( fileLength, '\n' );
			for(int i = 0; i < numWeights; i++)
			{
				Weight weight;
				int joint;
				string bias, posX, posY, posZ;
				file >> junk >> joint >> bias >> posX >> posY >> posZ;
				vector3d posicion(strtof(posX.c_str(), NULL), strtof(posY.c_str(), NULL), strtof(posZ.c_str(), NULL));
				weight.setJoint(joint); weight.setBias(strtof(bias.c_str(), NULL)); weight.setPosicion(posicion);
				_matrizWeight[_matrizWeight.size() - 1].push_back(weight);
				file.ignore( fileLength, '\n' );
			}
		}
		else if ( param == "numtris" )
		{
			file >> numTris;
			_matrizIndiceVertices.push_back(vector<int>());
			file.ignore( fileLength, '\n' );
			for(int i = 0; i < numTris; i++)
			{
				int indiceA, indiceB, indiceC;
				file >> junk >> indiceA >> indiceB >> indiceC;
				file.ignore( fileLength, '\n' );
				_matrizIndiceVertices[_matrizIndiceVertices.size() - 1].push_back(indiceA);
				_matrizIndiceVertices[_matrizIndiceVertices.size() - 1].push_back(indiceB);
				_matrizIndiceVertices[_matrizIndiceVertices.size() - 1].push_back(indiceC);
			}
		}
		else if ( param == "hierarchy" )
		{
			file >> junk; // read in the '{' character
			for ( int i = 0; i < _num_joints; ++i )
			{
				JointInfo joint;
				string nombre;
				int parent, flags, startIndex;
				file >> nombre >> parent >> flags >> startIndex;
				EliminarSobrante( nombre );
				joint.setNombre(nombre); joint.setParent(parent); joint.setFlags(flags); joint.setStartIndex(startIndex);

				_jointInfo.push_back(joint);

				file.ignore( fileLength, '\n' );
			}
			file >> junk; // read in the '}' character
		}
		else if ( param == "bounds" )
		{
			file >> junk; // read in the '{' character
			file.ignore( fileLength, '\n' );
			for ( int i = 0; i < _num_frames; ++i ) 
			{
				string minX, maxX, minY, maxY, minZ, maxZ;
				Bbox bound;
				file >> junk; // read in the '(' character
				file >> minX >> minY >> minZ;
				file >> junk >> junk; // read in the ')' and '(' characters.
				//file >> bound.m_Max.x >> bound.m_Max.y >> bound.m_Max.z;
				file >> maxX >> maxY >> maxZ;
				vector3d minimo(strtof(minX.c_str(), NULL), strtof(minY.c_str(), NULL), strtof(minZ.c_str(), NULL));
				vector3d maximo(strtof(maxX.c_str(), NULL), strtof(maxY.c_str(), NULL), strtof(maxZ.c_str(), NULL));
				//bound._min.setX(strtof(minX.c_str(), NULL)); bound._min.setY(strtof(minY.c_str(), NULL)); bound._min.setZ(strtof(minZ.c_str(), NULL));
				//bound._max.setX(strtof(maxX.c_str(), NULL)); bound._max.setY(strtof(maxY.c_str(), NULL)); bound._max.setZ(strtof(maxZ.c_str(), NULL));
				bound.setVectorMin(minimo);
				bound.setVectorMax(maximo);
		        
				_bboxes.push_back(bound);

				file.ignore( fileLength, '\n' );
			}

			file >> junk; // read in the '}' character
			file.ignore( fileLength, '\n' );
		}
		else if ( param == "baseframe" )
		{
			file >> junk; // read in the '{' character
			file.ignore( fileLength, '\n' );

			for ( int i = 0; i < _num_joints; ++i )
			{
				string posX, posY, posZ, orientX, orientY, orientZ;
				BaseframeJoint BaseFrame;
				file >> junk;
				//file >> baseFrame.m_Pos.x >> baseFrame.m_Pos.y >> baseFrame.m_Pos.z;
				file >> posX >> posY >> posZ;
				file >> junk >> junk;
				//file >> baseFrame.m_Orient.x >> baseFrame.m_Orient.y >> baseFrame.m_Orient.z;
				file >> orientX >> orientY >> orientZ;

				file.ignore( fileLength, '\n' );
				vector3d posicion(strtof(posX.c_str(), NULL), strtof(posY.c_str(), NULL), strtof(posZ.c_str(), NULL));
				quaternion orientacion(strtof(orientX.c_str(), NULL), strtof(orientY.c_str(), NULL), strtof(orientZ.c_str(), NULL));
				//BaseFrame._pos.setX(strtof(posX.c_str(), NULL)); BaseFrame._pos.setY(strtof(posY.c_str(), NULL)); BaseFrame._pos.setZ(strtof(posZ.c_str(), NULL));
				//BaseFrame._orient.setX(strtof(orientX.c_str(), NULL)); BaseFrame._orient.setY(strtof(orientY.c_str(), NULL)); BaseFrame._orient.setZ(strtof(orientZ.c_str(), NULL));
				BaseFrame.setPosicion(posicion);
				BaseFrame.setOrientacion(orientacion);

				_baseFrame.push_back(BaseFrame);
			}
			file >> junk; // read in the '}' character
			file.ignore( fileLength, '\n' );
		}
		else if ( param == "frame" )
		{
			FrameData frame;
			int id;
			vector<float> vectorFrameData;
			file >> id >> junk; // Read in the '{' character
			frame.setId(id);
			file.ignore(fileLength, '\n' );

			for ( int i = 0; i < numAnimatedComponents; ++i )
			{
				float frameData;
				file >> frameData;
				vectorFrameData.push_back(frameData);
			}
			frame.setFrameData(vectorFrameData);

			_frames.push_back(frame);

			// Build a skeleton for this frame
			BuildFrameSkeleton( _jointInfo, _baseFrame, frame, _skelFrames );

			file >> junk; // Read in the '}' character
			file.ignore(fileLength, '\n' );        
		}

		file >> param;
	}

	// Make sure there are enough joints for the animated skeleton.
	_animSkeleton.assign(_num_joints, skeletonJoint() );

	//FrameDuration = 1.0f / (float)frameRate;
	//AnimDuration = ( FrameDuration * (float)num_frames );
	//AnimTime = 0.0f;
	_curr_frame = 0;
	_next_frame = 1;
	_last_time = 0.0f;
	_max_time = 1.0f / (float)_frameRate;

	file.close();

	return 1;
}

/**
 * Smoothly interpolate two skeletons
 */
void Animacion::InterpolateSkeletons(vector<skeletonJoint> &out, const vector<skeletonJoint> &skelA, const vector<skeletonJoint> &skelB, float interp)
{
	int i;
	for (i = 0; i < _num_joints; ++i)
	{
		vector3d posicion;
		quaternion orientacion;
		/* Copy parent index */
		out[i].setParent(skelA[i].getParent());

		/* Linear interpolation for position */
		/*out[i]._pos.setX(skelA[i]._pos.getX() + interp * (skelB[i]._pos.getX() - skelA[i]._pos.getX()));
		out[i]._pos.setY(skelA[i]._pos.getY() + interp * (skelB[i]._pos.getY() - skelA[i]._pos.getY()));
		out[i]._pos.setZ(skelA[i]._pos.getZ() + interp * (skelB[i]._pos.getZ() - skelA[i]._pos.getZ()));*/
		posicion.setX(skelA[i].getPosicion().getX() + interp * (skelB[i].getPosicion().getX() - skelA[i].getPosicion().getX()));
		posicion.setY(skelA[i].getPosicion().getY() + interp * (skelB[i].getPosicion().getY() - skelA[i].getPosicion().getY()));
		posicion.setZ(skelA[i].getPosicion().getZ() + interp * (skelB[i].getPosicion().getZ() - skelA[i].getPosicion().getZ()));
		out[i].setPosicion(posicion);

		/* Spherical linear interpolation for orientation */
		Quat_slerp (skelA[i].getOrientacion(), skelB[i].getOrientacion(), interp, orientacion);
		out[i].setOrientacion(orientacion);
	}
}

/**
 * Perform animation related computations.  Calculate the current and
 * next frames, given a delta time.
 */
void Animacion::Animate(float dt)
{
	int maxFrames = _num_frames - 1;

	_last_time += dt;

	// move to next frame
	if (_last_time >= _max_time)
	{
		_curr_frame++;
		_next_frame++;
		_last_time = 0.0;

		if (_curr_frame > maxFrames)
			_curr_frame = 0;

		if (_next_frame > maxFrames)
			_next_frame = 0;
	}
	//float fInterpolate = fmodf( last_time, max_time ) / max_time;
	float fInterpolate = _last_time*_frameRate;
	InterpolateSkeletons(_animSkeleton, _skelFrames[_curr_frame], _skelFrames[_next_frame], fInterpolate);

	/*if ( num_frames < 1 ) return;

	AnimTime += dt;

	while ( AnimTime > AnimDuration ) AnimTime -= AnimDuration;
	while ( AnimTime < 0.0f ) AnimTime += AnimDuration;

	// Figure out which frame we're on
	float fFramNum = AnimTime * (float)frameRate;
	int iFrame0 = (int)floorf( fFramNum );
	int iFrame1 = (int)ceilf( fFramNum );
	iFrame0 = iFrame0 % num_frames;
	iFrame1 = iFrame1 % num_frames;

	float fInterpolate = fmodf( AnimTime, FrameDuration ) / FrameDuration;

	InterpolateSkeletons(animSkeleton, skelFrames[iFrame0], skelFrames[iFrame1], fInterpolate);*/
}

void Animacion::Render()
{
	glPointSize( 5.0f );
	glColor3f( 1.0f, 0.0f, 0.0f );

	glPushAttrib( GL_ENABLE_BIT );

	glDisable(GL_LIGHTING );
	glDisable( GL_DEPTH_TEST );

	const vector<skeletonJoint>& joints = _animSkeleton;

	// Draw the joint positions
	glBegin( GL_POINTS );
	{
		float radian = 3.1415926535897932/180;
		float posRotY, posRotZ;
		for ( unsigned int i = 0; i < joints.size(); ++i )
		{
			//glVertex3fv( glm::value_ptr(joints[i].m_Pos) );
			posRotY = joints[i].getPosicion().getY()*cos(-90*radian) - joints[i].getPosicion().getZ()*sin(-90*radian);
			posRotZ = joints[i].getPosicion().getY()*sin(-90*radian) + joints[i].getPosicion().getZ()*cos(-90*radian);
			//glVertex3f(joints[i].pos.getX(), joints[i].pos.getY(), joints[i].pos.getZ());
			glVertex3f(joints[i].getPosicion().getX(), posRotY, posRotZ);
		}
	}
	glEnd();

	// Draw the bones
	glColor3f( 0.0f, 1.0f, 0.0f );
	glBegin( GL_LINES );
	{
		float radian = 3.1415926535897932/180;
		float posRotY, posRotZ;
		for( unsigned int i = 0; i < joints.size(); ++i )
		{
			const skeletonJoint& j0 = joints[i];
			if ( j0.getParent() != -1 )
			{
				const skeletonJoint& j1 = joints[j0.getParent()];
				//glVertex3fv( glm::value_ptr(j0.m_Pos) );
				//glVertex3fv( glm::value_ptr(j1.m_Pos) );
				posRotY = j0.getPosicion().getY()*cos(-90*radian) - j0.getPosicion().getZ()*sin(-90*radian);
				posRotZ = j0.getPosicion().getY()*sin(-90*radian) + j0.getPosicion().getZ()*cos(-90*radian);
				//glVertex3f(j0.pos.getX(), j0.pos.getY(), j0.pos.getZ());
				//glVertex3f(j1.pos.getX(), j1.pos.getY(), j1.pos.getZ());
				glVertex3f(j0.getPosicion().getX(), posRotY, posRotZ);
				posRotY = j1.getPosicion().getY()*cos(-90*radian) - j1.getPosicion().getZ()*sin(-90*radian);
				posRotZ = j1.getPosicion().getY()*sin(-90*radian) + j1.getPosicion().getZ()*cos(-90*radian);
				glVertex3f(j1.getPosicion().getX(), posRotY, posRotZ);
			}
		}
	}
	glEnd();

	glPopAttrib();
}

}
