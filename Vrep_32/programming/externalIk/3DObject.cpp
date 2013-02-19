





#include "v_repConst.h"
#include "jointObject.h"
#include "3DObject.h"
#include "Dummy.h"
#include "Ct.h"
#include "Global.h"
zbc00b3c1a7::zbc00b3c1a7(){z389b2f1654=NULL;zadaece61fd=-(0x16c2+3687-0x2528);
zf1248efa26=(0x651+3073-0x1252);zd5719902ec.z8079139e84();}zbc00b3c1a7::~
zbc00b3c1a7(){}


void zbc00b3c1a7::ze7e6fc81e7(std::vector<int>*zef07098d7c){}void zbc00b3c1a7::
za7283c038e(std::vector<int>*zef07098d7c){int zdbfe37a476=z87df41beda::
z935b5aba45->z9e1c5cc5cd(zef07098d7c,zadaece61fd);z66b46386fb(z87df41beda::
z935b5aba45->zad59a48cc3(zdbfe37a476));}std::string zbc00b3c1a7::zb913bf88e0(){
return(z0a9ce337c9);}void zbc00b3c1a7::z2d788884fe(std::string zb324cfc3e9){
z0a9ce337c9=zb324cfc3e9;}bool zbc00b3c1a7::z9724cc4111(int z01bbee82e6,bool 
z8aa0e0b314){
return(false);}void zbc00b3c1a7::ze270727174(int z89682a1788,bool z8aa0e0b314){}
void zbc00b3c1a7::z92f44bf341(int z01bbee82e6,bool z8aa0e0b314){



if((zfeb40b2026()!=NULL)&&(!z8aa0e0b314)){if(zfeb40b2026()->z9890051730()==
z01bbee82e6)z87df41beda::z935b5aba45->z4f08e8bd38(this,zfeb40b2026()->
zfeb40b2026());}}void zbc00b3c1a7::z745b455f9b(int z89682a1788,bool z8aa0e0b314)
{


}void zbc00b3c1a7::zf597fa0895(float zcec140f672[(0x1187+2816-0x1c83)][
(0x9e8+4483-0x1b67)],bool z4f5e0d6ab8){
z48768ee0bb(z4f5e0d6ab8).z692df07ea8(zcec140f672);}void zbc00b3c1a7::z834da1f651
(float zcec140f672[(0x415+3305-0x10fa)][(0x44+741-0x325)],bool z4f5e0d6ab8){
z253df73c29(z4f5e0d6ab8).z692df07ea8(zcec140f672);}zcab2ae559c zbc00b3c1a7::
z7d9c1b2957(bool z4f5e0d6ab8){
if(zfeb40b2026()==NULL){zcab2ae559c zd094a88178;zd094a88178.z8079139e84();return
(zd094a88178);}else return(zfeb40b2026()->z48768ee0bb(z4f5e0d6ab8));}zcab2ae559c
 zbc00b3c1a7::z48768ee0bb(bool z4f5e0d6ab8){
if(zfeb40b2026()==NULL)return(z989dd8fa33(z4f5e0d6ab8));else return(z7d9c1b2957(
z4f5e0d6ab8)*z989dd8fa33(z4f5e0d6ab8));}zcab2ae559c zbc00b3c1a7::z989dd8fa33(
bool z4f5e0d6ab8){
if(z59ecca4dfc()==sim_object_joint_type){zcf0f3da7c0*z839a645366=(zcf0f3da7c0*)
this;zcab2ae559c z22792d0c1e;z22792d0c1e.z8079139e84();float val;val=z839a645366
->z2bff4c64fe(z4f5e0d6ab8);if(z839a645366->zfb3b8778ca()==
sim_joint_revolute_subtype){z22792d0c1e.Q.zd55d782e18(val,z43c30c772b(0.0f,0.0f,
1.0f));z22792d0c1e.X((0x527+1323-0xa50))=val*z839a645366->zf5d1de8e1b();}if(
z839a645366->zfb3b8778ca()==sim_joint_prismatic_subtype)z22792d0c1e.X(
(0x760+2244-0x1022))=val;if(z839a645366->zfb3b8778ca()==
sim_joint_spherical_subtype){if(z4f5e0d6ab8){if(z839a645366->z1e8b2dc40f()==
(0xcd1+302-0xdff)){
z22792d0c1e.Q.zc8c9b1ff2a(0.0f,0.0f,z839a645366->z9aa1e0129e((0x142c+981-0x17ff)
));zc996524f70 z28435a928c;z28435a928c.zc8c9b1ff2a(z7cda74903d,0.0f,0.0f);
z22792d0c1e.Q=z28435a928c*z22792d0c1e.Q;z28435a928c.zc8c9b1ff2a(0.0f,0.0f,
z839a645366->z9aa1e0129e((0x1564+4217-0x25dc)));z22792d0c1e.Q=z28435a928c*
z22792d0c1e.Q;z28435a928c.zc8c9b1ff2a(-z7cda74903d,0.0f,-z7cda74903d);
z22792d0c1e.Q=z28435a928c*z22792d0c1e.Q;z28435a928c.zc8c9b1ff2a(0.0f,0.0f,
z839a645366->z9aa1e0129e((0xde6+2535-0x17cd)));z22792d0c1e.Q=z28435a928c*
z22792d0c1e.Q;z28435a928c.zc8c9b1ff2a(0.0f,z7cda74903d,0.0f);z22792d0c1e.Q=
z28435a928c*z22792d0c1e.Q;z28435a928c=z839a645366->zd38919858c();z22792d0c1e.Q=
z28435a928c*z22792d0c1e.Q;}else{
z22792d0c1e.Q.zc8c9b1ff2a(0.0f,0.0f,z839a645366->z9aa1e0129e((0x15c+8210-0x216c)
));zc996524f70 z28435a928c;z28435a928c.zc8c9b1ff2a(0.0f,-z7cda74903d,0.0f);
z22792d0c1e.Q=z28435a928c*z22792d0c1e.Q;z28435a928c.zc8c9b1ff2a(0.0f,0.0f,
z839a645366->z9aa1e0129e((0xab7+156-0xb52)));z22792d0c1e.Q=z28435a928c*
z22792d0c1e.Q;z28435a928c.zc8c9b1ff2a(0.0f,z7cda74903d,0.0f);z22792d0c1e.Q=
z28435a928c*z22792d0c1e.Q;z28435a928c.zc8c9b1ff2a(0.0f,0.0f,z839a645366->
z9aa1e0129e((0xd95+879-0x1104)));z22792d0c1e.Q=z28435a928c*z22792d0c1e.Q;}}else 
z22792d0c1e.Q=z839a645366->zd38919858c();}return(zd5719902ec*z22792d0c1e);}else 
if(z59ecca4dfc()==sim_object_dummy_type){z697f571449*z839a645366=(z697f571449*)
this;if(z4f5e0d6ab8)return(z839a645366->z1c2cc5c098());
return(zd5719902ec);}else return(zd5719902ec);}zcab2ae559c zbc00b3c1a7::
z253df73c29(bool z4f5e0d6ab8){
if(z59ecca4dfc()==sim_object_joint_type){if(zfeb40b2026()==NULL)return(
z5dd63d5999(z4f5e0d6ab8));else return(z7d9c1b2957(z4f5e0d6ab8)*z5dd63d5999(
z4f5e0d6ab8));}else return(z48768ee0bb(z4f5e0d6ab8));}zcab2ae559c&zbc00b3c1a7::
z5dd63d5999(bool z4f5e0d6ab8)
{
return(zd5719902ec);}void zbc00b3c1a7::z0c137baeab(const zcab2ae559c&z37ef40bf5d
){zd5719902ec=z37ef40bf5d;}void zbc00b3c1a7::z0c137baeab(const zc996524f70&q){
zd5719902ec.Q=q;}void zbc00b3c1a7::z0c137baeab(const z43c30c772b&x){zd5719902ec.
X=x;}void zbc00b3c1a7::z52fb1adfeb(const zcab2ae559c&z37ef40bf5d){zcab2ae559c 
z2d694dc9e4(z7d9c1b2957().z2a56b020d9());zd5719902ec.z8b98bfb2be(z2d694dc9e4,
z37ef40bf5d);}void zbc00b3c1a7::z52fb1adfeb(const zc996524f70&q){zcab2ae559c 
z2d694dc9e4(z7d9c1b2957().z2a56b020d9());zd5719902ec.Q=z2d694dc9e4.Q*q;}void 
zbc00b3c1a7::z52fb1adfeb(const z43c30c772b&x){zcab2ae559c z2d694dc9e4(
z7d9c1b2957().z2a56b020d9());zd5719902ec.X=z2d694dc9e4*x;}int zbc00b3c1a7::
z9890051730(){return(zf1248efa26);}void zbc00b3c1a7::z5c23104456(int zc1020150ee
){
zf1248efa26=zc1020150ee;}bool zbc00b3c1a7::z6d1a1b4e60(zbc00b3c1a7*z3ea8d0b4ec){
if(zfeb40b2026()==NULL)return(false);if(zfeb40b2026()==z3ea8d0b4ec)return(true);
return(zfeb40b2026()->z6d1a1b4e60(z3ea8d0b4ec));}int zbc00b3c1a7::z6b8699529b(){
return(zadaece61fd);}void zbc00b3c1a7::z10a9cf8c67(int pID){
zadaece61fd=pID;}void zbc00b3c1a7::z66b46386fb(zbc00b3c1a7*z2d7d2b0f2c,bool 
z0ffcd297c3){
if(z2d7d2b0f2c==this)return;z389b2f1654=z2d7d2b0f2c;if(z0ffcd297c3)z87df41beda::
z935b5aba45->zac183c5cbf();}zbc00b3c1a7*zbc00b3c1a7::zfeb40b2026(){return(
z389b2f1654);}int zbc00b3c1a7::z59ecca4dfc(){return(ze22742c9a6);}


void zbc00b3c1a7::z3b7b9ab2ed(z2966f2073e&zc035e59036){}void zbc00b3c1a7::
z5b303b716b(z2966f2073e&zc035e59036){zd5719902ec.Q((0x642+428-0x7ee))=
zc035e59036.zd29080bea8();zd5719902ec.Q((0xee5+1762-0x15c6))=zc035e59036.
zd29080bea8();zd5719902ec.Q((0x5+7619-0x1dc6))=zc035e59036.zd29080bea8();
zd5719902ec.Q((0xbad+3577-0x19a3))=zc035e59036.zd29080bea8();zd5719902ec.X(
(0x762+3639-0x1599))=zc035e59036.zd29080bea8();zd5719902ec.X((0x952+3783-0x1818)
)=zc035e59036.zd29080bea8();zd5719902ec.X((0x7dd+6888-0x22c3))=zc035e59036.
zd29080bea8();zf1248efa26=zc035e59036.z5f93610747();zadaece61fd=zc035e59036.
z5f93610747();z0a9ce337c9=zc035e59036.zbf799d7883().c_str();}
