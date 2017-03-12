#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cmath>
#include "md5modelo.hpp"

using namespace std;
using namespace ed;

namespace ed{

void RemoveQuotes( string& str )
{
    size_t n;
    while ( ( n = str.find('\"') ) != std::string::npos ) str.erase(n,1);
}

int GetFileLength( istream& file )
{
    int pos = file.tellg();
    file.seekg(0, std::ios::end );
    int length = file.tellg();
    // Restore the position of the get pointer
    file.seekg(pos);

    return length;
}

/**
 * Load an MD5 model from file.
 */
int md5_model_t::ReadMD5Model(string filename)
{
    string param;
    string junk;   // Read junk from the file
	int version;

    ifstream file(filename.c_str()/*, ios_base::in | ios_base::binary*/);
    int fileLength = GetFileLength( file );   
    assert( fileLength > 0 );

    //m_Joints.clear();
    //m_Meshes.clear();
    
    file >> param;

    while ( !file.eof() )
    {
        if ( param == "MD5Version" )
        {
            file >> version;
            assert( version == 10 );
//		cout << "Version: " << version << endl;
        }
        else if ( param == "commandline" )
        {
            //IgnoreLine(file, fileLength ); // Ignore the contents of the line
	    file.ignore(fileLength, '\n' );
        }
        else if ( param == "numJoints" )
        {
            file >> num_joints;
            baseSkel.reserve(num_joints);
//		cout << "Num Joints: " << num_joints << endl;
        }
        else if ( param == "numMeshes" )
        {
            file >> num_meshes;
            meshes.reserve(num_meshes);
//		cout << "Num Meshes: " << num_meshes << endl;
        }
        else if ( param == "joints" )
        {
            md5_joint_t joint;
            file >> junk; // Read the '{' character

            for ( int i = 0; i < num_joints; ++i )
            {
		string parent, posX, posY, posZ, orientX, orientY, orientZ;
//		float posRotX, posRotY, posRotZ, orientRotX, orientRotY, orientRotZ;
                file >> joint.name >> joint.parent >> junk
                     //>> joint.m_Pos.x >> joint.m_Pos.y >> joint.m_Pos.z >> junk >> junk
                     //>> joint.m_Orient.x >> joint.m_Orient.y >> joint.m_Orient.z >> junk;
                     >> posX >> posY >> posZ >> junk >> junk
                     >> orientX >> orientY >> orientZ >> junk;
		//joint.parent = strtof(parent.c_str(), NULL);
		/*posRotX = strtof(posX.c_str(), NULL); posRotY = strtof(posY.c_str(), NULL)*cos(-90) - strtof(posZ.c_str(), NULL)*sin(-90); posRotZ = strtof(posY.c_str(), NULL)*sin(-90) + strtof(posZ.c_str(), NULL)*cos(-90);
		orientRotX = strtof(orientX.c_str(), NULL); orientRotY = strtof(orientY.c_str(), NULL)*cos(-90) - strtof(orientZ.c_str(), NULL)*sin(-90); orientRotZ = strtof(orientY.c_str(), NULL)*sin(-90) + strtof(orientZ.c_str(), NULL)*cos(-90);
		joint.pos.setX(posRotX); joint.pos.setY(posRotY); joint.pos.setZ(posRotZ);
		joint.orient.setX(orientRotX); joint.orient.setY(orientRotY); joint.orient.setZ(orientRotZ);*/
		joint.pos.setX(strtof(posX.c_str(), NULL)); joint.pos.setY(strtof(posY.c_str(), NULL)); joint.pos.setZ(strtof(posZ.c_str(), NULL));
		joint.orient.setX(strtof(orientX.c_str(), NULL)); joint.orient.setY(strtof(orientY.c_str(), NULL)); joint.orient.setZ(strtof(orientZ.c_str(), NULL));
                
                RemoveQuotes( joint.name );
                //Quat_computeW( joint.orient );
                joint.orient.Quat_computeW();
//		cout << "Joints: " << joint.name << ", " << joint.parent << ", X: " << joint.pos.getX() << ", Y: " << joint.pos.getY() << ", Z: " << joint.pos.getZ() << ", X: " << joint.orient.getX() << ", Y: " << joint.orient.getY() << ", Z: " << joint.orient.getZ() << endl;

                baseSkel.push_back(joint);
                // Ignore everything else on the line up to the end-of-line character.
                //IgnoreLine( file, fileLength );
		file.ignore(fileLength, '\n' );
            }
            file >> junk; // Read the '}' character
        }
        else if ( param == "mesh" )
        {
            md5_mesh_t mesh;
            int numVerts, numTris, numWeights;

            file >> junk; // Read the '{' character
            file >> param;
            while ( param != "}" )  // Read until we get to the '}' character
            {
                if ( param == "shader" )
                {
                    file >> mesh.shader;
                    RemoveQuotes( mesh.shader );
		//cout << "Shader: " << mesh.shader << endl;

			mesh.idTexture = LoadBitmap(mesh.shader);

		    file.ignore(fileLength, '\n' );
                }
                else if ( param == "numverts")
                {
                    file >> numVerts;               // Read in the vertices
                    //IgnoreLine(file, fileLength);
		    file.ignore(fileLength, '\n' );
                    for ( int i = 0; i < numVerts; ++i )
                    {
                        md5_vertex_t vert;
			string posX, posY;//, start, count;

                        file >> junk >> junk >> junk                    // vert vertIndex (
                            //>> vert.m_Tex0.x >> vert.m_Tex0.y >> junk  //  s t )
                            >> posX >> posY >> junk  //  s t )
                            >> vert.start >> vert.count;
			vert.st.setU(strtof(posX.c_str(), NULL)); vert.st.setV(1 - strtof(posY.c_str(), NULL));
			//vert.start = atoi(start.c_str());
			//vert.count = atoi(count.c_str());
//			cout << "Vertices: X: " << vert.st.getU() << ", Y: " << vert.st.getV() << ", " << vert.start << ", " << vert.count << endl;

                        //IgnoreLine(file, fileLength);
			file.ignore(fileLength, '\n' );

                        mesh.vertices.push_back(vert);
                        mesh.textureArray.push_back(vert.st);
                    }
                }
                else if ( param == "numtris" )
                {
                    file >> numTris;
                    //IgnoreLine(file, fileLength);
		    file.ignore(fileLength, '\n' );
                    for ( int i = 0; i < numTris; ++i )
                    {
                        md5_triangle_t tri;
                        file >> junk >> junk >> tri.index[0] >> tri.index[1] >> tri.index[2];

//			cout << "Triangulos: " << tri.index[0] << ", " << tri.index[1] << ", " << tri.index[2] << endl;

                        //IgnoreLine( file, fileLength );
			file.ignore(fileLength, '\n' );

                        mesh.triangles.push_back(tri);
                        mesh.vertexIndices.push_back( (GLuint)tri.index[0] );
                        mesh.vertexIndices.push_back( (GLuint)tri.index[1] );
                        mesh.vertexIndices.push_back( (GLuint)tri.index[2] );
                    }              
                }
                else if ( param == "numweights" )
                {
                    file >> numWeights;
                    //IgnoreLine( file, fileLength );
		    file.ignore(fileLength, '\n' );
                    for ( int i = 0; i < numWeights; ++i )
                    {
			string bias, posX, posY, posZ;
//			float posRotX, posRotY, posRotZ;
                        md5_weight_t weight;
                        file >> junk >> junk >> weight.joint >> bias >> junk
                            //>> weight.m_Pos.x >> weight.m_Pos.y >> weight.m_Pos.z >> junk;
                            >> posX >> posY >> posZ >> junk;
			weight.bias = strtof(bias.c_str(), NULL);
//			posRotX = strtof(posX.c_str(), NULL); posRotY = strtof(posY.c_str(), NULL)*cos(-90) - strtof(posZ.c_str(), NULL)*sin(-90); posRotZ = strtof(posY.c_str(), NULL)*sin(-90) + strtof(posZ.c_str(), NULL)*cos(-90);
			weight.pos.setX(strtof(posX.c_str(), NULL)); weight.pos.setY(strtof(posY.c_str(), NULL)); weight.pos.setZ(strtof(posZ.c_str(), NULL));
//			weight.pos.setX(posRotX); weight.pos.setY(posRotY); weight.pos.setZ(posRotZ);

//			cout << "Joints: " << weight.joint << ", " << weight.bias << ", X: " << weight.pos.getX() << ", Y: " << weight.pos.getY() << ", Z: " << weight.pos.getZ() << endl;

                        //IgnoreLine( file, fileLength );
			file.ignore(fileLength, '\n' );
                        mesh.weights.push_back(weight);
                    }
                }
                else
                {
                    //IgnoreLine(file, fileLength);
		    file.ignore(fileLength, '\n' );
                }
            
                file >> param;
            }

            PrepareMesh(mesh);
            PrepareNormals(mesh);

            meshes.push_back(mesh);
        }

        file >> param;
    }
	file.close();

    assert( baseSkel.size() == (unsigned int)num_joints );
    assert( meshes.size() == (unsigned int)num_meshes );

  return 1;
}

/**
 * Check if an animation can be used for a given model.  Model's
 * skeleton and animation's skeleton must match.
 */
bool md5_model_t::CheckAnimValidity (const Animacion &animation)
{
	if ( num_joints != animation.getNumJoints() )
	{
		return false;
	}

	// Check to make sure the joints match up
	for ( unsigned int i = 0; i < baseSkel.size(); ++i )
	{
		const md5_joint_t& meshJoint = baseSkel[i];
		const /*md5_anim_t::*/JointInfo& animJoint = animation.getJointInfo(i);

		if ( meshJoint.name != animJoint.getNombre() || meshJoint.parent != animJoint.getParent() )
		{
			return false;
		}
	}

	return true;
}

void md5_model_t::PrepareMesh(md5_mesh_t &mesh)
{
    mesh.vertexArray.clear();
    mesh.textureArray.clear();
	float radian = 3.1415926535897932/180;

    // Compute vertex positions
    for ( unsigned int i = 0; i < mesh.vertices.size(); ++i )
    {
        vector3d finalPos(0, 0, 0);
        md5_vertex_t& vert = mesh.vertices[i];
 
        //vert.pos = vector3d(0, 0, 0);
 
        // Sum the position of the weights
        for ( int j = 0; j < mesh.vertices[i].count; ++j )
        {
            md5_weight_t& weight = mesh.weights[vert.start + j];
            md5_joint_t& joint = baseSkel[weight.joint];
 
            // Convert the weight position from Joint local space to object space
            //vector3d rotPos = joint.orient * weight.pos;

            vector3d rotPos;
            //Quat_rotatePoint(joint.orient, weight.pos, rotPos);
            rotPos = Quat_rotatePoint(joint.orient, weight.pos);
 
            //vert.pos += ( joint.pos + rotPos ) * weight.bias;
            //vert.pos = vert.pos + ( joint.pos + rotPos ) * weight.bias;
            finalPos = finalPos + ( ( joint.pos + rotPos ) * weight.bias);
        }
	finalPos.setY(finalPos.getY()*cos(-90*radian) - finalPos.getZ()*sin(-90*radian));
	finalPos.setZ(finalPos.getY()*sin(-90*radian) + finalPos.getZ()*cos(-90*radian));
 
        mesh.vertexArray.push_back(finalPos);
        mesh.textureArray.push_back(vert.st);
    }
	for(unsigned int i = 0; i < mesh.vertexIndices.size() ; ++i)
	{
		mesh.verticeArray.push_back(mesh.vertexArray[mesh.vertexIndices[i]]);
		mesh.texturaArray.push_back(mesh.textureArray[mesh.vertexIndices[i]]);
	}
	/*for(unsigned int i = 0; i < mesh.vertexArray.size() ; i = i + 3)
	{
		mesh.verticeArray.push_back(mesh.vertexArray[mesh.vertexIndices[i]]);
		mesh.verticeArray.push_back(mesh.vertexArray[mesh.vertexIndices[i+1]]);
		mesh.verticeArray.push_back(mesh.vertexArray[mesh.vertexIndices[i+2]]);
	}*/
}

/**
 * Prepare a mesh for drawing.  Compute mesh's final vertex positions
 * given a skeleton.  Put the vertices in vertex arrays.
 */
void md5_model_t::PrepareMesh(md5_mesh_t &mesh, const vector<skeletonJoint> &skeleton)
{
	float radian = 3.1415926535897932/180;
    vector<vector3d> vectorPuntos;
    for ( unsigned int i = 0; i < mesh.vertices.size(); ++i )
    {
        const md5_vertex_t& vert = mesh.vertices[i];
        //vector3d& posicion = mesh.vertexArray[i];
        vector3d& normal = mesh.normalArray[i];

        vector3d posicion = vector3d(0, 0, 0);
        normal = vector3d(0, 0, 0);

        for ( int j = 0; j < vert.count; ++j )
        {
            md5_weight_t& weight = mesh.weights[vert.start + j];
            skeletonJoint joint = skeleton[weight.joint];

            //vector3d rotPos = joint.orient * weight.pos;
            vector3d rotPos;
            //Quat_rotatePoint (joint.orient, weight.pos, rotPos);
            rotPos = Quat_rotatePoint (joint.getOrientacion(), weight.pos);

            posicion = posicion + ( joint.getPosicion() + rotPos ) * weight.bias;

            normal = normal + ( Quat_rotatePoint(joint.getOrientacion(), vert.normal) ) * weight.bias;
        }
	posicion.setY(posicion.getY()*cos(-90*radian) - posicion.getZ()*sin(-90*radian));
	posicion.setZ(posicion.getY()*sin(-90*radian) + posicion.getZ()*cos(-90*radian));
        vectorPuntos.push_back(posicion);
    }

    vector<vector3d> &posiciones = mesh.vertexArray;
    posiciones = vectorPuntos;

	for(unsigned int i = 0; i < mesh.vertexIndices.size(); ++i)
	{
		mesh.verticeArray[i] = vectorPuntos[mesh.vertexIndices[i]];
	}
}

void md5_model_t::PrepareNormals(md5_mesh_t &mesh)
{
    mesh.normalArray.clear();

    // Loop through all triangles and calculate the normal of each triangle
    for ( unsigned int i = 0; i < mesh.triangles.size(); ++i )
    {
        vector3d v0 = mesh.vertices[ mesh.triangles[i].index[0] ].pos;
        vector3d v1 = mesh.vertices[ mesh.triangles[i].index[1] ].pos;
        vector3d v2 = mesh.vertices[ mesh.triangles[i].index[2] ].pos;

        vector3d normal = productoVectorial( v2 - v0, v1 - v0 );

        //mesh.vertices[ mesh.triangles[i].index[0] ].normal += normal;
        //mesh.vertices[ mesh.triangles[i].index[1] ].normal += normal;
        //mesh.vertices[ mesh.triangles[i].index[2] ].normal += normal;
        mesh.vertices[ mesh.triangles[i].index[0] ].normal = mesh.vertices[ mesh.triangles[i].index[0] ].normal + normal;
        mesh.vertices[ mesh.triangles[i].index[1] ].normal = mesh.vertices[ mesh.triangles[i].index[1] ].normal + normal;
        mesh.vertices[ mesh.triangles[i].index[2] ].normal = mesh.vertices[ mesh.triangles[i].index[2] ].normal + normal;
    }

    // Now normalize all the normals
    for ( unsigned int i = 0; i < mesh.vertices.size(); ++i )
    {
        md5_vertex_t vert = mesh.vertices[i];

        vector3d normal = normalizarVector( vert.normal );
        mesh.normalArray.push_back( normal );

        // Reset the normal to calculate the bind-pose normal in joint space
        vert.normal = vector3d(0, 0, 0);

        // Put the bind-pose normal into joint-local space
        // so the animated normal can be computed faster later
        for ( int j = 0; j < vert.count; ++j )
        {
            const md5_weight_t weight = mesh.weights[vert.start + j];
            const md5_joint_t joint = baseSkel[weight.joint];
            vert.normal = vert.normal + ( Quat_rotatePoint(joint.orient, normal) ) * weight.bias;
        }
    }
}

void md5_model_t::Render()
{
	glPushMatrix();

	for( unsigned int i = 0; i < meshes.size(); ++i )
	{
		//cout << "Iteracion " << i << endl;
		RenderMesh( meshes[i] );
	}

	//animacion.Render();

	glPopMatrix();
}

void md5_model_t::RenderMesh(const md5_mesh_t & mesh)
{
/*ofstream flujo;
flujo.open("datos.txt");
	float posRotX, posRotY, posRotZ;
for(unsigned int i = 0; i < mesh.verticeArray.size(); i++)
{
	float radian = 3.1415926535897932/180;
	//posRotX = mesh.verticeArray[i].getX();
	//posRotY = mesh.verticeArray[i].getY();
	//posRotZ = mesh.verticeArray[i].getZ();
	posRotX = mesh.verticeArray[i].getX();
	posRotY = mesh.verticeArray[i].getY()*cos(-90*radian) - mesh.verticeArray[i].getZ()*sin(-90*radian);
	posRotZ = mesh.verticeArray[i].getY()*sin(-90*radian) + mesh.verticeArray[i].getZ()*cos(-90*radian);

	flujo << "Vert: X: " << posRotX << ", Y: " << posRotY << ", Z: " << posRotZ << ", Coord: X: " << mesh.texturaArray[i].getU() << "Y: " << mesh.texturaArray[i].getV() << endl;
}
flujo.close();*/
	glColor3f( 1.0f, 1.0f, 1.0f );
	glEnable(GL_TEXTURE_2D);

	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glEnableClientState( GL_NORMAL_ARRAY );

	glBindTexture( GL_TEXTURE_2D, mesh.idTexture );
	glVertexPointer( 3, GL_FLOAT, sizeof(vector3d), &mesh.vertexArray[0] );
	//glVertexPointer( 3, GL_FLOAT, sizeof(vector3d), &mesh.verticeArray[0] );
	glNormalPointer( GL_FLOAT, sizeof(vector3d), &mesh.normalArray[0] );
	glTexCoordPointer( 2, GL_FLOAT, sizeof(vector2d), &mesh.textureArray[0] );
	//glTexCoordPointer( 2, GL_FLOAT, sizeof(vector2d), &mesh.texturaArray[0] );

	glDrawElements( GL_TRIANGLES, mesh.vertexIndices.size(), GL_UNSIGNED_INT, &mesh.vertexIndices[0] );
	//glDrawArrays(GL_TRIANGLES, 0, mesh.verticeArray.size());

	glDisableClientState( GL_NORMAL_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	glDisableClientState( GL_VERTEX_ARRAY );
	glBindTexture( GL_TEXTURE_2D, 0 );
	glDisable(GL_TEXTURE_2D);
}

/**
 * Draw the skeleton as lines and points (for joints).
 */
void md5_model_t::DrawSkeleton (const vector<md5_joint_t> &skeleton)
{
  unsigned int i;

  /* Draw each joint */
  glPointSize (5.0f);
  glColor3f (1.0f, 0.0f, 0.0f);
  glBegin (GL_POINTS);
    for (i = 0; i < skeleton.size(); ++i)
      //glVertex3fv (skeleton[i].pos);
      glVertex3f(skeleton[i].pos.getX(), skeleton[i].pos.getY(), skeleton[i].pos.getZ());
  glEnd ();
  glPointSize (1.0f);

  /* Draw each bone */
  glColor3f (0.0f, 1.0f, 0.0f);
  glBegin (GL_LINES);
    for (i = 0; i < skeleton.size(); ++i)
      {
	if (skeleton[i].parent != -1)
	  {
	    //glVertex3fv (skeleton[skeleton[i].parent].pos);
	    //glVertex3fv (skeleton[i].pos);
	    glVertex3f(skeleton[skeleton[i].parent].pos.getX(), skeleton[skeleton[i].parent].pos.getY(), skeleton[skeleton[i].parent].pos.getZ());
	    glVertex3f(skeleton[i].pos.getX(), skeleton[i].pos.getY(), skeleton[i].pos.getZ());
	  }
      }
  glEnd();
}

void md5_model_t::Update(float time)
{
	animacion.Animate(time);
	const vector<skeletonJoint> frameSkeleton = animacion.getAnimSkeleton();

	for(unsigned int i = 0; i < meshes.size(); i++)
		PrepareMesh(meshes[i], frameSkeleton);
}

}
