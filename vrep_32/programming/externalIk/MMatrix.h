
#pragma once
#include "mathDefines.h"
#include "extIk.h"
#include "3X3Matrix.h"
#include "4X4Matrix.h"
#include "6X6Matrix.h"
#include "Vector.h"
class z957fc62c41{public:z957fc62c41();
z957fc62c41(int z24dcc27d94,int zf6188af592);z957fc62c41(const ze2b7e09268&
zcec140f672);z957fc62c41(const z38505d4d88&zcec140f672);z957fc62c41(const 
z11fde56c28&zcec140f672);z957fc62c41(const z957fc62c41&zcec140f672);~z957fc62c41
();bool z0d5a1d870e();void z9b0b4ab621();void clear();void z8079139e84();
z957fc62c41 operator*(const ze2b7e09268&zcec140f672)const;z957fc62c41 operator*(
const z38505d4d88&zcec140f672)const;z957fc62c41 operator*(const z11fde56c28&
zcec140f672)const;z957fc62c41 operator*(const z957fc62c41&zcec140f672)const;
z957fc62c41 operator*(float z9aabdad99d)const;z957fc62c41 operator/(float 
z9aabdad99d)const;ze230f62758 operator*(const ze230f62758&z37ef40bf5d)const;
z957fc62c41 operator+(const z957fc62c41&zcec140f672)const;z957fc62c41 operator-(
const z957fc62c41&zcec140f672)const;void operator*=(const z957fc62c41&
zcec140f672);void operator+=(const z957fc62c41&zcec140f672);void operator-=(
const z957fc62c41&zcec140f672);void operator*=(float z9aabdad99d);void operator
/=(float z9aabdad99d);z957fc62c41&operator=(const ze2b7e09268&zcec140f672);
z957fc62c41&operator=(const z38505d4d88&zcec140f672);z957fc62c41&operator=(const
 z11fde56c28&zcec140f672);z957fc62c41&operator=(const z957fc62c41&zcec140f672);
inline float&operator()(int zcb41917595,int z9082a251b4){return(data[zcb41917595
*z2468d7d02c+z9082a251b4]);}inline float z7b78657f1d(int zcb41917595,int 
z9082a251b4)const{return(data[zcb41917595*z2468d7d02c+z9082a251b4]);}inline void
 z5ca26ffb6e(int zcb41917595,int z9082a251b4,float value){data[zcb41917595*
z2468d7d02c+z9082a251b4]=value;}inline const float&operator()(int zcb41917595,
int z9082a251b4)const{return(data[zcb41917595*z2468d7d02c+z9082a251b4]);}int 
z3b6bdfe927,z2468d7d02c;private:float*data;};
