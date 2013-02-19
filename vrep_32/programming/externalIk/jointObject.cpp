





#include "jointObject.h"
#include "Ct.h"
#include "Tt.h"
#include "v_repConst.h"
#include "Global.h"
zcf0f3da7c0::zcf0f3da7c0(){
zf4ee49f080();
z93f4b04676=sim_joint_revolute_subtype;zaaf789a4b9=true;zabce936d13=zd9868840d1;
z4f5163cf85=-piVal;za69ecb0e79=10.0f*zae8adfe92e;}zcf0f3da7c0::zcf0f3da7c0(int 
ze9802f5d5f){z93f4b04676=ze9802f5d5f;zf4ee49f080();if(ze9802f5d5f==
sim_joint_revolute_subtype){z0ada5964c5=sim_jointmode_force;zaaf789a4b9=true;
zabce936d13=zd9868840d1;z4f5163cf85=-piVal;za69ecb0e79=10.0f*zae8adfe92e;}if(
ze9802f5d5f==sim_joint_prismatic_subtype){z0ada5964c5=sim_jointmode_force;
zaaf789a4b9=false;zabce936d13=1.0f;z4f5163cf85=-0.5f;za69ecb0e79=0.1f;}if(
ze9802f5d5f==sim_joint_spherical_subtype){z0ada5964c5=sim_jointmode_force;
zaaf789a4b9=true;zabce936d13=piVal;z4f5163cf85=0.0f;
za69ecb0e79=10.0f*zae8adfe92e;}}void zcf0f3da7c0::zf4ee49f080(){
ze22742c9a6=sim_object_joint_type;z8bbbac6332=0.0f;z4b7d1f6319.z8079139e84();
z30e6fd7c3c=0.0f;
z0ada5964c5=sim_jointmode_ik;zf79df498ed=-(0x1c64+162-0x1d05);z54285e3105=1.0f;
z18fc91c157=0.0f;z0a9ce337c9="\x64\x65\x66\x61\x75\x6c\x74";z5b9af3b8df=1.0f;}
zcf0f3da7c0::~zcf0f3da7c0(){}


void zcf0f3da7c0::ze7e6fc81e7(std::vector<int>*zef07098d7c){
za7283c038e(zef07098d7c);zf79df498ed=z87df41beda::z935b5aba45->z9e1c5cc5cd(
zef07098d7c,zf79df498ed);}void zcf0f3da7c0::z2fcc89db8d(int z7c2af51e19){if(
z7c2af51e19==sim_jointmode_passive){zf79df498ed=-(0x76+4439-0x11cc);z87df41beda
::z935b5aba45->zac183c5cbf();
z0ada5964c5=z7c2af51e19;}if(z7c2af51e19==sim_jointmode_motion){if(z93f4b04676!=
sim_joint_spherical_subtype){zf79df498ed=-(0xa73+5051-0x1e2d);z87df41beda::
z935b5aba45->zac183c5cbf();
z0ada5964c5=z7c2af51e19;}}if(z7c2af51e19==sim_jointmode_ikdependent){if(
z93f4b04676!=sim_joint_spherical_subtype){z87df41beda::z935b5aba45->zac183c5cbf(
);
z0ada5964c5=z7c2af51e19;}}if(z7c2af51e19==sim_jointmode_dependent){if(
z93f4b04676!=sim_joint_spherical_subtype){z87df41beda::z935b5aba45->zac183c5cbf(
);
z0ada5964c5=z7c2af51e19;}}if(z7c2af51e19==sim_jointmode_force){zf79df498ed=-
(0x11d3+3503-0x1f81);
z8bbbac6332=0.0f;if(z93f4b04676==sim_joint_revolute_subtype)zabce936d13=
zb026169845::z70c1af2822(0.0f,zd9868840d1,zabce936d13);
if(z93f4b04676==sim_joint_spherical_subtype)zabce936d13=piVal;z87df41beda::
z935b5aba45->zac183c5cbf();
z0ada5964c5=z7c2af51e19;}if(z7c2af51e19==sim_jointmode_ik){zf79df498ed=-
(0x1594+1751-0x1c6a);z87df41beda::z935b5aba45->zac183c5cbf();
z0ada5964c5=z7c2af51e19;}z1c5ae67dc1(z2bff4c64fe());
}void zcf0f3da7c0::z848207bb5c(){
for(int i=(0x141d+913-0x17ae);i<int(z098091a9d3.size());i++){if(z098091a9d3[i]->
zf847780e9c()==sim_jointmode_dependent)z098091a9d3[i]->z1c5ae67dc1(0.0f,false);
}}int zcf0f3da7c0::zf847780e9c(){return(z0ada5964c5);}int zcf0f3da7c0::
ze63a7da466(){return(zf79df498ed);}float zcf0f3da7c0::z476cb349f4(){return(
z54285e3105);}float zcf0f3da7c0::z11196f2ea1(){return(z18fc91c157);}int 
zcf0f3da7c0::zfb3b8778ca(){return(z93f4b04676);}float zcf0f3da7c0::zf5d1de8e1b()
const{return(z8bbbac6332);}void zcf0f3da7c0::z61275fc1b1(const zc996524f70&
zec880c2e91){zc996524f70 zf2dc2f6435(zec880c2e91);if(zabce936d13<piVal*0.99f){
ze2b7e09268 z44cc7ca359(zf2dc2f6435);z43c30c772b z8a99cac568(0.0f,0.0f,1.0f);
float z6fafebb892=z8a99cac568.z6f55e083ba(z44cc7ca359.z7bd9fa8427[
(0xb81+5790-0x221d)]);if(z6fafebb892>zabce936d13){
z43c30c772b z7fab5016d7((z44cc7ca359.z7bd9fa8427[(0x4b0+692-0x762)]^z8a99cac568)
.zce732648bf());zc996524f70 z3c9bf1dbbf(z6fafebb892-zabce936d13,z7fab5016d7);
zf2dc2f6435=z3c9bf1dbbf*zf2dc2f6435;}}z4b7d1f6319=zf2dc2f6435;}zc996524f70 
zcf0f3da7c0::zd38919858c()const{return(z4b7d1f6319);}void zcf0f3da7c0::
zba04dca8d3(float z10182bc485){if(z93f4b04676==sim_joint_revolute_subtype)
zb026169845::zcaaed61082(0.01f*zae8adfe92e,100000.0f,z10182bc485);
if(z93f4b04676==sim_joint_prismatic_subtype)zb026169845::zcaaed61082(0.0001f,
1000.0f,z10182bc485);if(z93f4b04676==sim_joint_spherical_subtype)zb026169845::
zcaaed61082(0.01f*zae8adfe92e,piVal,z10182bc485);za69ecb0e79=z10182bc485;}float 
zcf0f3da7c0::ze037be1594(){return(za69ecb0e79);}float zcf0f3da7c0::z2bff4c64fe(
bool z4f5e0d6ab8){
if(z4f5e0d6ab8)return(z1c1a35db38);return(z30e6fd7c3c);}float zcf0f3da7c0::
zb4033c554c(){return(z5b9af3b8df);}void zcf0f3da7c0::zc554c19532(float 
z14f0fa92d0){z14f0fa92d0=zb026169845::z70c1af2822(-1.0f,1.0f,z14f0fa92d0);
z5b9af3b8df=z14f0fa92d0;}float zcf0f3da7c0::zcf4dffd178(){return((z2bff4c64fe()-
z4f5163cf85)/zabce936d13);}void zcf0f3da7c0::zd5b8ae80e4(float z5142b12eb6){
z1c5ae67dc1(z4f5163cf85+z5142b12eb6*zabce936d13);}void zcf0f3da7c0::z1c5ae67dc1(
float zab46142f2e,bool z4f5e0d6ab8){
if(zaaf789a4b9)zab46142f2e=zb026169845::zb302084cf1(zab46142f2e);else{if(
zab46142f2e>(zc17d1aba73()+z4a5ca97b2a()))zab46142f2e=zc17d1aba73()+z4a5ca97b2a(
);if(zab46142f2e<zc17d1aba73())zab46142f2e=zc17d1aba73();}if(z4f5e0d6ab8)
z1c1a35db38=zab46142f2e;else z30e6fd7c3c=zab46142f2e;if(z0ada5964c5==
sim_jointmode_dependent){
float z6dee6dc258=0.0f;if(zf79df498ed!=-(0x11ba+3245-0x1e66)){zcf0f3da7c0*
z141a18ec75=z87df41beda::z935b5aba45->z9a24f554a0(zf79df498ed);if(z141a18ec75!=
NULL)z6dee6dc258=z54285e3105*z141a18ec75->z2bff4c64fe(z4f5e0d6ab8);}if(
z4f5e0d6ab8)z1c1a35db38=z6dee6dc258+z18fc91c157;else z30e6fd7c3c=z6dee6dc258+
z18fc91c157;}z848207bb5c();}float zcf0f3da7c0::zc17d1aba73(){return(z4f5163cf85)
;}float zcf0f3da7c0::z4a5ca97b2a(){return(zabce936d13);}bool zcf0f3da7c0::
z03078ef7c0(){if(z93f4b04676==sim_joint_prismatic_subtype)return(false);return(
zaaf789a4b9);}void zcf0f3da7c0::z0f0a1f33c9(float ze8d299719a){if(z93f4b04676!=
sim_joint_spherical_subtype)z1c1a35db38=z30e6fd7c3c;else{
z246f1bdc38=(0x3c9+5632-0x19c9);ze2b7e09268 zcec140f672(z4b7d1f6319);float 
z6fafebb892=z43c30c772b::zaebd0fb77e.z6f55e083ba(zcec140f672.z7bd9fa8427[
(0x1309+4821-0x25dc)]);if((zabce936d13<179.9f*zae8adfe92e)&&(z6fafebb892>1.0f*
zae8adfe92e)){if((zabce936d13-ze8d299719a)/2.0f<z6fafebb892){
z246f1bdc38=(0x4cb+4720-0x1739);z43c30c772b n(zcec140f672.z7bd9fa8427[
(0x1b2f+2753-0x25ee)]);n((0x900+2765-0x13cb))=0.0f;n.normalize();z43c30c772b y((
z43c30c772b::zaebd0fb77e^n).zce732648bf());float z87de2c3ad0=z43c30c772b::
z7e831c1eef.z6f55e083ba(y);z43c30c772b z2aa8e507da(z43c30c772b::z7e831c1eef^y);
if(z2aa8e507da((0x30d+6799-0x1d9a))<0.0f)z87de2c3ad0=-z87de2c3ad0;z1c1a35db38=
0.0f;
z46b8c50687=z87de2c3ad0;z0c3a29177e=z6fafebb892;float zb9f414dadb=zcec140f672.
z7bd9fa8427[(0x23c5+711-0x268c)].z6f55e083ba(y);z43c30c772b zb47b58e45d(y^
zcec140f672.z7bd9fa8427[(0x621+4283-0x16dc)]);if(zb47b58e45d*zcec140f672.
z7bd9fa8427[(0x1101+4066-0x20e1)]<0.0f)zb9f414dadb=-zb9f414dadb;z219b32a893=
zb9f414dadb;}}if(z246f1bdc38==(0x1ad5+501-0x1cca)){
z1c1a35db38=0.0f;
z46b8c50687=0.0f;z0c3a29177e=0.0f;z219b32a893=0.0f;}}}int zcf0f3da7c0::
z9a988f2392(){if(z93f4b04676!=sim_joint_spherical_subtype)return(
(0x12e8+5069-0x26b4));return((0x3d9+6659-0x1dd9));}int zcf0f3da7c0::z1e8b2dc40f(
){return(z246f1bdc38);}void zcf0f3da7c0::zef9ebc18fb(zcab2ae559c&z678a409ea5,int
 z93438c6aa1,bool z4f5e0d6ab8){
if(z246f1bdc38==(0xf5+2656-0xb55)){
if(z93438c6aa1==(0xe7f+5897-0x2588)){z678a409ea5.z8079139e84();z678a409ea5.Q.
zc8c9b1ff2a(0.0f,z7cda74903d,0.0f);zcab2ae559c z5c61edca16(z989dd8fa33());
z678a409ea5=z5c61edca16*z678a409ea5;}if(z93438c6aa1==(0x1ac3+1088-0x1f02)){
z678a409ea5.z8079139e84();z678a409ea5.Q.zc8c9b1ff2a(-z7cda74903d,0.0f,-
z7cda74903d);}if(z93438c6aa1==(0x43b+6424-0x1d51)){z678a409ea5.z8079139e84();
z678a409ea5.Q.zc8c9b1ff2a(z7cda74903d,0.0f,0.0f);}}else{if(z93438c6aa1==
(0x15e6+52-0x161a)){z678a409ea5=z5dd63d5999();}if(z93438c6aa1==(0x2dc+722-0x5ad)
){z678a409ea5.z8079139e84();z678a409ea5.Q.zc8c9b1ff2a(0.0f,z7cda74903d,0.0f);}if
(z93438c6aa1==(0x1125+5116-0x251f)){z678a409ea5.z8079139e84();z678a409ea5.Q.
zc8c9b1ff2a(0.0f,-z7cda74903d,0.0f);}}}float zcf0f3da7c0::z9aa1e0129e(int 
z93438c6aa1){if(z93438c6aa1==(0x23fd+754-0x26ef))return(z46b8c50687);if(
z93438c6aa1==(0x1ed1+1169-0x2361))return(z0c3a29177e);if(z93438c6aa1==
(0x19e6+2681-0x245d))return(z219b32a893);return(0.0f);}void zcf0f3da7c0::
ze7268c0935(float zab46142f2e,int z93438c6aa1){if(z93438c6aa1==
(0x455+6280-0x1cdd))z46b8c50687=zab46142f2e;if(z93438c6aa1==(0x1184+3673-0x1fdc)
)z0c3a29177e=zab46142f2e;if(z93438c6aa1==(0x216b+1133-0x25d6))z219b32a893=
zab46142f2e;if(z246f1bdc38==(0x1050+411-0x11eb)){
zc996524f70 z3c100b5e37(z4b7d1f6319);zef2cfac6b7();zc996524f70 zec880c2e91(
z3c100b5e37.z2a56b020d9()*z4b7d1f6319);z43c30c772b z514e59275f(zec880c2e91.
z5bc3f5e12e());z46b8c50687=z514e59275f((0x6c0+8227-0x26e3));z0c3a29177e=
z514e59275f((0x17+5805-0x16c3));z219b32a893=z514e59275f((0x555+7374-0x2221));
z4b7d1f6319=z3c100b5e37;}else{
zc996524f70 z3c100b5e37(z4b7d1f6319);zef2cfac6b7();ze2b7e09268 zcec140f672(
z4b7d1f6319);float z6fafebb892=z43c30c772b::zaebd0fb77e.z6f55e083ba(zcec140f672.
z7bd9fa8427[(0x1040+3637-0x1e73)]);if(z6fafebb892>0.01f*zae8adfe92e){z43c30c772b
 n(zcec140f672.z7bd9fa8427[(0x753+1829-0xe76)]);n((0x161d+832-0x195b))=0.0f;n.
normalize();z43c30c772b y((z43c30c772b::zaebd0fb77e^n).zce732648bf());float 
z87de2c3ad0=z43c30c772b::z7e831c1eef.z6f55e083ba(y);z43c30c772b z2aa8e507da(
z43c30c772b::z7e831c1eef^y);if(z2aa8e507da((0x491+8220-0x24ab))<0.0f)z87de2c3ad0
=-z87de2c3ad0;z46b8c50687=z87de2c3ad0;z0c3a29177e=z6fafebb892;float zb9f414dadb=
zcec140f672.z7bd9fa8427[(0x698+6092-0x1e64)].z6f55e083ba(y);z43c30c772b 
zb47b58e45d(y^zcec140f672.z7bd9fa8427[(0xf28+3506-0x1cda)]);if(zb47b58e45d*
zcec140f672.z7bd9fa8427[(0x66a+7350-0x231e)]<0.0f)zb9f414dadb=-zb9f414dadb;
z219b32a893=zb9f414dadb;}else{
float z6fafebb892=z43c30c772b::z7e831c1eef.z6f55e083ba(zcec140f672.z7bd9fa8427[
(0x17a7+2262-0x207d)]);if((z43c30c772b::z7e831c1eef^zcec140f672.z7bd9fa8427[
(0x457+8753-0x2688)])((0x2a0+4909-0x15cb))<0.0f)z6fafebb892=-z6fafebb892;
z46b8c50687=z6fafebb892;z0c3a29177e=0.0f;z219b32a893=0.0f;}z4b7d1f6319=
z3c100b5e37;}}void zcf0f3da7c0::zef2cfac6b7(){if(z93f4b04676==
sim_joint_spherical_subtype){zcab2ae559c zc69be4e6cc(z5dd63d5999(true));
zcab2ae559c z5c61edca16(z989dd8fa33(true));z61275fc1b1(zc69be4e6cc.Q.z2a56b020d9
()*z5c61edca16.Q);}}bool zcf0f3da7c0::z9724cc4111(int z01bbee82e6,bool 
z8aa0e0b314){





z92f44bf341(z01bbee82e6,z8aa0e0b314);if(zf79df498ed==z01bbee82e6){zf79df498ed=-
(0x1223+3642-0x205c);}
for(int i=(0x1ab1+580-0x1cf5);i<int(z098091a9d3.size());i++){if(z098091a9d3[i]->
z9890051730()==z01bbee82e6)z098091a9d3.erase(z098091a9d3.begin()+i);}return(
false);}void zcf0f3da7c0::ze270727174(int z89682a1788,bool z8aa0e0b314){

z745b455f9b(z89682a1788,z8aa0e0b314);}


void zcf0f3da7c0::z3b7b9ab2ed(z2966f2073e&zc035e59036){z5b303b716b(zc035e59036);
z93f4b04676=zc035e59036.z5f93610747();z8bbbac6332=zc035e59036.zd29080bea8();
z4b7d1f6319((0x179c+313-0x18d5))=zc035e59036.zd29080bea8();z4b7d1f6319(
(0xa35+4107-0x1a3f))=zc035e59036.zd29080bea8();z4b7d1f6319((0xa96+2102-0x12ca))=
zc035e59036.zd29080bea8();z4b7d1f6319((0x4f6+6921-0x1ffc))=zc035e59036.
zd29080bea8();unsigned char dummy=zc035e59036.zdbce8f148f();zaaf789a4b9=
SIM_IS_BIT_SET(dummy,(0x19f5+688-0x1ca5));z4f5163cf85=zc035e59036.zd29080bea8();
zabce936d13=zc035e59036.zd29080bea8();z30e6fd7c3c=zc035e59036.zd29080bea8();
za69ecb0e79=zc035e59036.zd29080bea8();z5b9af3b8df=zc035e59036.zd29080bea8();
z0ada5964c5=zc035e59036.z5f93610747();zf79df498ed=zc035e59036.z5f93610747();
z54285e3105=zc035e59036.zd29080bea8();z18fc91c157=zc035e59036.zd29080bea8();}
