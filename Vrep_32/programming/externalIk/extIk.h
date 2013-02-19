#pragma once

#include <math.h>
#include <vector>
#include <string>
#include <float.h>
#include <limits>

#define VREP_INLINE inline
#define SIM_ASSERT(x)
#define SIM_IS_BIT_SET(var,bit) (((var) & (1<<(bit)))!=0)

#ifdef _WIN32
	#define VREP_IS_FINITE(x) (_finite(x))
	#define VREP_IS_NAN(x) (_isnan(x))
#endif // _WIN32

#ifdef __APPLE__
	#define VREP_IS_FINITE(x) (finite(x))
	#define VREP_IS_NAN(x) ((boost::math::isnan)(x))
#endif // __APPLE__

#ifdef __linux
	#define VREP_IS_NAN(x) (isnan(x))
	#define VREP_IS_FINITE(x)                           \
            (sizeof (x) == sizeof (float)                   \
            ? __finitef (x)                                 \
            : sizeof (x) == sizeof (double)                 \
            ? __finite (x) : __finitel (x))
#endif // __linux

bool simEmbLaunch();
bool simEmbShutDown();
int simEmbStart(unsigned char* data,int dataLength);

int simEmbGetObjectHandle(const char* objectName);
int simEmbGetObjectParent(int objectHandle);
int simEmbSetObjectParent(int objectHandle,int parentObjectHandle,bool keepInPlace);

int simEmbGetJointPosition(int jointHandle,float* position);
int simEmbSetJointPosition(int jointHandle,float position);
int simEmbGetJointTransformation(int jointHandle,float* position,float* quaternion);
int simEmbSetSphericalJointQuaternion(int jointHandle,const float* quaternion);
int simEmbSetJointMode(int jointHandle,int jointMode);

int simEmbGetIkGroupHandle(const char* ikGroupName);
int simEmbHandleIkGroup(int ikGroupHandle);
int simEmbSetIkGroupExplicitHandling(int ikGroupHandle,bool explicitHandling);
int simEmbSetIkGroupProperties(int ikGroupHandle,int resolutionMethod,int maxIterations,float damping);
int simEmbSetIkElementProperties(int ikGroupHandle,int tipDummyHandle,int constraints,const float* precision,const float* weight);

int simEmbGetObjectTransformation(int objectHandle,int relativeToObjectHandle,float* position,float* quaternion);
int simEmbSetObjectTransformation(int objectHandle,int relativeToObjectHandle,const float* position,const float* quaternion);
int simEmbQuaternionToEulerAngles(const float* quaternion,float* euler);
int simEmbEulerAnglesToQuaternion(const float* euler,float* quaternion);
int simEmbInvertTransformation(float* position,float* quaternion);
int simEmbMultiplyTransformations(const float* position1,const float* quaternion1,const float* position2,const float* quaternion2,float* positionOut,float* quaternionOut);
int simEmbInterpolateTransformations(const float* position1,const float* quaternion1,const float* position2,const float* quaternion2,float interpolFactor,float* positionOut,float* quaternionOut);
int simEmbMultTransformationWithVector(const float* position,const float* quaternion,float* vect);
int simEmbGetRotationAxis(const float* positionStart,const float* quaternionStart,const float* positionGoal,const float* quaternionGoal,float* axis,float* angle);
int simEmbRotateAroundAxis(const float* positionIn,const float* quaternionIn,const float* axisVector,const float* axisPosition,float angle,float* positionOut,float* quaternionOut);
