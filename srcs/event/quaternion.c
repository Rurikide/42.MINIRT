#include "../incls/mini_rt.h"


// QUATERNIONS USE
// they store an axis and the amount of rotation about the axis
// using the appropriate quaternion rotation matrix, you will be able to rotate
// an object over some arbitrarily-defined-axis by some arbitrarily-amount without the fear of gimbal lock

t_quaternion    new_quaternion(double w, double x, double y, double z)
{
	t_quaternion q;

	q.w = w;
	q.x = x;
	q.y = y;
	q.z = z;

	return (q);
}

double  quaternion_normalize(t_quaternion *q)
{
	double magnitude;

	magnitude = sqrt(q->w * q->w + q->x * q->x + q->y * q->y + q->z * q->z);
	q->w /= magnitude;
	q->x /= magnitude;
	q->y /= magnitude;
	q->z /= magnitude;

	return (magnitude);
}

// IMPORTANT QUAT MULTI IS NOT COMMUTATIVE
t_quaternion	quaternion_multiply(t_quaternion src, t_quaternion dst)
{
	t_quaternion result;

	result.w = src.w*dst.w - src.x*dst.x - src.y*dst.y - src.z*dst.z;
	result.x = src.w*dst.x + src.x*dst.w + src.y*dst.z - src.z*dst.y;
	result.y = src.w*dst.y - src.x*dst.z + src.y*dst.w + src.z*dst.x;
	result.z = src.w*dst.z + src.x*dst.y - src.y*dst.x + src.z*dst.w;

	return (result);
}

// to change the rotation represented by a quaternion, a few steps are necessary. 
// step 1: generate a temporary quaternion, which will backwards over the x-axis a little bit
// this temp quaternion will represent that step 1

// step 2: by multiplying the temp and permanent quaternions together, we will generate a new permanent quat
// which has the permanent quat rotation axis changed by the rotation described in the temp quaternion

// by convention the temp quaternion is called LOCAL_ROTATION quaternion.

// generate local_rocation()
// TOTAL is the PERMANENT QUATERNION
// total = LOCAL_ROTATION * TOTAL   THE ORDER IS IMPORTANT
// to generate local_location, you need AXIS and ANGLE prepared, and this will convert them to a quaternion.
// the formulae for generating the local_rotation quaternion

// FORMULAE
// axis is a unit 3d direction vector
t_quaternion	quaternion_local_rotation(t_vec3 axis, double angle)
{
	t_quaternion local;

	local.w = cosf(angle * 0.5);
	local.x = axis.x * sinf(angle * 0.5);
	local.y = axis.y * sinf(angle * 0.5);
	local.z = axis.z * sinf(angle * 0.5);

	return (local);
}



/*
And, since we're only dealing with unit quaternions, that matrix can be optimized a bit down to this:

1-2y2-2z2
	

2xy-2wz
	

2xz+2wy
	

0

2xy+2wz
	

1-2x2-2z2
	

2yz+2wx
	

0

2xz-2wy
	

2yz-2wx
	

1-2x2-2y2
	

0

0
	

0
	

0
	

1
*/
