#ifndef __MD5ANIMACION_HPP__
#define __MD5ANIMACION_HPP__

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cmath>
#include <cstring>
#include <assert.h>
#include <vector>
#include <fstream>
#include "quaternion.hpp"

using namespace std;
using std::vector;
using std::string;

namespace ed{

/* Bounding box */
class Bbox//md5_bbox_t
{
private:
	vector3d _min;
	vector3d _max;
public:
	inline vector3d getVectorMin() const
	{
		return _min;
	}
	inline vector3d getVectorMax() const
	{
		return _max;
	}
	inline void setVectorMin(vector3d min)
	{
		_min = min;
	}
	inline void setVectorMax(vector3d max)
	{
		_max = max;
	}

	Bbox& operator = (const Bbox& box)
	{
		_min = box._min;
		_max = box._max;
		return *this;
	}
};

class FrameData//frame_data_t
{
private:
	int _id;
	vector<float> _frameData;
public:
	inline int getId() const
	{
		return _id;
	}
	inline vector<float> getFrameData() const
	{
		return _frameData;
	}
	inline float getFrameData(int indice) const
	{
		return _frameData[indice];
	}
	inline void setId(int id)
	{
		_id = id;
	}
	inline void setFrameData(vector<float> frameData)
	{
		_frameData = frameData;
	}

	FrameData& operator = (const FrameData& data)
	{
		_id = data._id;
		_frameData = data._frameData;
		return *this;
	}
};

/* Joint info */
class JointInfo//joint_info_t
{
private:
	string _name;
	int _parent;
	int _flags;
	int _startIndex;
public:
	inline string getNombre() const
	{
		return _name;
	}
	inline int getParent() const
	{
		return _parent;
	}
	inline int getFlags() const
	{
		return _flags;
	}
	inline int getStartIndex() const
	{
		return _startIndex;
	}
	inline void setNombre(string nombre)
	{
		_name = nombre;
	}
	inline void setParent(int parent)
	{
		_parent = parent;
	}
	inline void setFlags(int flags)
	{
		_flags = flags;
	}
	inline void setStartIndex(int startIndex)
	{
		_startIndex = startIndex;
	}

	JointInfo& operator = (const JointInfo& info)
	{
		_name = info._name;
		_parent = info._parent;
		_flags = info._flags;
		_startIndex = info._startIndex;
		return *this;
	}
};

/* Base frame joint */
class BaseframeJoint//baseframe_joint_t
{
private:
	vector3d _pos;
	quaternion _orient;
public:
	inline vector3d getPosicion() const
	{
		return _pos;
	}
	inline quaternion getOrientacion() const
	{
		return _orient;
	}
	inline void setPosicion(vector3d pos)
	{
		_pos = pos;
	}
	inline void setOrientacion(quaternion orient)
	{
		_orient = orient;
	}

	BaseframeJoint& operator = (const BaseframeJoint& frame)
	{
		_pos = frame._pos;
		_orient = frame._orient;
		return *this;
	}
};

/* Animation info */
class skeletonJoint
{
private:
	int _parent;
	vector3d _pos;
	quaternion _orient;
public:
	inline int getParent() const
	{
		return _parent;
	}
	inline vector3d getPosicion() const
	{
		return _pos;
	}
	inline quaternion getOrientacion() const
	{
		return _orient;
	}
	inline void setParent(int parent)
	{
		_parent = parent;
	}
	inline void setPosicion(vector3d pos)
	{
		_pos = pos;
	}
	inline void setOrientacion(quaternion orient)
	{
		_orient = orient;
	}

	skeletonJoint()
	{
		_parent = -1;
		_pos = vector3d(0, 0, 0);
	}

	skeletonJoint& operator = (const skeletonJoint& skel)
	{
		_parent = skel._parent;
		_pos = skel._pos;
		_orient = skel._orient;
		return *this;
	}

	skeletonJoint( const BaseframeJoint& copy ): _pos( copy.getPosicion() ), _orient( copy.getOrientacion() )
        {}
};

class Weight
{
private:
	int _joint;
	float _bias;
	vector3d _posicion;
public:
	inline void setJoint(int joint)
	{
		_joint = joint;
	}
	inline void setBias(float bias)
	{
		_bias = bias;
	}
	inline void setPosicion(vector3d posicion)
	{
		_posicion = posicion;
	}

	inline int getJoint() const
	{
		return _joint;
	}
	inline float getBias() const
	{
		return _bias;
	}
	inline vector3d getPosicion() const
	{
		return _posicion;
	}

	Weight& operator = (const Weight &w);
};

/* Animation data */
class Animacion//md5_anim_t
{
private:
	int _num_frames;
	int _num_joints;
	int _frameRate;

	int _curr_frame;
	int _next_frame;
	float _last_time;	//Equivale a AnimTime
	float _max_time;	//Equivale a FrameDuration
	/*float AnimDuration;
	float FrameDuration;
	float AnimTime;*/

	vector<JointInfo> _jointInfo;
	vector<Bbox> _bboxes;
	vector<BaseframeJoint> _baseFrame;
	vector<FrameData> _frames;
	vector< vector<skeletonJoint> > _skelFrames;
	vector<skeletonJoint> _animSkeleton;

	vector< vector<Weight> > _matrizWeight;
	vector< vector<vector2d> > _matrizCoordAnim;
	vector< vector<int> > _matrizStart;
	vector< vector<int> > _matrizCount;
	vector< vector<int> > _matrizIndiceVertices;
public:
	inline int getNumFrames() const
	{
		return _num_frames;
	}
	inline int getNumJoints() const
	{
		return _num_joints;
	}
	inline int getFrameRate() const
	{
		return _frameRate;
	}
	inline int getCurrFrame() const
	{
		return _curr_frame;
	}
	inline int getNextFrame() const
	{
		return _next_frame;
	}
	inline int getLastTime() const
	{
		return _last_time;
	}
	inline int getMaxTime() const
	{
		return _max_time;
	}
	inline vector<JointInfo> getJointInfo() const
	{
		return _jointInfo;
	}
	inline JointInfo getJointInfo(int indice) const
	{
		return _jointInfo[indice];
	}
	inline vector<Bbox> getBoxes() const
	{
		return _bboxes;
	}
	inline vector<BaseframeJoint> getBaseFrame() const
	{
		return _baseFrame;
	}
	inline vector<FrameData> getFrames() const
	{
		return _frames;
	}
	inline vector< vector<skeletonJoint> > getSkelFrames() const
	{
		return _skelFrames;
	}
	inline vector<skeletonJoint> getAnimSkeleton() const
	{
		return _animSkeleton;
	}
	inline vector< vector<Weight> > getMatrizWeight() const
	{
		return _matrizWeight;
	}
	inline vector<Weight> getVectorWeight(int indice) const
	{
		return _matrizWeight[indice];
	}
	inline vector< vector<vector2d> > getMatrizCoordAnim() const
	{
		return _matrizCoordAnim;
	}
	inline vector<vector2d> getVectorCoordAnim(int indice) const
	{
		return _matrizCoordAnim[indice];
	}
	inline vector< vector<int> > getMatrizStart() const
	{
		return _matrizStart;
	}
	inline vector<int> getVectorStart(int indice) const
	{
		return _matrizStart[indice];
	}
	inline vector< vector<int> > getMatrizCount() const
	{
		return _matrizCount;
	}
	inline vector<int> getVectorCount(int indice) const
	{
		return _matrizCount[indice];
	}
	inline vector< vector<int> > getIndiceVertices() const
	{
		return _matrizIndiceVertices;
	}
	inline vector<int> getVectorIndiceVertices(int indice) const
	{
		return _matrizIndiceVertices[indice];
	}

	inline void setNumFrames(int num_frames)
	{
		_num_frames = num_frames;
	}
	inline void setNumJoints(int num_joints)
	{
		_num_joints = num_joints;
	}
	inline void setFrameRate(int frameRate)
	{
		_frameRate = frameRate;
	}
	inline void setCurrFrame(int curr_frame)
	{
		_curr_frame = curr_frame;
	}
	inline void setNextFrame(int next_frame)
	{
		_next_frame = next_frame;
	}
	inline void setLastTime(int last_time)
	{
		_last_time = last_time;
	}
	inline void setMaxTime(int max_time)
	{
		_max_time = max_time;
	}
	inline void setJointInfo(vector<JointInfo> jointInfo)
	{
		_jointInfo = jointInfo;
	}
	inline void setBoxes(vector<Bbox> bboxes)
	{
		_bboxes = bboxes;
	}
	inline void setBaseFrame(vector<BaseframeJoint> baseFrame)
	{
		_baseFrame = baseFrame;
	}
	inline void setFrames(vector<FrameData> frames)
	{
		_frames = frames;
	}
	inline void setSkelFrames(vector< vector<skeletonJoint> > skelFrames)
	{
		_skelFrames = skelFrames;
	}
	inline void setAnimSkeleton(vector<skeletonJoint> animSkeleton)
	{
		_animSkeleton = animSkeleton;
	}
	inline void setMatrizWeight(vector< vector<Weight> > matrizWeight)
	{
		_matrizWeight = matrizWeight;
	}
	inline void setMatrizCoordAnim(vector< vector<vector2d> > matrizCoordAnim)
	{
		_matrizCoordAnim = matrizCoordAnim;
	}
	inline void setMatrizStart(vector< vector<int> > matrizStart)
	{
		_matrizStart = matrizStart;
	}
	inline void setMatrizCount(vector< vector<int> > matrizCount)
	{
		_matrizCount = matrizCount;
	}
	inline void setIndiceVertices(vector< vector<int> > matrizIndiceVertices)
	{
		_matrizIndiceVertices = matrizIndiceVertices;
	}

	Animacion& operator = (const Animacion &anim);
	int ReadMD5Anim(string filename);
	void Animate(float dt);
	void Render();
	void BuildFrameSkeleton(const vector<JointInfo> &jointInfos, const vector<BaseframeJoint> &baseFrame, const FrameData &animFrameData, vector< vector<skeletonJoint> > &skelFrame);
	void InterpolateSkeletons(vector<skeletonJoint> &out, const vector<skeletonJoint> &skelA, const vector<skeletonJoint> &skelB, float interp);
};

void EliminarSobrante( string& str );
int LongitudFichero( istream& file );

}

#endif
