
#pragma once
#include "mathDefines.h"
#include "extIk.h"
#include "3Vector.h"
#include "3X3Matrix.h"
class zc996524f70{public:zc996524f70();zc996524f70(float zd1edcde5e1,float 
z7b058c25be,float z6e0310fb34,float z46565b3777);zc996524f70(const float 
z37ef40bf5d[(0x15eb+1249-0x1ac8)]);zc996524f70(const z43c30c772b&z37ef40bf5d);
zc996524f70(const zc996524f70&q);zc996524f70(float a,float b,float g);
zc996524f70(float z6fafebb892,const z43c30c772b&z7bd9fa8427);zc996524f70(const 
z43c30c772b&zbaa067b922,const z43c30c772b&z8a33818460);~zc996524f70();void 
zc8c9b1ff2a(const z43c30c772b&z37ef40bf5d);void zc8c9b1ff2a(float a,float b,
float g);void zd55d782e18(float z6fafebb892,const z43c30c772b&z7bd9fa8427);void 
z083379063a(const z43c30c772b&zbaa067b922,const z43c30c772b&z8a33818460);void 
z4174ee2a49(const zc996524f70&z0755af5496,const zc996524f70&z8930959f0b,float t)
;float zc5c0ff5e64(const zc996524f70&q);zc996524f70 z17fc270567()const;
zc996524f70 zebae1d77fd()const;z43c30c772b z5bc3f5e12e()const;inline void 
zadfcae214e(float z9aabdad99d[(0xeeb+349-0x1044)])const{z9aabdad99d[
(0x8ca+6-0x8d0)]=data[(0x18c1+2547-0x22b4)];z9aabdad99d[(0x1087+1567-0x16a5)]=
data[(0x4c0+8125-0x247c)];z9aabdad99d[(0x1338+3775-0x21f5)]=data[
(0x20ef+680-0x2395)];z9aabdad99d[(0x18e9+617-0x1b4f)]=data[(0x130+4058-0x1107)];
}inline void z345062ac80(const float z9aabdad99d[(0x2f2+6068-0x1aa2)]){data[
(0xa8+7722-0x1ed2)]=z9aabdad99d[(0x1c3+5867-0x18ae)];data[(0x30a+8599-0x24a0)]=
z9aabdad99d[(0x88d+1914-0x1006)];data[(0x1147+1542-0x174b)]=z9aabdad99d[
(0x55f+3824-0x144d)];data[(0xbf5+6663-0x25f9)]=z9aabdad99d[(0xa46+6630-0x2429)];
}inline float&operator()(unsigned i){return(data[i]);}inline const float&
operator()(unsigned i)const{return(data[i]);}inline void normalize(){float l=
sqrtf(data[(0x7a6+4163-0x17e9)]*data[(0x54+8960-0x2354)]+data[
(0xf17+2537-0x18ff)]*data[(0x14c+839-0x492)]+data[(0x294+3425-0xff3)]*data[
(0x1e94+1660-0x250e)]+data[(0x102c+4347-0x2124)]*data[(0x1e7+2316-0xaf0)]);data[
(0x95d+591-0xbac)]/=l;data[(0x13f3+1497-0x19cb)]/=l;data[(0x8d6+6351-0x21a3)]/=l
;data[(0xa3a+4251-0x1ad2)]/=l;}inline void clear(){data[(0xba8+2087-0x13cf)]=
0.0f;data[(0x1452+940-0x17fd)]=0.0f;data[(0x4a1+2205-0xd3c)]=0.0f;data[
(0x17a+766-0x475)]=0.0f;}inline void z8079139e84(){data[(0x261+926-0x5ff)]=1.0f;
data[(0x764+1147-0xbde)]=0.0f;data[(0xc22+3821-0x1b0d)]=0.0f;data[
(0x10a3+508-0x129c)]=0.0f;}inline zc996524f70 z2a56b020d9()const{return(
zc996524f70(data[(0xcb3+5764-0x2337)],-data[(0x14ea+3226-0x2183)],-data[
(0x3dc+2433-0xd5b)],-data[(0x72+7911-0x1f56)]));}inline void z0d5a1d870e(){data[
(0x484+6806-0x1f19)]=-data[(0x15c+3147-0xda6)];data[(0x210+8984-0x2526)]=-data[
(0xb20+945-0xecf)];data[(0x13ac+3157-0x1ffe)]=-data[(0x238+4491-0x13c0)];}inline
 zc996524f70 operator/(float z9aabdad99d)const{zc996524f70 zd094a88178;
zd094a88178((0x145a+4091-0x2455))=data[(0x7ef+5806-0x1e9d)]/z9aabdad99d;
zd094a88178((0xe0d+2836-0x1920))=data[(0x14a8+4304-0x2577)]/z9aabdad99d;
zd094a88178((0x1451+1580-0x1a7b))=data[(0x101f+3258-0x1cd7)]/z9aabdad99d;
zd094a88178((0x1233+74-0x127a))=data[(0xf87+4789-0x2239)]/z9aabdad99d;return(
zd094a88178);}inline zc996524f70 operator*(float z9aabdad99d)const{zc996524f70 
zd094a88178;zd094a88178((0x470+2775-0xf47))=data[(0x1ef+6705-0x1c20)]*
z9aabdad99d;zd094a88178((0x1e3d+1418-0x23c6))=data[(0x633+5804-0x1cde)]*
z9aabdad99d;zd094a88178((0xf60+694-0x1214))=data[(0xbda+6439-0x24ff)]*
z9aabdad99d;zd094a88178((0xef6+5786-0x258d))=data[(0xc83+3040-0x1860)]*
z9aabdad99d;return(zd094a88178);}inline zc996524f70&operator=(const zc996524f70&
z37ef40bf5d){data[(0x1b7c+2677-0x25f1)]=z37ef40bf5d((0x972+4610-0x1b74));data[
(0x2d5+8405-0x23a9)]=z37ef40bf5d((0x18+4631-0x122e));data[(0xe86+3836-0x1d80)]=
z37ef40bf5d((0x136f+3954-0x22df));data[(0x2f9+7227-0x1f31)]=z37ef40bf5d(
(0x19fc+2818-0x24fb));return(*this);}inline bool operator!=(const zc996524f70&
z37ef40bf5d){return((data[(0x1b5c+2740-0x2610)]!=z37ef40bf5d((0x1929+144-0x19b9)
))||(data[(0xfd7+5673-0x25ff)]!=z37ef40bf5d((0x7da+5738-0x1e43)))||(data[
(0x18c0+1179-0x1d59)]!=z37ef40bf5d((0x13f6+2977-0x1f95)))||(data[
(0x1bb7+2311-0x24bb)]!=z37ef40bf5d((0x1a1+6489-0x1af7))));}inline zc996524f70 
operator*(const zc996524f70&z37ef40bf5d)const{
zc996524f70 zd094a88178;zd094a88178((0x52c+7141-0x2111))=data[
(0x13bd+4789-0x2672)]*z37ef40bf5d((0xc4c+4274-0x1cfe))-data[(0xdf+4481-0x125f)]*
z37ef40bf5d((0xf0+4703-0x134e))-data[(0x22a+2537-0xc11)]*z37ef40bf5d(
(0xed6+1684-0x1568))-data[(0x1e29+296-0x1f4e)]*z37ef40bf5d((0xc32+1329-0x1160));
zd094a88178((0x2018+163-0x20ba))=data[(0xab7+5831-0x217e)]*z37ef40bf5d(
(0x1340+3101-0x1f5c))+z37ef40bf5d((0xdfc+2307-0x16ff))*data[(0xf1d+2625-0x195d)]
+data[(0xa30+1848-0x1166)]*z37ef40bf5d((0x346+5440-0x1883))-data[
(0x119b+1213-0x1655)]*z37ef40bf5d((0x9cc+2989-0x1577));zd094a88178(
(0x182+8053-0x20f5))=data[(0x230f+11-0x231a)]*z37ef40bf5d((0x785+3742-0x1621))+
z37ef40bf5d((0x18ff+1010-0x1cf1))*data[(0x929+1683-0xfba)]+data[
(0x29f+9312-0x26fc)]*z37ef40bf5d((0xb6c+3467-0x18f6))-data[(0x1212+224-0x12f1)]*
z37ef40bf5d((0xab7+2748-0x1570));zd094a88178((0xc84+5974-0x23d7))=data[
(0x81d+333-0x96a)]*z37ef40bf5d((0x7cb+766-0xac6))+z37ef40bf5d(
(0x117f+4913-0x24b0))*data[(0xa9+3527-0xe6d)]+data[(0x255+7531-0x1fbf)]*
z37ef40bf5d((0xe4a+5848-0x2520))-data[(0xa2d+6555-0x23c6)]*z37ef40bf5d(
(0xdfc+4572-0x1fd7));
return(zd094a88178);}inline z43c30c772b z8d8ecc4db8(int z93438c6aa1)const{
ze2b7e09268 zcec140f672=zc48c746a21();return(zcec140f672.z7bd9fa8427[z93438c6aa1
]);}inline z43c30c772b operator*(const z43c30c772b&z37ef40bf5d)const{
zc996524f70 zd4344cbf8e(1.0f,z37ef40bf5d((0x13b+5340-0x1617)),z37ef40bf5d(
(0x362+6455-0x1c98)),z37ef40bf5d((0x170a+3108-0x232c)));zd4344cbf8e=(*this)*(
zd4344cbf8e*z2a56b020d9());return(z43c30c772b(zd4344cbf8e((0xd40+1693-0x13dc)),
zd4344cbf8e((0x569+5030-0x190d)),zd4344cbf8e((0x45+6786-0x1ac4))));}inline 
zc996524f70 operator+(const zc996524f70&z37ef40bf5d)const{zc996524f70 
zd094a88178;zd094a88178((0x6b5+443-0x870))=data[(0x1054+1485-0x1621)]+
z37ef40bf5d((0xab3+4714-0x1d1d));zd094a88178((0x909+6624-0x22e8))=data[
(0x1e7c+1799-0x2582)]+z37ef40bf5d((0x402+7735-0x2238));zd094a88178(
(0x858+3601-0x1667))=data[(0x943+1792-0x1041)]+z37ef40bf5d((0xf41+2583-0x1956));
zd094a88178((0x1a1a+2690-0x2499))=data[(0x289+6460-0x1bc2)]+z37ef40bf5d(
(0x11d0+337-0x131e));return(zd094a88178);}inline ze2b7e09268 zc48c746a21()const{
ze2b7e09268 zc025341aa2;float z2e7d3b574e=data[(0x70b+526-0x918)]*data[
(0x342+8104-0x22e9)];float z4890ad51e9=data[(0x555+486-0x73a)]*data[
(0x1ea3+306-0x1fd3)];float zb20864294c=data[(0xdd9+3590-0x1bde)]*data[
(0x5ad+2790-0x1090)];float zd2a95a1fed=data[(0x1b71+2672-0x25e0)]*data[
(0xd2a+4584-0x1f12)];float zac51a2c411=data[(0x56b+8343-0x2600)]*data[
(0x1267+2311-0x1b6c)];float z3e13f4dfa7=data[(0x184d+2117-0x2090)]*data[
(0x8a7+2536-0x128c)];float zb8ebc58328=data[(0x1afd+919-0x1e92)]*data[
(0xea5+2515-0x1878)];float z2aa8e507da=data[(0x2231+66-0x2270)]*data[
(0x17d4+2648-0x2229)];float z2aa7c6fc71=data[(0x610+1704-0xcb5)]*data[
(0x1657+1093-0x1a9c)];zc025341aa2((0x1421+4228-0x24a5),(0x6af+7596-0x245b))=1.0f
-2.0f*(zac51a2c411+z2aa8e507da);zc025341aa2((0x19f5+443-0x1bb0),
(0x15ab+1656-0x1c22))=2.0f*(z4890ad51e9-z2aa7c6fc71);zc025341aa2(
(0xc5d+5787-0x22f8),(0x18e0+1899-0x2049))=2.0f*(zb20864294c+zb8ebc58328);
zc025341aa2((0x1b65+2761-0x262d),(0x3a1+2825-0xeaa))=2.0f*(z4890ad51e9+
z2aa7c6fc71);zc025341aa2((0x885+5355-0x1d6f),(0xd61+1375-0x12bf))=1.0f-2.0f*(
z2e7d3b574e+z2aa8e507da);zc025341aa2((0x80+5365-0x1574),(0x6f1+941-0xa9c))=2.0f*
(z3e13f4dfa7-zd2a95a1fed);zc025341aa2((0xd7+4572-0x12b1),(0x183d+931-0x1be0))=
2.0f*(zb20864294c-zb8ebc58328);zc025341aa2((0x11+1951-0x7ae),(0x465+5911-0x1b7b)
)=2.0f*(z3e13f4dfa7+zd2a95a1fed);zc025341aa2((0x9a3+2984-0x1549),
(0x517+5695-0x1b54))=1.0f-2.0f*(z2e7d3b574e+zac51a2c411);return(zc025341aa2);}
inline void operator/=(float z9aabdad99d){data[(0x1462+1751-0x1b39)]/=
z9aabdad99d;data[(0x3e8+3210-0x1071)]/=z9aabdad99d;data[(0x851+6049-0x1ff0)]/=
z9aabdad99d;data[(0x136a+94-0x13c5)]/=z9aabdad99d;}inline void operator*=(float 
z9aabdad99d){data[(0x9d3+2023-0x11ba)]*=z9aabdad99d;data[(0x1d73+2122-0x25bc)]*=
z9aabdad99d;data[(0x10b4+5646-0x26c0)]*=z9aabdad99d;data[(0xacf+3003-0x1687)]*=
z9aabdad99d;}inline void operator*=(const zc996524f70&z37ef40bf5d){(*this)=(*
this)*z37ef40bf5d;
}inline void operator+=(const zc996524f70&z37ef40bf5d){data[(0x13b1+1909-0x1b26)
]+=z37ef40bf5d((0x148d+1546-0x1a97));data[(0x1e3+3029-0xdb7)]+=z37ef40bf5d(
(0x1+134-0x86));data[(0x1646+3036-0x2220)]+=z37ef40bf5d((0x77c+3811-0x165d));
data[(0xb8f+2136-0x13e4)]+=z37ef40bf5d((0xab2+3288-0x1787));}static const 
zc996524f70 z6dbe01008c;float data[(0x135f+2435-0x1cde)];};
