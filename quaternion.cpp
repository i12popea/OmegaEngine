#include "quaternion.hpp"
 
using namespace std;
using namespace ed;
 
namespace ed{

quaternion& quaternion::operator = (quaternion const &vector)
{
    if(this != &vector)
    {
        setX(vector.getX());
        setY(vector.getY());
        setZ(vector.getZ());
        setW(vector.getW());
    }
    return *this;
}

/*void Quat_computeW (quaternion &q)
{
  float t = 1.0f - (q.getX() * q.getX()) - (q.getY() * q.getY()) - (q.getZ() * q.getZ());

  if (t < 0.0f)
    q.setW(0.0f);
  else
    q.setW(-sqrt(t));
}*/

void quaternion::Quat_computeW()
{
	float t = 1.0f - (_x * _x) - (_y * _y) - (_z * _z);

	if (t < 0.0f)
		_w = 0.0f;
	else
		_w = -sqrt(t);
}

/*void Quat_normalize (quaternion &q)
{
  // compute magnitude of the quaternion
  float mag = sqrt ((q.getX() * q.getX()) + (q.getY() * q.getY()) + (q.getZ() * q.getZ()) + (q.getW() * q.getW()));

  // check for bogus length, to protect against divide by zero
  if (mag > 0.0f)
    {
      // normalize it
      float oneOverMag = 1.0f / mag;

      q.setX(q.getX() * oneOverMag);
      q.setY(q.getY() * oneOverMag);
      q.setZ(q.getZ() * oneOverMag);
      q.setW(q.getW() * oneOverMag);
    }
}*/

void quaternion::Quat_normalize()
{
	/* compute magnitude of the quaternion */
	float mag = sqrt ((_x * _x) + (_y * _y) + (_z * _z) + (_w * _w));

	/* check for bogus length, to protect against divide by zero */
	if (mag > 0.0f)
	{
		/* normalize it */
		float oneOverMag = 1.0f / mag;

		_x = _x * oneOverMag;
		_y = _y * oneOverMag;
		_z = _z * oneOverMag;
		_w = _w * oneOverMag;
	}
}

/*void Quat_multQuat (const quaternion qa, const quaternion qb, quaternion &out)
{
  out.setW((qa.getW() * qb.getW()) - (qa.getX() * qb.getX()) - (qa.getY() * qb.getY()) - (qa.getZ() * qb.getZ()));
  out.setX((qa.getX() * qb.getW()) + (qa.getW() * qb.getX()) + (qa.getY() * qb.getZ()) - (qa.getZ() * qb.getY()));
  out.setY((qa.getY() * qb.getW()) + (qa.getW() * qb.getY()) + (qa.getZ() * qb.getX()) - (qa.getX() * qb.getZ()));
  out.setZ((qa.getZ() * qb.getW()) + (qa.getW() * qb.getZ()) + (qa.getX() * qb.getY()) - (qa.getY() * qb.getX()));
}*/

quaternion Quat_multQuat (const quaternion qa, const quaternion qb)
{
	quaternion out;
	out.setW((qa.getW() * qb.getW()) - (qa.getX() * qb.getX()) - (qa.getY() * qb.getY()) - (qa.getZ() * qb.getZ()));
	out.setX((qa.getX() * qb.getW()) + (qa.getW() * qb.getX()) + (qa.getY() * qb.getZ()) - (qa.getZ() * qb.getY()));
	out.setY((qa.getY() * qb.getW()) + (qa.getW() * qb.getY()) + (qa.getZ() * qb.getX()) - (qa.getX() * qb.getZ()));
	out.setZ((qa.getZ() * qb.getW()) + (qa.getW() * qb.getZ()) + (qa.getX() * qb.getY()) - (qa.getY() * qb.getX()));
	return out;
}

/*void Quat_multVec (const quaternion q, const vector3d v, quaternion &out)
{
  out.setW(-(q.getX() * v.getX()) - (q.getY() * v.getY()) - (q.getZ() * v.getZ()));
  out.setX((q.getW() * v.getX()) + (q.getY() * v.getZ()) - (q.getZ() * v.getY()));
  out.setY((q.getW() * v.getY()) + (q.getZ() * v.getX()) - (q.getX() * v.getZ()));
  out.setZ((q.getW() * v.getZ()) + (q.getX() * v.getY()) - (q.getY() * v.getX()));
}*/

quaternion Quat_multVec (const quaternion q, const vector3d v)
{
	quaternion out;
	out.setW(-(q.getX() * v.getX()) - (q.getY() * v.getY()) - (q.getZ() * v.getZ()));
	out.setX((q.getW() * v.getX()) + (q.getY() * v.getZ()) - (q.getZ() * v.getY()));
	out.setY((q.getW() * v.getY()) + (q.getZ() * v.getX()) - (q.getX() * v.getZ()));
	out.setZ((q.getW() * v.getZ()) + (q.getX() * v.getY()) - (q.getY() * v.getX()));
	return out;
}

/*void Quat_rotatePoint (const quaternion q, const vector3d in, vector3d &out)
{
  quaternion tmp, inv, fin;

  inv.setX(-q.getX()); inv.setY(-q.getY());
  inv.setZ(-q.getZ()); inv.setW(q.getW());

  Quat_normalize(inv);

  Quat_multVec(q, in, tmp);
  Quat_multQuat(tmp, inv, fin);

  out.setX(fin.getX());
  out.setY(fin.getY());
  out.setZ(fin.getZ());
}*/

vector3d Quat_rotatePoint (const quaternion q, const vector3d in)
{
	vector3d out;
	quaternion tmp, inv, fin;

	inv.setX(-q.getX()); inv.setY(-q.getY());
	inv.setZ(-q.getZ()); inv.setW(q.getW());

	inv.Quat_normalize();

	tmp = Quat_multVec(q, in);
	fin = Quat_multQuat(tmp, inv);

	out.setX(fin.getX());
	out.setY(fin.getY());
	out.setZ(fin.getZ());

	return out;
}

float Quat_dotProduct (const quaternion qa, const quaternion qb)
{
	return ((qa.getX() * qb.getX()) + (qa.getY() * qb.getY()) + (qa.getZ() * qb.getZ()) + (qa.getW() * qb.getW()));
}

void Quat_slerp (const quaternion qa, const quaternion qb, float t, quaternion &out)
{
  /* Check for out-of range parameter and return edge points if so */
  if (t <= 0.0)
    {
      //memcpy (out, qa, sizeof(quaternion));
      out = qa;
      return;
    }

  if (t >= 1.0)
    {
      //memcpy (out, qb, sizeof (quaternion));
      out = qb;
      return;
    }

  /* Compute "cosine of angle between quaternions" using dot product */
  float cosOmega = Quat_dotProduct(qa, qb);

  /* If negative dot, use -q1.  Two quaternions q and -q
     represent the same rotation, but may produce
     different slerp.  We chose q or -q to rotate using
     the acute angle. */
  float q1w = qb.getW();
  float q1x = qb.getX();
  float q1y = qb.getY();
  float q1z = qb.getZ();

  if (cosOmega < 0.0f)
    {
      q1w = -q1w;
      q1x = -q1x;
      q1y = -q1y;
      q1z = -q1z;
      cosOmega = -cosOmega;
    }

  /* We should have two unit quaternions, so dot should be <= 1.0 */
  assert (cosOmega < 1.1f);

  /* Compute interpolation fraction, checking for quaternions
     almost exactly the same */
  float k0, k1;

  if (cosOmega > 0.9999f)
    {
      /* Very close - just use linear interpolation,
	 which will protect againt a divide by zero */

      k0 = 1.0f - t;
      k1 = t;
    }
  else
    {
      /* Compute the sin of the angle using the
	 trig identity sin^2(omega) + cos^2(omega) = 1 */
      float sinOmega = sqrt (1.0f - (cosOmega * cosOmega));

      /* Compute the angle from its sin and cosine */
      float omega = atan2 (sinOmega, cosOmega);

      /* Compute inverse of denominator, so we only have
	 to divide once */
      float oneOverSinOmega = 1.0f / sinOmega;

      /* Compute interpolation parameters */
      k0 = sin ((1.0f - t) * omega) * oneOverSinOmega;
      k1 = sin (t * omega) * oneOverSinOmega;
    }

  /* Interpolate and return new quaternion */
  out.setW((k0 * qa.getW()) + (k1 * q1w));
  out.setX((k0 * qa.getX()) + (k1 * q1x));
  out.setY((k0 * qa.getY()) + (k1 * q1y));
  out.setZ((k0 * qa.getZ()) + (k1 * q1z));
}
 
}
