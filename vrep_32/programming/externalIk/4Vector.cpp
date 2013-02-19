

#include "4Vector.h"
#include "MyMath.h"
zc996524f70::zc996524f70(){}zc996524f70::zc996524f70(float zd1edcde5e1,float 
z7b058c25be,float z6e0310fb34,float z46565b3777){data[(0xefb+2962-0x1a8d)]=
zd1edcde5e1;data[(0x4fd+8122-0x24b6)]=z7b058c25be;data[(0x171+6064-0x191f)]=
z6e0310fb34;data[(0x57f+359-0x6e3)]=z46565b3777;
}zc996524f70::zc996524f70(const float z37ef40bf5d[(0x104f+1335-0x1582)]){data[
(0x1429+3890-0x235b)]=z37ef40bf5d[(0x2362+400-0x24f2)];data[(0x1d43+1437-0x22df)
]=z37ef40bf5d[(0x4f6+7996-0x2431)];data[(0x130+485-0x313)]=z37ef40bf5d[
(0xd7b+4053-0x1d4e)];data[(0x41f+1733-0xae1)]=z37ef40bf5d[(0x80c+4865-0x1b0a)];
}zc996524f70::zc996524f70(const zc996524f70&q){data[(0x918+2213-0x11bd)]=q(
(0xe53+5808-0x2503));data[(0x1797+2701-0x2223)]=q((0xba+5234-0x152b));data[
(0x15bd+3447-0x2332)]=q((0xb33+1758-0x120f));data[(0x85d+4376-0x1972)]=q(
(0x561+7840-0x23fe));
}zc996524f70::zc996524f70(const z43c30c772b&z37ef40bf5d){
zc8c9b1ff2a(z37ef40bf5d);}zc996524f70::zc996524f70(float a,float b,float g){
zc8c9b1ff2a(a,b,g);}zc996524f70::zc996524f70(float z6fafebb892,const z43c30c772b
&z7bd9fa8427){
zd55d782e18(z6fafebb892,z7bd9fa8427);}zc996524f70::zc996524f70(const z43c30c772b
&zbaa067b922,const z43c30c772b&z8a33818460){z083379063a(zbaa067b922,z8a33818460)
;}zc996524f70::~zc996524f70(){}void zc996524f70::zc8c9b1ff2a(float a,float b,
float g){
zc996524f70 z576521bde7(a,z43c30c772b(1.0f,0.0f,0.0f));zc996524f70 z18f6d1cca1(b
,z43c30c772b(0.0f,1.0f,0.0f));zc996524f70 z04175f5a1e(g,z43c30c772b(0.0f,0.0f,
1.0f));(*this)=z576521bde7*z18f6d1cca1*z04175f5a1e;}void zc996524f70::
zc8c9b1ff2a(const z43c30c772b&z37ef40bf5d){
zc8c9b1ff2a(z37ef40bf5d((0x114+4247-0x11ab)),z37ef40bf5d((0x25a4+221-0x2680)),
z37ef40bf5d((0xa3d+5433-0x1f74)));}void zc996524f70::zd55d782e18(float 
z6fafebb892,const z43c30c772b&z7bd9fa8427){
z43c30c772b zdea1f0b8f1=z7bd9fa8427;zdea1f0b8f1.normalize();float z20bf81b2cb=(
float)sin(z6fafebb892/2.0f);data[(0xe1f+5963-0x2569)]=zdea1f0b8f1(
(0x801+2365-0x113e))*z20bf81b2cb;data[(0xea6+3994-0x1e3e)]=zdea1f0b8f1(
(0x1084+602-0x12dd))*z20bf81b2cb;data[(0xcea+398-0xe75)]=zdea1f0b8f1(
(0x6eb+4573-0x18c6))*z20bf81b2cb;data[(0x16e6+325-0x182b)]=(float)cos(
z6fafebb892/2.0f);}void zc996524f70::z083379063a(const z43c30c772b&zbaa067b922,
const z43c30c772b&z8a33818460){z43c30c772b zd1edcde5e1(zbaa067b922.zce732648bf()
);z43c30c772b z7b058c25be(z8a33818460.zce732648bf());z43c30c772b zff27107b40(
zd1edcde5e1^z7b058c25be);float zb51a0aa7fe=zd1edcde5e1*z7b058c25be;if(
zb51a0aa7fe>1.0f)z8079139e84();else zd55d782e18(z16efbd9f9a::zca43de2d36(
zb51a0aa7fe),zff27107b40);}zc996524f70 zc996524f70::z17fc270567()const{
zc996524f70 zd094a88178;zc996524f70 z9aabdad99d(*this);if(z9aabdad99d(
(0x4c6+400-0x656))<0.0f)
z9aabdad99d=z9aabdad99d*-1.0f;float l=sqrtf(z9aabdad99d((0x18a7+2006-0x207d))*
z9aabdad99d((0xbcc+4751-0x1e5b))+z9aabdad99d((0x159b+1268-0x1a8e))*z9aabdad99d(
(0x379+6173-0x1b95))+z9aabdad99d((0x73a+4835-0x1a1b))*z9aabdad99d(
(0x8c8+5151-0x1ce5))+z9aabdad99d((0xf+5272-0x14a4))*z9aabdad99d(
(0x1af+672-0x44c)));float z0f5f967b5a=z9aabdad99d((0x496+4965-0x17fb))/l;
if(z0f5f967b5a>1.0f)
z0f5f967b5a=1.0f;zd094a88178((0xeb3+2540-0x189f))=z16efbd9f9a::zca43de2d36(
z0f5f967b5a)*2.0f;float z20bf81b2cb=sqrtf(1.0f-z0f5f967b5a*z0f5f967b5a);if(fabs(
z20bf81b2cb)<0.00005f)z20bf81b2cb=1.0f;else z20bf81b2cb*=l;
zd094a88178((0xc27+5046-0x1fdc))=z9aabdad99d((0xf91+3923-0x1ee3))/z20bf81b2cb;
zd094a88178((0x40c+2947-0xf8d))=z9aabdad99d((0xa55+6107-0x222e))/z20bf81b2cb;
zd094a88178((0x133a+1113-0x1790))=z9aabdad99d((0x1903+3136-0x2540))/z20bf81b2cb;
return(zd094a88178);}zc996524f70 zc996524f70::zebae1d77fd()const{
zc996524f70 zd094a88178;zc996524f70 z9aabdad99d(*this);if(z9aabdad99d(
(0xb82+2020-0x1366))<0.0f)
z9aabdad99d=z9aabdad99d*-1.0f;float l=sqrtf(z9aabdad99d((0x2153+1000-0x253b))*
z9aabdad99d((0x1a4f+2544-0x243f))+z9aabdad99d((0x59d+1190-0xa42))*z9aabdad99d(
(0x7f+8557-0x21eb))+z9aabdad99d((0x716+4664-0x194c))*z9aabdad99d(
(0x20c0+338-0x2210))+z9aabdad99d((0xd44+5803-0x23ec))*z9aabdad99d(
(0xc3+8455-0x21c7)));float z0f5f967b5a=z9aabdad99d((0x1004+2033-0x17f5))/l;
if(z0f5f967b5a>1.0f)
z0f5f967b5a=1.0f;zd094a88178((0x101f+1153-0x14a0))=acos(z0f5f967b5a)*2.0f;float 
z20bf81b2cb=sqrtf(1.0f-z0f5f967b5a*z0f5f967b5a);if(fabs(z20bf81b2cb)<0.00005f)
z20bf81b2cb=1.0f;else z20bf81b2cb*=l;
zd094a88178((0x488+1375-0x9e6))=z9aabdad99d((0xa80+1384-0xfe7))/z20bf81b2cb;
zd094a88178((0x9ac+734-0xc88))=z9aabdad99d((0x1cbb+994-0x209b))/z20bf81b2cb;
zd094a88178((0x9f+2496-0xa5c))=z9aabdad99d((0x4b4+3344-0x11c1))/z20bf81b2cb;
return(zd094a88178);}z43c30c772b zc996524f70::z5bc3f5e12e()const{
return(zc48c746a21().z5bc3f5e12e());}float zc996524f70::zc5c0ff5e64(const 
zc996524f70&q){float z6fafebb892=fabs(data[(0x34f+5197-0x179c)]*q(
(0xec5+6007-0x263c))+data[(0x6c3+4239-0x1751)]*q((0x191+6061-0x193d))+data[
(0xc9b+3771-0x1b54)]*q((0x1526+4206-0x2592))+data[(0x12e3+2645-0x1d35)]*q(
(0x5a7+1146-0xa1e)));return(z16efbd9f9a::zca43de2d36(z6fafebb892)*2.0f);}void 
zc996524f70::z4174ee2a49(const zc996524f70&z0755af5496,const zc996524f70&
z8930959f0b,float t){zc996524f70 zf3a5916c7a(z0755af5496);zc996524f70 BB(
z8930959f0b);if(zf3a5916c7a((0xbb+7164-0x1cb7))*BB((0x70d+6352-0x1fdd))+
zf3a5916c7a((0x900+5935-0x202e))*BB((0x177f+354-0x18e0))+zf3a5916c7a(
(0xf02+579-0x1143))*BB((0x1212+2080-0x1a30))+zf3a5916c7a((0x95a+4239-0x19e6))*BB
((0x194b+1073-0x1d79))<0.0f)zf3a5916c7a=zf3a5916c7a*-1.0f;zc996524f70 r((
zf3a5916c7a.z2a56b020d9()*BB).z17fc270567());(*this)=(zf3a5916c7a*zc996524f70(r(
(0x616+4877-0x1923))*t,z43c30c772b(r((0x197+8056-0x210e)),r((0xeb8+834-0x11f8)),
r((0x54f+8496-0x267c)))));
}const zc996524f70 zc996524f70::z6dbe01008c(1.0f,0.0f,0.0f,0.0f);
