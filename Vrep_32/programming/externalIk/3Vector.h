
#pragma once
#include "mathDefines.h"
#include "extIk.h"
class ze2b7e09268;class z38505d4d88;class zcab2ae559c;class z43c30c772b{public:
z43c30c772b();z43c30c772b(float zd1edcde5e1,float z7b058c25be,float z6e0310fb34)
;z43c30c772b(const float z37ef40bf5d[(0xf23+3746-0x1dc2)]);z43c30c772b(const 
z43c30c772b&z37ef40bf5d);~z43c30c772b();void z4174ee2a49(const z43c30c772b&
z0755af5496,const z43c30c772b&z8930959f0b,float t);float z6f55e083ba(const 
z43c30c772b&z37ef40bf5d)const;ze2b7e09268 z6a5f3da250()const;void operator*=(
const z38505d4d88&zcec140f672);void operator*=(const ze2b7e09268&zcec140f672);
void operator*=(const zcab2ae559c&zf2dc2f6435);inline void zadfcae214e(float 
z9aabdad99d[(0xa6c+1022-0xe67)])const{z9aabdad99d[(0x830+5477-0x1d95)]=data[
(0x21ba+522-0x23c4)];z9aabdad99d[(0x558+1544-0xb5f)]=data[(0x12cc+4337-0x23bc)];
z9aabdad99d[(0xeda+3026-0x1aaa)]=data[(0x75a+2228-0x100c)];}inline void 
z345062ac80(const float z9aabdad99d[(0x394+7140-0x1f75)]){data[
(0x6d6+3152-0x1326)]=z9aabdad99d[(0x63b+5823-0x1cfa)];data[(0x422+4012-0x13cd)]=
z9aabdad99d[(0x42f+4649-0x1657)];data[(0x7e4+4455-0x1949)]=z9aabdad99d[
(0x52a+5487-0x1a97)];}inline float*z780df94f7f(){return(data);}inline bool 
zacb7a08926(const z43c30c772b&z37ef40bf5d,float precision)const{float 
z128a62786f=(*this)*z37ef40bf5d;z128a62786f=z128a62786f*z128a62786f;float 
z56a5844769=(*this)*(*this);float z8b165133af=z37ef40bf5d*z37ef40bf5d;return((
z128a62786f/(z56a5844769*z8b165133af))>=precision);}inline float&operator()(
unsigned i){return(data[i]);}inline const float&operator()(unsigned i)const{
return(data[i]);}inline float zbc5ef27003()const{return(sqrtf(data[
(0x4f6+5808-0x1ba6)]*data[(0x48c+918-0x822)]+data[(0x68a+3583-0x1488)]*data[
(0xd93+132-0xe16)]+data[(0x1d01+2548-0x26f3)]*data[(0x1d4c+1477-0x230f)]));}
inline void z692df07ea8(float z37ef40bf5d[(0xf22+4408-0x2057)])const{z37ef40bf5d
[(0x592+5604-0x1b76)]=data[(0x40c+6583-0x1dc3)];z37ef40bf5d[(0x54b+8014-0x2498)]
=data[(0x926+557-0xb52)];z37ef40bf5d[(0x1b1+243-0x2a2)]=data[
(0x1dfc+1395-0x236d)];}inline void za35174b61d(const float z37ef40bf5d[
(0x9bd+959-0xd79)]){data[(0x24e6+346-0x2640)]=z37ef40bf5d[(0x193+4460-0x12ff)];
data[(0xcad+3333-0x19b1)]=z37ef40bf5d[(0x12f4+4244-0x2387)];data[
(0x9d8+6205-0x2213)]=z37ef40bf5d[(0xe59+1218-0x1319)];}inline void get(float 
z37ef40bf5d[(0x502+4043-0x14ca)])const{z37ef40bf5d[(0x584+5600-0x1b64)]=data[
(0x1f4d+356-0x20b1)];z37ef40bf5d[(0x775+6519-0x20eb)]=data[(0x968+7202-0x2589)];
z37ef40bf5d[(0x10b6+729-0x138d)]=data[(0x188+7049-0x1d0f)];}inline z43c30c772b 
zce732648bf()const{z43c30c772b zd094a88178;float l=sqrtf(data[
(0xd66+2254-0x1634)]*data[(0xf75+4697-0x21ce)]+data[(0x1d37+1104-0x2186)]*data[
(0x14d4+964-0x1897)]+data[(0xea+192-0x1a8)]*data[(0x1422+4302-0x24ee)]);if(l!=
0.0f){zd094a88178((0x13a4+3268-0x2068))=data[(0xd41+4244-0x1dd5)]/l;zd094a88178(
(0xa9a+5889-0x219a))=data[(0x40+1815-0x756)]/l;zd094a88178((0x462+4356-0x1564))=
data[(0xaa3+2650-0x14fb)]/l;return(zd094a88178);}return(z43c30c772b::z69267038d3
);}inline void zcdf0b2defb(const z43c30c772b&z37ef40bf5d){if(z37ef40bf5d(
(0xcd0+6641-0x26c1))>data[(0x3a+906-0x3c4)])data[(0x12ca+2262-0x1ba0)]=
z37ef40bf5d((0xd50+3040-0x1930));if(z37ef40bf5d((0x785+2573-0x1191))>data[
(0x1911+420-0x1ab4)])data[(0x1a6b+2496-0x242a)]=z37ef40bf5d((0x98f+922-0xd28));
if(z37ef40bf5d((0x5e4+5101-0x19cf))>data[(0x42+8255-0x207f)])data[
(0x766+7791-0x25d3)]=z37ef40bf5d((0x1d40+534-0x1f54));}inline void zd2af439578(
const z43c30c772b&z37ef40bf5d){if(z37ef40bf5d((0x129c+2402-0x1bfe))<data[
(0x1b+5562-0x15d5)])data[(0xcd2+3483-0x1a6d)]=z37ef40bf5d((0x9dd+1412-0xf61));if
(z37ef40bf5d((0xd6a+3237-0x1a0e))<data[(0x1143+1219-0x1605)])data[
(0x70c+6492-0x2067)]=z37ef40bf5d((0xd92+572-0xfcd));if(z37ef40bf5d(
(0x1624+1399-0x1b99))<data[(0x544+6747-0x1f9d)])data[(0x613+7543-0x2388)]=
z37ef40bf5d((0xae6+2511-0x14b3));}inline bool z8493e69197()const{return((
VREP_IS_FINITE(data[(0x199+3945-0x1102)])!=(0x65f+7004-0x21bb))&&(VREP_IS_FINITE
(data[(0xfe9+48-0x1018)])!=(0xb84+4088-0x1b7c))&&(VREP_IS_FINITE(data[
(0x19a7+2723-0x2448)])!=(0x3ac+1166-0x83a))&&(VREP_IS_NAN(data[
(0x104f+2664-0x1ab7)])==(0x9c6+2837-0x14db))&&(VREP_IS_NAN(data[
(0xdd4+851-0x1126)])==(0x14c+534-0x362))&&(VREP_IS_NAN(data[(0x1a1f+973-0x1dea)]
)==(0xa48+4337-0x1b39)));}inline void za35174b61d(float zd1edcde5e1,float 
z7b058c25be,float z6e0310fb34){data[(0x3e5+7636-0x21b9)]=zd1edcde5e1;data[
(0xa89+973-0xe55)]=z7b058c25be;data[(0xe6+3820-0xfd0)]=z6e0310fb34;}inline void 
normalize(){float l=sqrtf(data[(0x2d4+584-0x51c)]*data[(0x71a+4918-0x1a50)]+data
[(0xe6f+16-0xe7e)]*data[(0x1aba+1068-0x1ee5)]+data[(0x39d+6715-0x1dd6)]*data[
(0xe2c+58-0xe64)]);if(l!=0.0f){data[(0x171b+1410-0x1c9d)]=data[
(0x1714+3486-0x24b2)]/l;data[(0x20a0+1260-0x258b)]=data[(0x89+1285-0x58d)]/l;
data[(0x5b1+2374-0xef5)]=data[(0x37+2749-0xaf2)]/l;}}inline void clear(){data[
(0xba0+4568-0x1d78)]=0.0f;data[(0x414+3468-0x119f)]=0.0f;data[(0xdcd+296-0xef3)]
=0.0f;}inline z43c30c772b operator/(float z9aabdad99d)const{z43c30c772b 
zd094a88178;zd094a88178((0x1378+1049-0x1791))=data[(0x73a+7996-0x2676)]/
z9aabdad99d;zd094a88178((0x16e9+3485-0x2485))=data[(0x1fc+2100-0xa2f)]/
z9aabdad99d;zd094a88178((0xd31+136-0xdb7))=data[(0xd96+6361-0x266d)]/z9aabdad99d
;return(zd094a88178);}inline void operator/=(float z9aabdad99d){data[
(0x4cd+6181-0x1cf2)]/=z9aabdad99d;data[(0x6cf+7473-0x23ff)]/=z9aabdad99d;data[
(0x1b52+1352-0x2098)]/=z9aabdad99d;}inline z43c30c772b operator*(float 
z9aabdad99d)const{z43c30c772b zd094a88178;zd094a88178((0x11a2+3191-0x1e19))=data
[(0x1569+3213-0x21f6)]*z9aabdad99d;zd094a88178((0x660+3210-0x12e9))=data[
(0xaef+5224-0x1f56)]*z9aabdad99d;zd094a88178((0x491+4125-0x14ac))=data[
(0x1c21+1559-0x2236)]*z9aabdad99d;return(zd094a88178);}inline void operator*=(
float z9aabdad99d){data[(0x1575+1349-0x1aba)]*=z9aabdad99d;data[
(0x8e8+2109-0x1124)]*=z9aabdad99d;data[(0xe2b+1699-0x14cc)]*=z9aabdad99d;}inline
 z43c30c772b&operator=(const z43c30c772b&z37ef40bf5d){data[(0x2060+380-0x21dc)]=
z37ef40bf5d((0x223+4651-0x144e));data[(0x109f+3364-0x1dc2)]=z37ef40bf5d(
(0xf4d+1690-0x15e6));data[(0x1250+3968-0x21ce)]=z37ef40bf5d((0xa39+178-0xae9));
return(*this);}inline bool operator!=(const z43c30c772b&z37ef40bf5d){return((
data[(0x152+8559-0x22c1)]!=z37ef40bf5d((0x128+2846-0xc46)))||(data[
(0x1442+3252-0x20f5)]!=z37ef40bf5d((0x231b+29-0x2337)))||(data[
(0x33d+3611-0x1156)]!=z37ef40bf5d((0xd5d+4623-0x1f6a))));}inline z43c30c772b 
operator+(const z43c30c772b&z37ef40bf5d)const{z43c30c772b zd094a88178;
zd094a88178((0x68c+3526-0x1452))=data[(0x13e9+1257-0x18d2)]+z37ef40bf5d(
(0xb2d+134-0xbb3));zd094a88178((0x1443+1998-0x1c10))=data[(0x4a1+232-0x588)]+
z37ef40bf5d((0x557+2678-0xfcc));zd094a88178((0x18d1+3153-0x2520))=data[
(0x8f4+6938-0x240c)]+z37ef40bf5d((0x19a8+1275-0x1ea1));return(zd094a88178);}
inline void operator+=(const z43c30c772b&z37ef40bf5d){data[(0x1691+130-0x1713)]
+=z37ef40bf5d((0x12a2+4976-0x2612));data[(0x37f+7083-0x1f29)]+=z37ef40bf5d(
(0x1087+4013-0x2033));data[(0x1aea+2260-0x23bc)]+=z37ef40bf5d((0x19f+833-0x4de))
;}inline z43c30c772b operator-(const z43c30c772b&z37ef40bf5d)const{z43c30c772b 
zd094a88178;zd094a88178((0x3d8+2590-0xdf6))=data[(0xf58+5587-0x252b)]-
z37ef40bf5d((0xae6+1898-0x1250));zd094a88178((0x10ed+2690-0x1b6e))=data[
(0x118b+2942-0x1d08)]-z37ef40bf5d((0x8e4+3301-0x15c8));zd094a88178(
(0x72+4844-0x135c))=data[(0x1290+3588-0x2092)]-z37ef40bf5d((0x8ca+3564-0x16b4));
return(zd094a88178);}inline void operator-=(const z43c30c772b&z37ef40bf5d){data[
(0x293+3734-0x1129)]-=z37ef40bf5d((0x1332+2377-0x1c7b));data[
(0x10bb+3310-0x1da8)]-=z37ef40bf5d((0x1a17+2282-0x2300));data[
(0x17b+6484-0x1acd)]-=z37ef40bf5d((0xb2f+3898-0x1a67));}inline z43c30c772b 
operator^(const z43c30c772b&z37ef40bf5d)const{
z43c30c772b zd094a88178;zd094a88178((0x6dc+7847-0x2583))=data[
(0xd58+1896-0x14bf)]*z37ef40bf5d((0x569+8495-0x2696))-data[(0xd83+1034-0x118b)]*
z37ef40bf5d((0xf0b+4849-0x21fb));zd094a88178((0xb86+4400-0x1cb5))=data[
(0x914+739-0xbf5)]*z37ef40bf5d((0x124d+5083-0x2628))-data[(0x10ea+4383-0x2209)]*
z37ef40bf5d((0x457+4675-0x1698));zd094a88178((0x22d+5143-0x1642))=data[
(0x1e7d+116-0x1ef1)]*z37ef40bf5d((0xf02+4920-0x2239))-data[(0x3af+8693-0x25a3)]*
z37ef40bf5d((0xab6+4991-0x1e35));return(zd094a88178);}inline void operator^=(
const z43c30c772b&z37ef40bf5d){
z43c30c772b zd094a88178;zd094a88178((0xfbc+4835-0x229f))=data[
(0x17b+6080-0x193a)]*z37ef40bf5d((0x14ab+470-0x167f))-data[(0xf4f+434-0x10ff)]*
z37ef40bf5d((0x870+345-0x9c8));zd094a88178((0x1831+2236-0x20ec))=data[
(0x438+267-0x541)]*z37ef40bf5d((0x1334+4815-0x2603))-data[(0x428+5755-0x1aa3)]*
z37ef40bf5d((0x196f+6-0x1973));zd094a88178((0x807+3987-0x1798))=data[
(0x5d+5391-0x156c)]*z37ef40bf5d((0x3bd+7818-0x2246))-data[(0xfcd+1644-0x1638)]*
z37ef40bf5d((0x291+5401-0x17aa));data[(0x10ab+3958-0x2021)]=zd094a88178(
(0x1747+1033-0x1b50));data[(0x1432+1839-0x1b60)]=zd094a88178((0xdd2+4865-0x20d2)
);data[(0xd99+1197-0x1244)]=zd094a88178((0x232b+859-0x2684));}inline float 
operator*(const z43c30c772b&z37ef40bf5d)const{
return(data[(0x6d6+1141-0xb4b)]*z37ef40bf5d.data[(0xbe7+3574-0x19dd)]+data[
(0x1e06+1143-0x227c)]*z37ef40bf5d.data[(0x216+6733-0x1c62)]+data[
(0x103d+646-0x12c1)]*z37ef40bf5d.data[(0x2229+965-0x25ec)]);}static const 
z43c30c772b z4527e069a3;static const z43c30c772b z7e831c1eef;static const 
z43c30c772b z289057c4d7;static const z43c30c772b zaebd0fb77e;static const 
z43c30c772b z69267038d3;float data[(0x146+9610-0x26cd)];};
