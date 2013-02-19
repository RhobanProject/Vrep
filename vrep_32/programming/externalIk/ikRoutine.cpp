
#include "v_repConst.h"
#include "Global.h"
#include "ikRoutine.h"
#include "Ct.h"
#include "Tt.h"
void z5c6e7d2910::ze1080bf4de(zefb78627df&z8a12d87841,zefb78627df&za0a5e46f06,
int z93438c6aa1,std::vector<zefb78627df*>&z77d193addf){









zefb78627df&za24320f37a=*z77d193addf[(0x19c3+2679-0x243a)];zefb78627df 
z1790eb4e40(za24320f37a);za24320f37a=z8a12d87841*z1790eb4e40;for(int i=
(0x696+2614-0x10cb);i<int(z77d193addf.size());i++)(*z77d193addf[i])=z8a12d87841*
(*z77d193addf[i]);if((z93438c6aa1>(0x46a+7231-0x20a9))&&(z93438c6aa1<int(
z77d193addf.size()))){zefb78627df zf667805127(za0a5e46f06*z1790eb4e40);(*
z77d193addf[z93438c6aa1])+=zf667805127;}}void z5c6e7d2910::zdfd7cbf487(
zefb78627df&z8a12d87841,zefb78627df&za0a5e46f06,float zbcc5a13f4a){z8a12d87841.
z8079139e84();za0a5e46f06.clear();za0a5e46f06((0x39a+2446-0xd28),
(0x1b57+235-0x1c41))=-1.0f;za0a5e46f06((0x1a1+3279-0xe6f),(0x1e6+2114-0xa28))=
1.0f;za0a5e46f06((0x1460+2486-0x1e14),(0xa5d+2744-0x1512))=zbcc5a13f4a;}void 
z5c6e7d2910::z38a1421cc7(zefb78627df&z8a12d87841,zefb78627df&za0a5e46f06){
z8a12d87841.z8079139e84();za0a5e46f06.clear();za0a5e46f06((0x133b+1516-0x1925),
(0xb91+3519-0x194d))=1.0f;}z957fc62c41*z5c6e7d2910::zddb2a33afa(zdc525f1a83*
z24169aa90e,z38505d4d88&z02a953a4c1,std::vector<int>*z5ef93ef1c5,std::vector<int
>*zb2002cb32a){






z697f571449*zfe46901f65=z87df41beda::z935b5aba45->z4cdd500443(z24169aa90e->
zef20b87497());if(zfe46901f65==NULL){
z24169aa90e->zcb111aef6b(false);return(NULL);}zbc00b3c1a7*base=z87df41beda::
z935b5aba45->zad59a48cc3(z24169aa90e->zc899e59d20());if((base!=NULL)&&(!
zfe46901f65->z6d1a1b4e60(base))){
z24169aa90e->za840da2d15(-(0x1240+2939-0x1dba));z24169aa90e->zcb111aef6b(false);
return(NULL);}
zbc00b3c1a7*z9b21b8bbb2=zfe46901f65;int z22d600ab59=(0x15b0+828-0x18ec);while(
z9b21b8bbb2!=base){z9b21b8bbb2=z9b21b8bbb2->zfeb40b2026();if((z9b21b8bbb2!=NULL)
&&(z9b21b8bbb2!=base)){if(z9b21b8bbb2->z59ecca4dfc()==sim_object_joint_type){if(
(((zcf0f3da7c0*)z9b21b8bbb2)->zf847780e9c()==sim_jointmode_ik)||(((zcf0f3da7c0*)
z9b21b8bbb2)->zf847780e9c()==sim_jointmode_ikdependent)){int z9aabdad99d=((
zcf0f3da7c0*)z9b21b8bbb2)->z9a988f2392();for(int i=z9aabdad99d-
(0x14d+9160-0x2514);i>=(0xed+1146-0x567);i--){if(z5ef93ef1c5!=NULL){z5ef93ef1c5
->push_back(z9b21b8bbb2->z9890051730());zb2002cb32a->push_back(i);}}z22d600ab59
+=z9aabdad99d;}}}}z957fc62c41*J=new z957fc62c41((0xdc9+998-0x11a9),(unsigned 
char)z22d600ab59);std::vector<zefb78627df*>z5f57236085;for(int i=
(0xadf+2930-0x1651);i<(z22d600ab59+(0x4f7+5847-0x1bcd));i++){zefb78627df*
zb3c1343172=new zefb78627df();if(i==(0x153+8095-0x20f2))(*zb3c1343172).
z8079139e84();else(*zb3c1343172).clear();z5f57236085.push_back(zb3c1343172);}
z9b21b8bbb2=zfe46901f65;zefb78627df zaadb14acda;zaadb14acda.z8079139e84();int 
z1d36242bc2=(0x1648+4005-0x25ed);zefb78627df z8a12d87841;zefb78627df za0a5e46f06
;zefb78627df zc240a3ba24;zcf0f3da7c0*z2fbb229670=NULL;int z3432112eea=-
(0xed9+3760-0x1d88);int z3e002d2ae8=-(0x88+9863-0x270e);while(z9b21b8bbb2!=base)
{zbc00b3c1a7*z005c0321c5=z9b21b8bbb2->zfeb40b2026();zcab2ae559c za7392ab5a4;if(
z9b21b8bbb2->z59ecca4dfc()==sim_object_joint_type){if((((zcf0f3da7c0*)
z9b21b8bbb2)->zf847780e9c()!=sim_jointmode_ik)&&(((zcf0f3da7c0*)z9b21b8bbb2)->
zf847780e9c()!=sim_jointmode_ikdependent))za7392ab5a4=z9b21b8bbb2->z989dd8fa33(
true);else{zcf0f3da7c0*z839a645366=(zcf0f3da7c0*)z9b21b8bbb2;if(z839a645366->
zfb3b8778ca()==sim_joint_spherical_subtype){if(z3432112eea==-
(0x143c+2537-0x1e24))z3432112eea=z839a645366->z9a988f2392()-(0x13f+5083-0x1519);
z839a645366->zef9ebc18fb(za7392ab5a4,z3432112eea--,true);if(z3432112eea!=-
(0xabd+1783-0x11b3))z005c0321c5=z9b21b8bbb2;
}else za7392ab5a4=z9b21b8bbb2->z5dd63d5999(true);}}else za7392ab5a4=z9b21b8bbb2
->z989dd8fa33(true);zaadb14acda=zefb78627df(za7392ab5a4.zc48c746a21())*
zaadb14acda;z9b21b8bbb2=z005c0321c5;bool z5717a8947e=false;if(z9b21b8bbb2!=NULL)
{if(z9b21b8bbb2->z59ecca4dfc()==sim_object_joint_type)z5717a8947e=((((
zcf0f3da7c0*)z9b21b8bbb2)->zf847780e9c()==sim_jointmode_ik)||(((zcf0f3da7c0*)
z9b21b8bbb2)->zf847780e9c()==sim_jointmode_ikdependent));}if((z9b21b8bbb2==base)
||z5717a8947e){
if(z1d36242bc2==(0x16dd+1432-0x1c75)){
z8a12d87841=zaadb14acda;za0a5e46f06.clear();ze1080bf4de(z8a12d87841,za0a5e46f06,
(0x223c+617-0x24a5),z5f57236085);}else{
if(z2fbb229670->zfb3b8778ca()==sim_joint_revolute_subtype){zdfd7cbf487(
z8a12d87841,za0a5e46f06,z2fbb229670->zf5d1de8e1b());ze1080bf4de(z8a12d87841,
za0a5e46f06,z1d36242bc2,z5f57236085);zc240a3ba24.z82b593ca65(z2fbb229670->
z2bff4c64fe(true));}else if(z2fbb229670->zfb3b8778ca()==
sim_joint_prismatic_subtype){z38a1421cc7(z8a12d87841,za0a5e46f06);ze1080bf4de(
z8a12d87841,za0a5e46f06,z1d36242bc2,z5f57236085);zc240a3ba24.zd9b62f8bf4(0.0f,
0.0f,z2fbb229670->z2bff4c64fe(true));}else{
zdfd7cbf487(z8a12d87841,za0a5e46f06,0.0f);ze1080bf4de(z8a12d87841,za0a5e46f06,
z1d36242bc2,z5f57236085);if(z3e002d2ae8==-(0xa8d+983-0xe63))z3e002d2ae8=
z2fbb229670->z9a988f2392()-(0xfd+3083-0xd07);zc240a3ba24.z82b593ca65(z2fbb229670
->z9aa1e0129e(z3e002d2ae8--));}z8a12d87841=zaadb14acda*zc240a3ba24;za0a5e46f06.
clear();ze1080bf4de(z8a12d87841,za0a5e46f06,(0x39b+5761-0x1a1c),z5f57236085);}
zaadb14acda.z8079139e84();z2fbb229670=(zcf0f3da7c0*)z9b21b8bbb2;z1d36242bc2++;}}
int z60fdd0dc02=z24169aa90e->z8dd442ee7a();if(z60fdd0dc02!=-(0x1003+1574-0x1628)
){z697f571449*ze41cf0ccb0=z87df41beda::z935b5aba45->z4cdd500443(z60fdd0dc02);if(
ze41cf0ccb0!=NULL){
zcab2ae559c z93e0ea6e13(ze41cf0ccb0->z253df73c29(true));zcab2ae559c zae7035cd63;
zae7035cd63.z8079139e84();if(base!=NULL)zae7035cd63=base->z48768ee0bb(true);
zefb78627df zafd3339d03((z93e0ea6e13.z2a56b020d9()*zae7035cd63).zc48c746a21());
za0a5e46f06.clear();ze1080bf4de(zafd3339d03,za0a5e46f06,(0x18d2+617-0x1b3b),
z5f57236085);}}
for(int i=(0x1567+3338-0x2271);i<z22d600ab59;i++){(*J)((0x1480+2160-0x1cf0),i)=(
*z5f57236085[(0x1db7+153-0x1e4f)+i])((0x179a+2649-0x21f3),(0x5bd+608-0x81a));(*J
)((0x25a+8486-0x237f),i)=(*z5f57236085[(0xbb+7176-0x1cc2)+i])(
(0xc29+3037-0x1805),(0x1223+166-0x12c6));(*J)((0x11a4+860-0x14fe),i)=(*
z5f57236085[(0x78d+1651-0xdff)+i])((0x1a16+2294-0x230a),(0x1458+3405-0x21a2));}
for(int i=(0x2da+1955-0xa7d);i<z22d600ab59;i++)(*z5f57236085[(0x561+1978-0xd1a)+
i])/=zbf63b2c3c4;
for(int i=(0x1709+1249-0x1bea);i<z22d600ab59;i++)(*z5f57236085[
(0x1892+2541-0x227e)+i])+=(*z5f57236085[(0x1369+21-0x137e)]);
z02a953a4c1=(*z5f57236085[(0xa5b+1390-0xfc9)]);
zefb78627df zef52a4586c(*z5f57236085[(0x8c+5096-0x1474)]);zef52a4586c.
zad65bf3f95();zefb78627df z52754d10b7;
for(int i=(0x1050+4559-0x221f);i<z22d600ab59;i++){z52754d10b7=zef52a4586c*(*
z5f57236085[(0x1664+2030-0x1e51)+i]);z43c30c772b z514e59275f(z52754d10b7.
z5bc3f5e12e());(*J)((0xca9+2362-0x15e0),i)=z514e59275f((0x7fd+984-0xbd5));(*J)(
(0xb84+2390-0x14d6),i)=z514e59275f((0x1c2b+2337-0x254b));(*J)(
(0xb2f+6885-0x260f),i)=z514e59275f((0x114+4944-0x1462));}








for(int i=(0x84+5370-0x157e);i<int(z5f57236085.size());i++)delete z5f57236085[i]
;return(J);}
