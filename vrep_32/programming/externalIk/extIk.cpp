
#include "extIk.h"
#include "Ct.h"
#include "v_repConst.h"
bool z2f54b4c83a(){return(z87df41beda::z4f12258ca0()>(0x3a4+1192-0x84c));}bool 
simEmbLaunch(){if(z2f54b4c83a())return(false);z87df41beda::zf63b8cf8e3(false);
return(true);}bool simEmbShutDown(){if(!z2f54b4c83a())return(false);z87df41beda
::z5dc6f2a7d5();
return(true);}int simEmbStart(unsigned char*data,int zbcc648e4da){if(!
z2f54b4c83a())return(-(0x8ec+6955-0x2416));if((data==NULL)||(zbcc648e4da==
(0x15e1+835-0x1924)))return(-(0x85f+1503-0xe3d));z2966f2073e zc035e59036(data,
zbcc648e4da);z87df41beda::z935b5aba45->zd38163d75f(zc035e59036);return(int(
z87df41beda::z935b5aba45->zf046ac2fe8.size()));}int simEmbGetObjectHandle(const 
char*z69667e4ade){if(!z2f54b4c83a())return(-(0x1402+3385-0x213a));zbc00b3c1a7*
z839a645366=z87df41beda::z935b5aba45->zad59a48cc3(z69667e4ade);if(z839a645366==
NULL)return(-(0x4df+7504-0x222e));return(z839a645366->z9890051730());}int 
simEmbGetObjectTransformation(int objectHandle,int z5abe23e514,float*z7f087d2eed
,float*za6ed841c4e){if(!z2f54b4c83a())return(-(0xcc8+3925-0x1c1c));

zbc00b3c1a7*z839a645366=z87df41beda::z935b5aba45->zad59a48cc3(objectHandle);if(
z839a645366==NULL)return(-(0x453+6119-0x1c39));if(z5abe23e514==sim_handle_parent
){z5abe23e514=-(0x188b+166-0x1930);zbc00b3c1a7*zfe0c1f25c1=z839a645366->
zfeb40b2026();if(zfe0c1f25c1!=NULL)z5abe23e514=zfe0c1f25c1->z9890051730();}
zbc00b3c1a7*z222566c220=z87df41beda::z935b5aba45->zad59a48cc3(z5abe23e514);if(
z5abe23e514!=-(0x1518+26-0x1531)){if(z222566c220==NULL)return(-
(0x697+2092-0xec2));}zcab2ae559c zec880c2e91;if(z5abe23e514==-
(0x1cf+9533-0x270b))zec880c2e91=z839a645366->z253df73c29();else{zcab2ae559c 
z57a435ce21(z222566c220->z253df73c29());
zec880c2e91=z57a435ce21.z2a56b020d9()*z839a645366->z253df73c29();
}za6ed841c4e[(0xd34+1784-0x142c)]=zec880c2e91.Q((0xaa3+18-0xab4));za6ed841c4e[
(0x914+3025-0x14e4)]=zec880c2e91.Q((0xe35+4449-0x1f94));za6ed841c4e[
(0x1e6b+1517-0x2456)]=zec880c2e91.Q((0xd63+2338-0x1682));za6ed841c4e[
(0xf6b+4498-0x20fa)]=zec880c2e91.Q((0xf4a+4351-0x2049));z7f087d2eed[
(0x6e3+4606-0x18e1)]=zec880c2e91.X((0x3dd+942-0x78b));z7f087d2eed[
(0x155+3969-0x10d5)]=zec880c2e91.X((0x33a+6018-0x1abb));z7f087d2eed[
(0x620+5241-0x1a97)]=zec880c2e91.X((0x1bd5+634-0x1e4d));return(
(0xc36+3881-0x1b5e));}int simEmbSetObjectTransformation(int objectHandle,int 
z5abe23e514,const float*z7f087d2eed,const float*za6ed841c4e){if(!z2f54b4c83a())
return(-(0x1845+2282-0x212e));

zbc00b3c1a7*z839a645366=z87df41beda::z935b5aba45->zad59a48cc3(objectHandle);if(
z839a645366==NULL)return(-(0x533+3063-0x1129));if(z5abe23e514==sim_handle_parent
){z5abe23e514=-(0xbd0+3203-0x1852);zbc00b3c1a7*zfe0c1f25c1=z839a645366->
zfeb40b2026();if(zfe0c1f25c1!=NULL)z5abe23e514=zfe0c1f25c1->z9890051730();}
zbc00b3c1a7*z222566c220=z87df41beda::z935b5aba45->zad59a48cc3(z5abe23e514);if(
z5abe23e514!=-(0xedf+5571-0x24a1)){if(z222566c220==NULL)return(-(0x8c+830-0x3c9)
);}if(z5abe23e514==-(0x1650+923-0x19ea)){zcab2ae559c zec880c2e91;zec880c2e91.Q(
(0x149f+1828-0x1bc3))=za6ed841c4e[(0x1c93+380-0x1e0c)];zec880c2e91.Q(
(0xd3d+992-0x111c))=za6ed841c4e[(0x1956+3320-0x264e)];zec880c2e91.Q(
(0x159f+2522-0x1f77))=za6ed841c4e[(0x36a+2313-0xc72)];zec880c2e91.Q(
(0x508+5484-0x1a71))=za6ed841c4e[(0x507+7628-0x22d1)];zec880c2e91.X(
(0x144d+67-0x1490))=z7f087d2eed[(0xd20+1876-0x1474)];zec880c2e91.X(
(0xb8b+1810-0x129c))=z7f087d2eed[(0x9b0+3862-0x18c5)];zec880c2e91.X(
(0xb46+6773-0x25b9))=z7f087d2eed[(0x15f9+3674-0x2451)];z87df41beda::z935b5aba45
->z01e813ee2f(z839a645366->z9890051730(),zec880c2e91,false);}else{zcab2ae559c 
z5413e82d98(z839a645366->z253df73c29());zcab2ae559c z57a435ce21(z222566c220->
z253df73c29());
zcab2ae559c x(z57a435ce21.z2a56b020d9()*z5413e82d98);x.Q((0xd5c+878-0x10ca))=
za6ed841c4e[(0x6a+8532-0x21bb)];x.Q((0x1119+2028-0x1904))=za6ed841c4e[
(0x1d31+2111-0x2570)];x.Q((0x1a4d+47-0x1a7a))=za6ed841c4e[(0x27c+759-0x572)];x.Q
((0xfb8+2548-0x19a9))=za6ed841c4e[(0x7a2+276-0x8b4)];x.X((0x1448+1462-0x19fe))=
z7f087d2eed[(0xe18+224-0xef8)];x.X((0x15b1+1284-0x1ab4))=z7f087d2eed[
(0x3e2+3536-0x11b1)];x.X((0x1563+4127-0x2580))=z7f087d2eed[(0xa07+3922-0x1957)];
z5413e82d98=z57a435ce21*x;z87df41beda::z935b5aba45->z01e813ee2f(z839a645366->
z9890051730(),z5413e82d98,false);}return((0x103f+1330-0x1570));}int 
simEmbGetJointPosition(int z8d5c1bae27,float*z7f087d2eed){if(!z2f54b4c83a())
return(-(0x1276+3357-0x1f92));zcf0f3da7c0*z839a645366=z87df41beda::z935b5aba45->
z9a24f554a0(z8d5c1bae27);if(z839a645366==NULL)return(-(0xbd5+6872-0x26ac));if(
z839a645366->zfb3b8778ca()==sim_joint_spherical_subtype)return(-
(0x322+859-0x67c));z7f087d2eed[(0x121a+5173-0x264f)]=z839a645366->z2bff4c64fe();
return((0x127c+709-0x1540));}int simEmbSetJointPosition(int z8d5c1bae27,float 
z7f087d2eed){if(!z2f54b4c83a())return(-(0x192+1032-0x599));zcf0f3da7c0*
z839a645366=z87df41beda::z935b5aba45->z9a24f554a0(z8d5c1bae27);if(z839a645366==
NULL)return(-(0xea3+952-0x125a));if(z839a645366->zfb3b8778ca()==
sim_joint_spherical_subtype)return(-(0x714+6870-0x21e9));z839a645366->
z1c5ae67dc1(z7f087d2eed);return((0x1507+815-0x1835));}int simEmbGetIkGroupHandle
(const char*zd68a480985){if(!z2f54b4c83a())return(-(0xb86+5799-0x222c));
z81a8e195d8*z839a645366=z87df41beda::zada844b223->zdee3818214(zd68a480985);if(
z839a645366==NULL)return(-(0x1aeb+355-0x1c4d));return(z839a645366->z72930d41ef()
);}int simEmbHandleIkGroup(int z25830ea86b){if(!z2f54b4c83a())return(-
(0x122c+4416-0x236b));z81a8e195d8*z839a645366=z87df41beda::zada844b223->
zdee3818214(z25830ea86b);if((z25830ea86b!=sim_handle_all)&&(z25830ea86b!=
sim_handle_all_except_explicit)){if(z839a645366==NULL)return(-(0xe3+5298-0x1594)
);}int z0a02a87b66=(0x619+7084-0x21c5);if(z25830ea86b<(0xef9+4030-0x1eb7))
z0a02a87b66=z87df41beda::zada844b223->z4850d10761(z25830ea86b==
sim_handle_all_except_explicit);else{
if(!z839a645366->z9db8ac7846())return(-(0x13b5+187-0x146f));z0a02a87b66=
z839a645366->z52e987711e();}return(z0a02a87b66);}int 
simEmbQuaternionToEulerAngles(const float*za6ed841c4e,float*z514e59275f){if(!
z2f54b4c83a())return(-(0xf98+594-0x11e9));

zc996524f70 q(za6ed841c4e[(0x1aff+810-0x1e26)],za6ed841c4e[(0x171c+2651-0x2177)]
,za6ed841c4e[(0x10c+1578-0x735)],za6ed841c4e[(0x3da+1083-0x813)]);z43c30c772b 
za42588c30d(q.z5bc3f5e12e());z514e59275f[(0x21c+19-0x22f)]=za42588c30d(
(0xdcb+3665-0x1c1c));z514e59275f[(0x8ef+5438-0x1e2c)]=za42588c30d(
(0x137+6064-0x18e6));z514e59275f[(0x787+7581-0x2522)]=za42588c30d(
(0x23f+3553-0x101e));return((0x1688+2599-0x20ae));}int 
simEmbEulerAnglesToQuaternion(const float*z514e59275f,float*za6ed841c4e){if(!
z2f54b4c83a())return(-(0xa81+1049-0xe99));

zc996524f70 q(z514e59275f[(0x854+3144-0x149c)],z514e59275f[(0x44+5250-0x14c5)],
z514e59275f[(0x168a+542-0x18a6)]);za6ed841c4e[(0x8c8+6593-0x2289)]=q(
(0x10ea+3913-0x2032));za6ed841c4e[(0x2dd+1193-0x785)]=q((0x153f+3538-0x230f));
za6ed841c4e[(0x635+8102-0x25d9)]=q((0xf5+1046-0x508));za6ed841c4e[
(0x7af+7017-0x2315)]=q((0xd42+943-0x10f1));return((0xaf4+1184-0xf93));}int 
simEmbGetJointTransformation(int z8d5c1bae27,float*z7f087d2eed,float*za6ed841c4e
){if(!z2f54b4c83a())return(-(0x1b69+2713-0x2601));

zcf0f3da7c0*z839a645366=z87df41beda::z935b5aba45->z9a24f554a0(z8d5c1bae27);if(
z839a645366==NULL)return(-(0x3df+8431-0x24cd));zcab2ae559c za4308025da(
z839a645366->z989dd8fa33());zcab2ae559c zda62005a96(z839a645366->z5dd63d5999());
zcab2ae559c zec880c2e91(zda62005a96.z2a56b020d9()*za4308025da);za6ed841c4e[
(0x1687+31-0x16a6)]=zec880c2e91.Q((0x162+2140-0x9bd));za6ed841c4e[
(0x49d+3257-0x1155)]=zec880c2e91.Q((0x145f+4156-0x2499));za6ed841c4e[
(0x48+5945-0x177f)]=zec880c2e91.Q((0x5da+5409-0x1af8));za6ed841c4e[
(0x208+665-0x49e)]=zec880c2e91.Q((0x178f+1777-0x1e80));z7f087d2eed[
(0x59b+4435-0x16ee)]=zec880c2e91.X((0x2aa+3869-0x11c7));z7f087d2eed[
(0xc8c+1615-0x12da)]=zec880c2e91.X((0x356+2412-0xcc1));z7f087d2eed[
(0x8c6+1589-0xef9)]=zec880c2e91.X((0x43b+3054-0x1027));return(
(0xd90+2490-0x1749));}int simEmbSetSphericalJointQuaternion(int z8d5c1bae27,
const float*za6ed841c4e){if(!z2f54b4c83a())return(-(0x4bd+7905-0x239d));

zcf0f3da7c0*z839a645366=z87df41beda::z935b5aba45->z9a24f554a0(z8d5c1bae27);if(
z839a645366==NULL)return(-(0x84a+7823-0x26d8));if(z839a645366->zfb3b8778ca()!=
sim_joint_spherical_subtype)return(-(0x456+2343-0xd7c));zc996524f70 q;q(
(0x4e6+2264-0xdbe))=za6ed841c4e[(0x6a9+5785-0x1d3f)];q((0x1cb+5259-0x1655))=
za6ed841c4e[(0x975+779-0xc80)];q((0x173+2469-0xb16))=za6ed841c4e[
(0x81b+614-0xa80)];q((0x1107+1756-0x17e0))=za6ed841c4e[(0x35+6087-0x17fa)];
z839a645366->z61275fc1b1(q);return((0x21f4+436-0x23a7));}int 
simEmbGetObjectParent(int objectHandle){if(!z2f54b4c83a())return(-
(0x11f8+2316-0x1b02));zbc00b3c1a7*z839a645366=z87df41beda::z935b5aba45->
zad59a48cc3(objectHandle);if(z839a645366==NULL)return(-(0x4b4+3883-0x13dd));int 
retVal=-(0x1ec0+1053-0x22dc);if(z839a645366->zfeb40b2026()!=NULL)retVal=
z839a645366->zfeb40b2026()->z9890051730();return(retVal);}int 
simEmbSetObjectParent(int objectHandle,int ze95baeec09,bool za1d97354b3){if(!
z2f54b4c83a())return(-(0x1808+2548-0x21fb));zbc00b3c1a7*z839a645366=z87df41beda
::z935b5aba45->zad59a48cc3(objectHandle);zbc00b3c1a7*z862805a370=z87df41beda::
z935b5aba45->zad59a48cc3(ze95baeec09);if(z839a645366==NULL)return(-
(0xa3+5368-0x159a));if((z862805a370==NULL)&&(ze95baeec09!=-(0xaa2+7028-0x2615)))
return(-(0x958+7321-0x25f0));if(za1d97354b3)z87df41beda::z935b5aba45->
z4f08e8bd38(z839a645366,z862805a370);else z839a645366->z66b46386fb(z862805a370);
return((0x595+6319-0x1e43));}int simEmbInvertTransformation(float*z7f087d2eed,
float*za6ed841c4e){if(!z2f54b4c83a())return(-(0x2b0+8249-0x22e8));

zcab2ae559c zec880c2e91;zec880c2e91.Q((0x15a+4961-0x14bb))=za6ed841c4e[
(0x1474+2958-0x1fff)];zec880c2e91.Q((0x20db+150-0x2170))=za6ed841c4e[
(0x1346+383-0x14c5)];zec880c2e91.Q((0x12a5+3438-0x2011))=za6ed841c4e[
(0x1a0a+797-0x1d26)];zec880c2e91.Q((0x103f+4947-0x238f))=za6ed841c4e[
(0xf71+3381-0x1ca4)];zec880c2e91.X((0x325+2803-0xe18))=z7f087d2eed[
(0x649+2719-0x10e8)];zec880c2e91.X((0x2050+548-0x2273))=z7f087d2eed[
(0xdbc+1338-0x12f5)];zec880c2e91.X((0x40c+1671-0xa91))=z7f087d2eed[
(0x1b+9640-0x25c1)];zec880c2e91.z0d5a1d870e();za6ed841c4e[(0x1e31+1001-0x221a)]=
zec880c2e91.Q((0x2ac+6299-0x1b46));za6ed841c4e[(0x12cc+4763-0x2566)]=zec880c2e91
.Q((0xa8d+2552-0x1483));za6ed841c4e[(0xb6f+4044-0x1b39)]=zec880c2e91.Q(
(0x1642+3759-0x24ee));za6ed841c4e[(0x1302+3362-0x2021)]=zec880c2e91.Q(
(0x10c5+5293-0x2572));z7f087d2eed[(0x172c+1541-0x1d31)]=zec880c2e91.X(
(0x74c+7328-0x23ec));z7f087d2eed[(0xc09+6487-0x255f)]=zec880c2e91.X(
(0x2189+610-0x23ea));z7f087d2eed[(0x2a0+4579-0x1481)]=zec880c2e91.X(
(0x1676+1183-0x1b13));return((0x6f9+4195-0x175b));}int 
simEmbMultiplyTransformations(const float*z13c075ddec,const float*zbacec7b331,
const float*z795f2ae776,const float*zf31a4e3263,float*z30cd19bca2,float*
z75a31f0a6d){if(!z2f54b4c83a())return(-(0x108+5730-0x1769));

zcab2ae559c zc69be4e6cc;zc69be4e6cc.Q((0xeba+1343-0x13f9))=zbacec7b331[
(0xcf0+5005-0x207a)];zc69be4e6cc.Q((0x2d3+6886-0x1db8))=zbacec7b331[
(0x10f5+1806-0x1803)];zc69be4e6cc.Q((0x812+456-0x9d8))=zbacec7b331[
(0x853+6987-0x239d)];zc69be4e6cc.Q((0x768+5342-0x1c43))=zbacec7b331[
(0x2138+717-0x2403)];zc69be4e6cc.X((0x11f+1840-0x84f))=z13c075ddec[
(0x9fc+803-0xd1f)];zc69be4e6cc.X((0x5e6+3131-0x1220))=z13c075ddec[
(0x57c+7859-0x242e)];zc69be4e6cc.X((0x96c+3985-0x18fb))=z13c075ddec[
(0xedf+4682-0x2127)];zcab2ae559c z5c61edca16;z5c61edca16.Q((0x1a8a+699-0x1d45))=
zf31a4e3263[(0xc8f+41-0xcb5)];z5c61edca16.Q((0x71c+2799-0x120a))=zf31a4e3263[
(0xfd6+3595-0x1de1)];z5c61edca16.Q((0x8b3+3298-0x1593))=zf31a4e3263[
(0xdcd+3715-0x1c4f)];z5c61edca16.Q((0x152d+2719-0x1fc9))=zf31a4e3263[
(0x1f73+1455-0x2520)];z5c61edca16.X((0x15d+488-0x345))=z795f2ae776[
(0x659+7741-0x2496)];z5c61edca16.X((0xb0f+2887-0x1655))=z795f2ae776[
(0x4bc+5051-0x1876)];z5c61edca16.X((0x1fd+9011-0x252e))=z795f2ae776[
(0x8fd+4271-0x19aa)];zcab2ae559c ze5798f3d19(zc69be4e6cc*z5c61edca16);
z75a31f0a6d[(0x1774+2048-0x1f74)]=ze5798f3d19.Q((0x65d+2457-0xff5));z75a31f0a6d[
(0x387+4961-0x16e7)]=ze5798f3d19.Q((0x1c53+1516-0x223d));z75a31f0a6d[
(0xc07+4972-0x1f71)]=ze5798f3d19.Q((0x86d+5973-0x1fbf));z75a31f0a6d[
(0xced+5254-0x2170)]=ze5798f3d19.Q((0xa2c+1481-0xff5));z30cd19bca2[
(0x19c3+1392-0x1f33)]=ze5798f3d19.X((0xa8b+7219-0x26be));z30cd19bca2[
(0x435+4056-0x140c)]=ze5798f3d19.X((0x1ae9+1450-0x2092));z30cd19bca2[
(0x403+1841-0xb32)]=ze5798f3d19.X((0x4b1+892-0x82b));return((0x975+1658-0xfee));
}int simEmbInterpolateTransformations(const float*z13c075ddec,const float*
zbacec7b331,const float*z795f2ae776,const float*zf31a4e3263,float z26e4782e38,
float*z30cd19bca2,float*z75a31f0a6d){if(!z2f54b4c83a())return(-
(0x455+3491-0x11f7));

zcab2ae559c zc69be4e6cc;zc69be4e6cc.Q((0xad6+678-0xd7c))=zbacec7b331[
(0x12f0+1386-0x1857)];zc69be4e6cc.Q((0x47b+7427-0x217d))=zbacec7b331[
(0x17c1+522-0x19cb)];zc69be4e6cc.Q((0x20eb+1195-0x2594))=zbacec7b331[
(0x1244+3967-0x21c2)];zc69be4e6cc.Q((0x1668+3446-0x23db))=zbacec7b331[
(0x86+3973-0x1009)];zc69be4e6cc.X((0x1315+2743-0x1dcc))=z13c075ddec[
(0x222+1625-0x87b)];zc69be4e6cc.X((0x1aa0+716-0x1d6b))=z13c075ddec[
(0xdb3+5498-0x232c)];zc69be4e6cc.X((0x4b9+2009-0xc90))=z13c075ddec[
(0x840+7405-0x252b)];zcab2ae559c z5c61edca16;z5c61edca16.Q((0x1170+3266-0x1e32))
=zf31a4e3263[(0x1233+2457-0x1bc9)];z5c61edca16.Q((0x1050+4268-0x20fb))=
zf31a4e3263[(0x689+510-0x887)];z5c61edca16.Q((0x14bf+82-0x150f))=zf31a4e3263[
(0x27b+2673-0xceb)];z5c61edca16.Q((0xa91+4511-0x1c2d))=zf31a4e3263[
(0x169a+2395-0x1ff3)];z5c61edca16.X((0x1562+2908-0x20be))=z795f2ae776[
(0x1418+1375-0x1977)];z5c61edca16.X((0x14d0+3400-0x2217))=z795f2ae776[
(0x4d6+6096-0x1ca5)];z5c61edca16.X((0x239d+601-0x25f4))=z795f2ae776[
(0x237+3833-0x112e)];zcab2ae559c ze5798f3d19;ze5798f3d19.z4174ee2a49(zc69be4e6cc
,z5c61edca16,z26e4782e38);z75a31f0a6d[(0x7bf+4110-0x17cd)]=ze5798f3d19.Q(
(0x16bb+1701-0x1d5f));z75a31f0a6d[(0xe3d+1357-0x1389)]=ze5798f3d19.Q(
(0x1773+501-0x1966));z75a31f0a6d[(0x149d+3064-0x2093)]=ze5798f3d19.Q(
(0x182b+2054-0x202e));z75a31f0a6d[(0x97a+4308-0x1a4b)]=ze5798f3d19.Q(
(0x44f+8860-0x26eb));z30cd19bca2[(0x8c3+6711-0x22fa)]=ze5798f3d19.X(
(0x7db+5490-0x1d4d));z30cd19bca2[(0x1b31+2386-0x2482)]=ze5798f3d19.X(
(0x1250+1708-0x18fb));z30cd19bca2[(0x598+6048-0x1d36)]=ze5798f3d19.X(
(0x652+1267-0xb43));return((0xb86+1658-0x11ff));}int zabb6627f9b(const float*
z7f087d2eed,const float*za6ed841c4e,float*z512c33a2e9){if(!z2f54b4c83a())return(
-(0x1a3d+749-0x1d29));

zcab2ae559c zec880c2e91;zec880c2e91.Q((0x519+2001-0xcea))=za6ed841c4e[
(0xe98+2902-0x19eb)];zec880c2e91.Q((0x38a+8930-0x266b))=za6ed841c4e[
(0x1424+4043-0x23ef)];zec880c2e91.Q((0xa27+4375-0x1b3c))=za6ed841c4e[
(0x35c+989-0x738)];zec880c2e91.Q((0x3ec+3872-0x1309))=za6ed841c4e[
(0x9aa+4630-0x1bbe)];zec880c2e91.X((0x84c+3134-0x148a))=z7f087d2eed[
(0x62+7646-0x1e40)];zec880c2e91.X((0xcbf+3596-0x1aca))=z7f087d2eed[
(0xfd6+4166-0x201b)];zec880c2e91.X((0x110c+2967-0x1ca1))=z7f087d2eed[
(0x1a4d+551-0x1c72)];z43c30c772b z7b058c25be(z512c33a2e9);z43c30c772b 
z6e0310fb34(zec880c2e91*z7b058c25be);z512c33a2e9[(0x1d46+862-0x20a4)]=
z6e0310fb34((0xddd+2718-0x187b));z512c33a2e9[(0x1fe3+1250-0x24c4)]=z6e0310fb34(
(0x1f46+1481-0x250e));z512c33a2e9[(0x1102+2143-0x195f)]=z6e0310fb34(
(0x351+6612-0x1d23));return((0x14c9+2276-0x1dac));}int simEmbGetRotationAxis(
const float*z17d45360ea,const float*z972c99b192,float*z7bd9fa8427,float*
z6fafebb892){if(!z2f54b4c83a())return(-(0x874+6396-0x216f));

zc996524f70 zc64e9f3c3a;zc64e9f3c3a((0x221a+1142-0x2690))=z17d45360ea[
(0x1785+3939-0x26e5)];zc64e9f3c3a((0xd08+3208-0x198f))=z17d45360ea[
(0x5c7+6410-0x1ed1)];zc64e9f3c3a((0x14c8+1809-0x1bd7))=z17d45360ea[
(0x883+115-0x8f5)];zc64e9f3c3a((0x432+6545-0x1dc0))=z17d45360ea[
(0x428+2530-0xe08)];zc996524f70 z5a02f51a13;z5a02f51a13((0x2e5+4869-0x15ea))=
z972c99b192[(0x9db+1251-0xebb)];z5a02f51a13((0x1517+1566-0x1b34))=z972c99b192[
(0x204b+1470-0x2609)];z5a02f51a13((0x12b0+1553-0x18bf))=z972c99b192[
(0x1155+1487-0x1723)];z5a02f51a13((0xa93+1243-0xf6b))=z972c99b192[
(0x8cc+5846-0x1fa0)];
zc996524f70 zf3a5916c7a(zc64e9f3c3a);zc996524f70 BB(z5a02f51a13);if(zf3a5916c7a(
(0x6bd+4593-0x18ae))*BB((0x1ab8+1374-0x2016))+zf3a5916c7a((0xbb9+1443-0x115b))*
BB((0x669+5620-0x1c5c))+zf3a5916c7a((0x896+5697-0x1ed5))*BB((0x1a8+7923-0x2099))
+zf3a5916c7a((0x2b9+4304-0x1386))*BB((0xe33+4215-0x1ea7))<0.0f)zf3a5916c7a=
zf3a5916c7a*-1.0f;zc996524f70 r((zf3a5916c7a.z2a56b020d9()*BB).z17fc270567());
z43c30c772b z37ef40bf5d(r((0xd66+3700-0x1bd9)),r((0x1fb3+1706-0x265b)),r(
(0xbac+3871-0x1ac8)));z37ef40bf5d=zf3a5916c7a*z37ef40bf5d;z7bd9fa8427[
(0xaef+2693-0x1574)]=z37ef40bf5d((0x10ff+564-0x1333));z7bd9fa8427[
(0x160c+1314-0x1b2d)]=z37ef40bf5d((0x1f1+4752-0x1480));z7bd9fa8427[
(0x8e2+6682-0x22fa)]=z37ef40bf5d((0x1ca0+1555-0x22b1));float l=sqrt(z37ef40bf5d(
(0xf13+1738-0x15dd))*z37ef40bf5d((0x158d+3048-0x2175))+z37ef40bf5d(
(0x371+8901-0x2635))*z37ef40bf5d((0x23a+1598-0x877))+z37ef40bf5d(
(0x8e0+757-0xbd3))*z37ef40bf5d((0x288+8461-0x2393)));if(l!=0.0f){z7bd9fa8427[
(0x704+6636-0x20f0)]/=l;z7bd9fa8427[(0xa63+5206-0x1eb8)]/=l;z7bd9fa8427[
(0xaad+6536-0x2433)]/=l;}z6fafebb892[(0xad0+699-0xd8b)]=r((0x833+2065-0x1044));
return((0x1ae5+6-0x1aea));}int simEmbRotateAroundAxis(const float*z7ce46f8d33,
const float*z647649a19b,const float*zaa3ea495ed,const float*zed0327ab5d,float 
z6fafebb892,float*z30cd19bca2,float*z75a31f0a6d){if(!z2f54b4c83a())return(-
(0x1fa+7888-0x20c9));

zcab2ae559c zcec140f672;zcec140f672.Q((0x1674+222-0x1752))=z647649a19b[
(0x19d+7467-0x1ec5)];zcec140f672.Q((0x17df+3673-0x2637))=z647649a19b[
(0x709+4877-0x1a16)];zcec140f672.Q((0x158f+3759-0x243c))=z647649a19b[
(0x342+3352-0x1059)];zcec140f672.Q((0x496+2304-0xd93))=z647649a19b[
(0x17cd+1585-0x1dfc)];zcec140f672.X((0x1842+1566-0x1e60))=z7ce46f8d33[
(0x757+7948-0x2663)];zcec140f672.X((0xbcd+1658-0x1246))=z7ce46f8d33[
(0xbdd+5527-0x2173)];zcec140f672.X((0x741+6244-0x1fa3))=z7ce46f8d33[
(0x15d2+3331-0x22d3)];z43c30c772b z9e904ea8e9(zaa3ea495ed);z43c30c772b 
z8a7e6753de(zed0327ab5d);float z72506057c6=-atan2(z9e904ea8e9(
(0x736+8006-0x267b)),z9e904ea8e9((0xeb3+4522-0x205d)));float z5b65d662e4=atan2(-
sqrt(z9e904ea8e9((0x312+4777-0x15bb))*z9e904ea8e9((0x1395+2931-0x1f08))+
z9e904ea8e9((0x34+3063-0xc2a))*z9e904ea8e9((0xbf0+1939-0x1382))),z9e904ea8e9(
(0xd58+721-0x1027)));zcec140f672.X-=z8a7e6753de;zcab2ae559c r;r.X.clear();r.Q.
zc8c9b1ff2a(0.0f,0.0f,z72506057c6);zcec140f672=r*zcec140f672;r.Q.zc8c9b1ff2a(
0.0f,z5b65d662e4,0.0f);zcec140f672=r*zcec140f672;r.Q.zc8c9b1ff2a(0.0f,0.0f,
z6fafebb892);zcec140f672=r*zcec140f672;r.Q.zc8c9b1ff2a(0.0f,-z5b65d662e4,0.0f);
zcec140f672=r*zcec140f672;r.Q.zc8c9b1ff2a(0.0f,0.0f,-z72506057c6);zcec140f672=r*
zcec140f672;zcec140f672.X+=z8a7e6753de;z75a31f0a6d[(0x9ab+3263-0x166a)]=
zcec140f672.Q((0xde1+653-0x106d));z75a31f0a6d[(0x930+4989-0x1cac)]=zcec140f672.Q
((0x1d2c+2402-0x268c));z75a31f0a6d[(0x458+8795-0x26b1)]=zcec140f672.Q(
(0x1bc+1793-0x8ba));z75a31f0a6d[(0x4bf+3594-0x12c6)]=zcec140f672.Q(
(0x10+5031-0x13b7));z30cd19bca2[(0x3cb+4651-0x15f6)]=zcec140f672.X(
(0x17ec+2074-0x2006));z30cd19bca2[(0xec+8861-0x2388)]=zcec140f672.X(
(0x6d8+7609-0x2490));z30cd19bca2[(0x2020+637-0x229b)]=zcec140f672.X(
(0x9ac+1996-0x1176));return((0xf48+1338-0x1481));}int simEmbSetJointMode(int 
z8d5c1bae27,int z9497f912e5){if(!z2f54b4c83a())return(-(0x1775+3398-0x24ba));
zcf0f3da7c0*z839a645366=z87df41beda::z935b5aba45->z9a24f554a0(z8d5c1bae27);if(
z839a645366==NULL)return(-(0x8af+1081-0xce7));z839a645366->z2fcc89db8d(
z9497f912e5);return((0x676+2258-0xf47));}int simEmbSetIkGroupExplicitHandling(
int z25830ea86b,bool z6bd1106fcb){if(!z2f54b4c83a())return(-(0xc3f+6386-0x2530))
;z81a8e195d8*z839a645366=z87df41beda::zada844b223->zdee3818214(z25830ea86b);if(
z839a645366==NULL)return(-(0xaeb+4258-0x1b8c));z839a645366->zea22073a6c(
z6bd1106fcb);return((0x1714+1188-0x1bb7));}int simEmbSetIkGroupProperties(int 
z25830ea86b,int zb30f984f14,int zab82c7fac8,float z3f01d343c0){if(!z2f54b4c83a()
)return(-(0x1cc+2266-0xaa5));z81a8e195d8*z839a645366=z87df41beda::zada844b223->
zdee3818214(z25830ea86b);if(z839a645366==NULL)return(-(0x7eb+2412-0x1156));
z839a645366->z80af1d48c7(zb30f984f14);z839a645366->z6a7c2d3d55(zab82c7fac8);
z839a645366->zdc4fe94cbc(z3f01d343c0);return((0x521+298-0x64a));}int 
simEmbSetIkElementProperties(int z25830ea86b,int zb842795133,int z710c3c22f2,
const float*precision,const float*zceec58c610){if(!z2f54b4c83a())return(-
(0x1070+4107-0x207a));z81a8e195d8*z839a645366=z87df41beda::zada844b223->
zdee3818214(z25830ea86b);if(z839a645366==NULL)return(-(0x1741+1146-0x1bba));
z697f571449*zeb9fa2b8fc=z87df41beda::z935b5aba45->z4cdd500443(zb842795133);if(
zeb9fa2b8fc==NULL)return(-(0x100f+4471-0x2185));zdc525f1a83*z3667fef0c6=
z839a645366->z041de889ec(zb842795133);if(z3667fef0c6==NULL)return(-
(0xfc1+4960-0x2320));if(z710c3c22f2!=-(0x5b6+1693-0xc52))z3667fef0c6->
z0d6a581a53(z710c3c22f2);if(precision!=NULL){z3667fef0c6->z48648a62fe(precision[
(0x913+14-0x921)]);z3667fef0c6->zfb65871add(precision[(0xec1+4354-0x1fc2)]);}if(
zceec58c610!=NULL){z3667fef0c6->z2be6a85ad7(zceec58c610[(0x26f+4470-0x13e5)]);
z3667fef0c6->zd05097ed48(zceec58c610[(0x122+725-0x3f6)]);}return(
(0x1+9196-0x23ec));}
