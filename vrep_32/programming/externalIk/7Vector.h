
#pragma once
#include "mathDefines.h"
#include "extIk.h"
#include "3Vector.h"
#include "4Vector.h"
class z38505d4d88;
class zcab2ae559c{public:zcab2ae559c();zcab2ae559c(const zcab2ae559c&z37ef40bf5d
);zcab2ae559c(const zc996524f70&q);zcab2ae559c(const z43c30c772b&x);zcab2ae559c(
const zc996524f70&q,const z43c30c772b&x);zcab2ae559c(const float zcec140f672[
(0x1554+2857-0x2079)][(0x64c+4452-0x17ac)]);zcab2ae559c(const z38505d4d88&
zcec140f672);zcab2ae559c(float z6fafebb892,const z43c30c772b&z8a7e6753de,const 
z43c30c772b&z34a925d9ab);~zcab2ae559c();void z8079139e84();void za35174b61d(
float zcec140f672[(0xc5a+4368-0x1d66)][(0x1eda+518-0x20dc)]);void za35174b61d(
const z38505d4d88&zcec140f672);z38505d4d88 zc48c746a21()const;zcab2ae559c 
z2a56b020d9()const;void z8b98bfb2be(const zcab2ae559c&z7b058c25be,const 
zcab2ae559c&z6e0310fb34);void z4174ee2a49(const zcab2ae559c&z0755af5496,const 
zcab2ae559c&z8930959f0b,float t);void z0d5a1d870e();void z692df07ea8(float 
zcec140f672[(0x20d1+409-0x2266)][(0x543+1110-0x995)])const;z43c30c772b 
z8d8ecc4db8(int z93438c6aa1)const;zcab2ae559c operator*(const zcab2ae559c&
z37ef40bf5d)const;void operator*=(const zcab2ae559c&z37ef40bf5d);z43c30c772b 
operator*(const z43c30c772b&z37ef40bf5d)const;zcab2ae559c&operator=(const 
zcab2ae559c&z37ef40bf5d);inline void zadfcae214e(float z9aabdad99d[
(0x121d+3236-0x1eba)])const{X.zadfcae214e(z9aabdad99d+(0xa27+4533-0x1bdc));Q.
zadfcae214e(z9aabdad99d+(0xc55+405-0xde7));}inline void z345062ac80(const float 
z9aabdad99d[(0xf36+1977-0x16e8)]){X.z345062ac80(z9aabdad99d+(0x1159+231-0x1240))
;Q.z345062ac80(z9aabdad99d+(0x1791+1586-0x1dc0));}inline bool operator!=(const 
zcab2ae559c&z37ef40bf5d){return((Q!=z37ef40bf5d.Q)||(X!=z37ef40bf5d.X));}inline 
float&operator()(unsigned i){if(i<(0x22b+4883-0x153b))return(X(i));else return(Q
(i-(0x15c8+556-0x17f1)));}inline const float&operator()(unsigned i)const{if(i<
(0x174+2032-0x961))return(X(i));else return(Q(i-(0x2463+34-0x2482)));}static 
const zcab2ae559c z22ca8a1799;zc996524f70 Q;z43c30c772b X;};
