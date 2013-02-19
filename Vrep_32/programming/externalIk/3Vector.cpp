

#include "MyMath.h"
#include "3Vector.h"
#include "3X3Matrix.h"
#include "4X4Matrix.h"
#include "7Vector.h"
z43c30c772b::z43c30c772b(){}z43c30c772b::z43c30c772b(float zd1edcde5e1,float 
z7b058c25be,float z6e0310fb34){data[(0x389+7525-0x20ee)]=zd1edcde5e1;data[
(0x466+4633-0x167e)]=z7b058c25be;data[(0xc31+907-0xfba)]=z6e0310fb34;}
z43c30c772b::z43c30c772b(const float z37ef40bf5d[(0x725+5197-0x1b6f)]){data[
(0x1518+2780-0x1ff4)]=z37ef40bf5d[(0xe46+524-0x1052)];data[(0x595+2186-0xe1e)]=
z37ef40bf5d[(0xc3f+51-0xc71)];data[(0x48f+5685-0x1ac2)]=z37ef40bf5d[
(0x11cf+661-0x1462)];}z43c30c772b::z43c30c772b(const z43c30c772b&z37ef40bf5d){(*
this)=z37ef40bf5d;}z43c30c772b::~z43c30c772b(){}float z43c30c772b::z6f55e083ba(
const z43c30c772b&z37ef40bf5d)const{
z43c30c772b a(zce732648bf());z43c30c772b b(z37ef40bf5d.zce732648bf());return(
z16efbd9f9a::zca43de2d36(a*b));}ze2b7e09268 z43c30c772b::z6a5f3da250()const{
ze2b7e09268 zc025341aa2;zc025341aa2((0x17ab+3398-0x24f1),(0x48d+7309-0x211a))=
0.0f;zc025341aa2((0x23ad+704-0x266d),(0x18b1+2527-0x228f))=-data[
(0xee4+2256-0x17b2)];zc025341aa2((0x355+3971-0x12d8),(0x85f+3262-0x151b))=data[
(0x1875+1638-0x1eda)];zc025341aa2((0xd5f+3489-0x1aff),(0x8dc+6271-0x215b))=data[
(0x99f+1522-0xf8f)];zc025341aa2((0x42+3308-0xd2d),(0xcf0+2017-0x14d0))=0.0f;
zc025341aa2((0xfab+509-0x11a7),(0x3d2+7879-0x2297))=-data[(0x1385+3613-0x21a2)];
zc025341aa2((0xc3b+3249-0x18ea),(0x95f+5250-0x1de1))=-data[(0x14a+3360-0xe69)];
zc025341aa2((0x11f9+1495-0x17ce),(0xaa6+4661-0x1cda))=data[(0x560+4888-0x1878)];
zc025341aa2((0x82f+735-0xb0c),(0x73d+6562-0x20dd))=0.0f;return(zc025341aa2);}
void z43c30c772b::operator*=(const z38505d4d88&zcec140f672){
float x=data[(0x369+2057-0xb72)];float y=data[(0xadb+3053-0x16c7)];float 
zf4af1ac000=data[(0x574+1577-0xb9b)];data[(0xdf7+4338-0x1ee9)]=zcec140f672.M.
z7bd9fa8427[(0xc17+1867-0x1362)].data[(0xcfd+4127-0x1d1c)]*x+zcec140f672.M.
z7bd9fa8427[(0xad1+5475-0x2033)].data[(0x1635+3779-0x24f8)]*y+zcec140f672.M.
z7bd9fa8427[(0xcb4+6265-0x252b)].data[(0x4b3+1230-0x981)]*zf4af1ac000+
zcec140f672.X.data[(0x332+1602-0x974)];data[(0xd48+6552-0x26df)]=zcec140f672.M.
z7bd9fa8427[(0x40a+5237-0x187f)].data[(0xaa+5445-0x15ee)]*x+zcec140f672.M.
z7bd9fa8427[(0x787+2544-0x1176)].data[(0x1809+3706-0x2682)]*y+zcec140f672.M.
z7bd9fa8427[(0x1ced+1622-0x2341)].data[(0xdfc+2064-0x160b)]*zf4af1ac000+
zcec140f672.X.data[(0x1249+2139-0x1aa3)];data[(0x10d7+4072-0x20bd)]=zcec140f672.
M.z7bd9fa8427[(0x6e6+7629-0x24b3)].data[(0x1132+2574-0x1b3e)]*x+zcec140f672.M.
z7bd9fa8427[(0x629+6120-0x1e10)].data[(0xa5f+1062-0xe83)]*y+zcec140f672.M.
z7bd9fa8427[(0x14dc+2630-0x1f20)].data[(0x1a85+775-0x1d8a)]*zf4af1ac000+
zcec140f672.X.data[(0x8db+4206-0x1947)];}void z43c30c772b::operator*=(const 
ze2b7e09268&zcec140f672){
float x=data[(0xe41+5581-0x240e)];float y=data[(0xbf+8281-0x2117)];float 
zf4af1ac000=data[(0x648+4502-0x17dc)];data[(0x1e0+4861-0x14dd)]=zcec140f672.
z7bd9fa8427[(0x1b45+956-0x1f01)].data[(0x171c+2886-0x2262)]*x+zcec140f672.
z7bd9fa8427[(0x160a+3408-0x2359)].data[(0xae1+3714-0x1963)]*y+zcec140f672.
z7bd9fa8427[(0x4d+6504-0x19b3)].data[(0x1970+3163-0x25cb)]*zf4af1ac000;data[
(0x955+6988-0x24a0)]=zcec140f672.z7bd9fa8427[(0xb0d+1989-0x12d2)].data[
(0xf+1331-0x541)]*x+zcec140f672.z7bd9fa8427[(0x17c+7467-0x1ea6)].data[
(0xe94+2061-0x16a0)]*y+zcec140f672.z7bd9fa8427[(0x368+233-0x44f)].data[
(0xd05+1264-0x11f4)]*zf4af1ac000;data[(0x150a+54-0x153e)]=zcec140f672.
z7bd9fa8427[(0x1e1a+964-0x21de)].data[(0x7f4+600-0xa4a)]*x+zcec140f672.
z7bd9fa8427[(0xc0a+2342-0x152f)].data[(0xe3b+212-0xf0d)]*y+zcec140f672.
z7bd9fa8427[(0xb90+6019-0x2311)].data[(0xf85+5990-0x26e9)]*zf4af1ac000;}void 
z43c30c772b::operator*=(const zcab2ae559c&zf2dc2f6435){(*this)=zf2dc2f6435*(*
this);}void z43c30c772b::z4174ee2a49(const z43c30c772b&z0755af5496,const 
z43c30c772b&z8930959f0b,float t){(*this)=z0755af5496+((z8930959f0b-z0755af5496)*
t);}const z43c30c772b z43c30c772b::z4527e069a3(1.0f,1.0f,1.0f);const z43c30c772b
 z43c30c772b::z7e831c1eef(1.0f,0.0f,0.0f);const z43c30c772b z43c30c772b::
z289057c4d7(0.0f,1.0f,0.0f);const z43c30c772b z43c30c772b::zaebd0fb77e(0.0f,0.0f
,1.0f);const z43c30c772b z43c30c772b::z69267038d3(0.0f,0.0f,0.0f);
