

#include "3X3Matrix.h"
#include "4Vector.h"
#include "MyMath.h"
ze2b7e09268::ze2b7e09268(){}ze2b7e09268::ze2b7e09268(const z43c30c772b&
z592d5c6dc0,const z43c30c772b&za2505258d4,const z43c30c772b&zcf8f4bb372){(*this)
.z7bd9fa8427[(0xf33+1924-0x16b7)]=z592d5c6dc0;(*this).z7bd9fa8427[
(0x11a6+717-0x1472)]=za2505258d4;(*this).z7bd9fa8427[(0xb41+3984-0x1acf)]=
zcf8f4bb372;}ze2b7e09268::ze2b7e09268(const zc996524f70&q){(*this)=q.zc48c746a21
();}ze2b7e09268::ze2b7e09268(const ze2b7e09268&zcec140f672){(*this).z7bd9fa8427[
(0x18f+917-0x524)]=zcec140f672.z7bd9fa8427[(0xc34+897-0xfb5)];(*this).
z7bd9fa8427[(0xc29+3985-0x1bb9)]=zcec140f672.z7bd9fa8427[(0x1a56+2471-0x23fc)];(
*this).z7bd9fa8427[(0x27d+811-0x5a6)]=zcec140f672.z7bd9fa8427[
(0x2f3+4221-0x136e)];}ze2b7e09268::~ze2b7e09268(){}void ze2b7e09268::zc8c9b1ff2a
(float a,float b,float g){
float A=(float)cos(a);float B=(float)sin(a);float C=(float)cos(b);float 
z7b370f9b18=(float)sin(b);float zcccce5545f=(float)cos(g);float F=(float)sin(g);
float zfe084664e7=A*z7b370f9b18;float BD=B*z7b370f9b18;z7bd9fa8427[
(0xfbd+4781-0x226a)]((0x2a9+3830-0x119f))=C*zcccce5545f;z7bd9fa8427[
(0x67c+4575-0x185a)]((0x51d+1735-0xbe4))=-C*F;z7bd9fa8427[(0x640+3825-0x152f)](
(0x2332+916-0x26c6))=z7b370f9b18;z7bd9fa8427[(0x1fa+177-0x2ab)](
(0x16dc+813-0x1a08))=BD*zcccce5545f+A*F;z7bd9fa8427[(0x11+6649-0x1a09)](
(0xf44+943-0x12f2))=-BD*F+A*zcccce5545f;z7bd9fa8427[(0xf3f+2496-0x18fd)](
(0xd3c+3209-0x19c4))=-B*C;z7bd9fa8427[(0x15a2+2557-0x1f9f)]((0x875+914-0xc05))=-
zfe084664e7*zcccce5545f+B*F;z7bd9fa8427[(0x377+7619-0x2139)]((0xfef+3590-0x1df3)
)=zfe084664e7*F+B*zcccce5545f;z7bd9fa8427[(0xc77+993-0x1056)]((0xd4+4092-0x10ce)
)=A*C;}void ze2b7e09268::zc8c9b1ff2a(const z43c30c772b&z37ef40bf5d){
zc8c9b1ff2a(z37ef40bf5d((0x1af3+1903-0x2262)),z37ef40bf5d((0x16f9+1773-0x1de5)),
z37ef40bf5d((0x188+8617-0x232f)));}z43c30c772b ze2b7e09268::z5bc3f5e12e()const{
z43c30c772b zd094a88178;float z5278edca54=z7bd9fa8427[(0x763+2814-0x125f)](
(0x167a+2421-0x1fef));if(z5278edca54>1.0f)z5278edca54=1.0f;
if(z5278edca54<-1.0f)z5278edca54=-1.0f;
zd094a88178((0xbb7+1865-0x12ff))=z16efbd9f9a::zdd8ee54467(z5278edca54);if(
z5278edca54<0.0f)z5278edca54=-z5278edca54;if(z5278edca54<0.999995f){
zd094a88178((0x1d43+772-0x2047))=(float)atan2(-z7bd9fa8427[(0x1054+1288-0x155a)]
((0x303+6646-0x1cf8)),z7bd9fa8427[(0x176+2577-0xb85)]((0x15df+3590-0x23e3)));
zd094a88178((0x1177+4061-0x2152))=(float)atan2(-z7bd9fa8427[(0x1123+3091-0x1d35)
]((0x15e6+1284-0x1aea)),z7bd9fa8427[(0x11b2+5216-0x2612)]((0x5f6+7199-0x2215)));
}else{
zd094a88178((0x3b+571-0x276))=0.0f;zd094a88178((0x59+8484-0x217b))=(float)atan2(
z7bd9fa8427[(0x17e8+328-0x1930)]((0x909+5463-0x1e5f)),z7bd9fa8427[
(0x14a3+2753-0x1f63)]((0x1707+2156-0x1f72)));}return(zd094a88178);}zc996524f70 
ze2b7e09268::z56ed45e3d1()const{zc996524f70 zd094a88178;float z2b7d9e78b1=
z7bd9fa8427[(0x518+4267-0x15c3)]((0x669+5889-0x1d6a))+z7bd9fa8427[
(0x1605+3922-0x2556)]((0x56d+3778-0x142e))+z7bd9fa8427[(0x796+1312-0xcb4)](
(0x1e2c+525-0x2037));if(z2b7d9e78b1>=0.0f)
{float s=sqrtf(z2b7d9e78b1+1.0f)*2.0f;zd094a88178((0x963+2743-0x1419))=(
z7bd9fa8427[(0x8d7+6836-0x238a)]((0x1f27+1457-0x24d6))-z7bd9fa8427[
(0x6a8+1014-0xa9c)]((0x1c1f+743-0x1f05)))/s;zd094a88178((0x192+5150-0x15ae))=(
z7bd9fa8427[(0x1ac9+971-0x1e92)]((0x57+694-0x30d))-z7bd9fa8427[
(0x1f3b+510-0x2139)]((0x117+9664-0x26d5)))/s;zd094a88178((0xadd+1562-0x10f4))=(
z7bd9fa8427[(0xd7d+138-0xe07)]((0x1e34+429-0x1fe0))-z7bd9fa8427[
(0x4ff+6231-0x1d55)]((0x1585+2845-0x20a2)))/s;zd094a88178((0xce3+639-0xf62))=
0.25f*s;}else{if((z7bd9fa8427[(0x1539+4246-0x25cf)]((0x9b9+3889-0x18ea))>=
z7bd9fa8427[(0x64d+2390-0xfa2)]((0x2bf+5481-0x1827)))&&(z7bd9fa8427[
(0x653+5876-0x1d47)]((0x1685+1587-0x1cb8))>=z7bd9fa8427[(0xd19+232-0xdff)](
(0x1260+273-0x136f)))){float s=sqrtf(1.0f+z7bd9fa8427[(0x1a8+2434-0xb2a)](
(0x2272+1134-0x26e0))-z7bd9fa8427[(0x1f9f+172-0x204a)]((0x4ea+3608-0x1301))-
z7bd9fa8427[(0x7d9+2581-0x11ec)]((0x132b+1203-0x17dc)))*2.0f;zd094a88178(
(0x5+559-0x233))=0.25f*s;zd094a88178((0x1209+720-0x14d7))=(z7bd9fa8427[
(0x86c+7736-0x26a4)]((0x44f+1604-0xa92))+z7bd9fa8427[(0x6c1+7856-0x2570)](
(0x1b46+2690-0x25c8)))/s;zd094a88178((0x3d0+7615-0x218c))=(z7bd9fa8427[
(0x47b+8342-0x250f)]((0x177+7104-0x1d37))+z7bd9fa8427[(0x798+7381-0x246d)](
(0x6bd+6450-0x1fed)))/s;zd094a88178((0x189+6803-0x1c1c))=(z7bd9fa8427[
(0x4b1+5671-0x1ad7)]((0x918+6759-0x237d))-z7bd9fa8427[(0x1751+154-0x17e9)](
(0x58a+7364-0x224d)))/s;}else{if((z7bd9fa8427[(0x172+8895-0x2430)](
(0x9c8+2827-0x14d2))>=z7bd9fa8427[(0xbed+1596-0x1229)]((0x22d1+847-0x2620)))&&(
z7bd9fa8427[(0xde1+5358-0x22ce)]((0x1acf+2832-0x25de))>=z7bd9fa8427[
(0x160+4156-0x119a)]((0x18d8+3248-0x2586)))){float s=sqrtf(1.0f+z7bd9fa8427[
(0x14f6+3226-0x218f)]((0x568+7275-0x21d2))-z7bd9fa8427[(0x1597+173-0x1644)](
(0x13c1+471-0x1598))-z7bd9fa8427[(0x720+7100-0x22da)]((0x17ad+3027-0x237e)))*
2.0f;zd094a88178((0xf25+240-0x1014))=(z7bd9fa8427[(0xd87+4168-0x1dcf)](
(0x11fb+2369-0x1b3b))+z7bd9fa8427[(0x975+1237-0xe49)]((0x1696+670-0x1934)))/s;
zd094a88178((0x1887+1647-0x1ef4))=0.25f*s;zd094a88178((0x18e2+827-0x1c1a))=(
z7bd9fa8427[(0x21c+6265-0x1a94)]((0x78+8502-0x21ac))+z7bd9fa8427[
(0xcf2+4318-0x1dce)]((0xc20+3084-0x182b)))/s;zd094a88178((0x830+6153-0x2039))=(
z7bd9fa8427[(0xebc+4543-0x2079)]((0x6f1+3886-0x161f))-z7bd9fa8427[
(0x899+5066-0x1c63)]((0x1253+2729-0x1cfa)))/s;}else{float s=sqrtf(1.0f+
z7bd9fa8427[(0x124d+4216-0x22c3)]((0xc62+6611-0x2633))-z7bd9fa8427[
(0x48+7629-0x1e15)]((0x1202+2811-0x1cfd))-z7bd9fa8427[(0x11db+4153-0x2213)](
(0x1704+99-0x1766)))*2.0f;zd094a88178((0x19b7+1309-0x1ed3))=(z7bd9fa8427[
(0x989+2742-0x143d)]((0x1704+1472-0x1cc4))+z7bd9fa8427[(0x48f+8333-0x251c)](
(0x1ab1+1608-0x20f7)))/s;zd094a88178((0x5e6+4504-0x177c))=(z7bd9fa8427[
(0x969+6757-0x23cd)]((0xc18+4528-0x1dc6))+z7bd9fa8427[(0x16a5+648-0x192b)](
(0x693+3894-0x15c8)))/s;zd094a88178((0xb64+316-0xc9d))=0.25f*s;zd094a88178(
(0x101d+863-0x137c))=(z7bd9fa8427[(0x1f63+1539-0x2566)]((0x140c+1142-0x1881))-
z7bd9fa8427[(0x14e7+4055-0x24bd)]((0x5ad+5013-0x1942)))/s;}}}zd094a88178.
normalize();
return(zd094a88178);}void ze2b7e09268::z4174ee2a49(const ze2b7e09268&z0755af5496
,const ze2b7e09268&z8930959f0b,float t){
zc996524f70 out;out.z4174ee2a49(z0755af5496.z56ed45e3d1(),z8930959f0b.
z56ed45e3d1(),t);(*this)=out;}void ze2b7e09268::z313e3777ba(float z6fafebb892){
float c=(float)cos(z6fafebb892);float s=(float)sin(z6fafebb892);z7bd9fa8427[
(0x42b+3459-0x11ae)]((0xf36+3951-0x1ea5))=1.0f;z7bd9fa8427[(0x867+7717-0x268b)](
(0x14d4+149-0x1569))=0.0f;z7bd9fa8427[(0x5f5+86-0x649)]((0xbb6+4824-0x1e8e))=
0.0f;z7bd9fa8427[(0xbc1+634-0xe3b)]((0x199a+2816-0x2499))=0.0f;z7bd9fa8427[
(0x450+729-0x728)]((0x6f6+3431-0x145c))=c;z7bd9fa8427[(0x609+4856-0x18ff)](
(0x2013+1413-0x2597))=-s;z7bd9fa8427[(0xbb8+6410-0x24c2)]((0x1897+1103-0x1ce4))=
0.0f;z7bd9fa8427[(0x9d8+3132-0x1613)]((0x38+4090-0x1030))=s;z7bd9fa8427[
(0xa4b+5363-0x1f3c)]((0x758+2156-0xfc2))=c;}void ze2b7e09268::z515ae34e81(float 
z6fafebb892){float c=(float)cos(z6fafebb892);float s=(float)sin(z6fafebb892);
z7bd9fa8427[(0x1af+3978-0x1139)]((0x9c9+2196-0x125d))=c;z7bd9fa8427[
(0xf01+4238-0x1f8e)]((0x294+4393-0x13bd))=0.0f;z7bd9fa8427[(0x6f3+5102-0x1adf)](
(0xd49+218-0xe23))=s;z7bd9fa8427[(0x247+2597-0xc6c)]((0x1969+1559-0x1f7f))=0.0f;
z7bd9fa8427[(0x77d+5449-0x1cc5)]((0xda2+5828-0x2465))=1.0f;z7bd9fa8427[
(0x439+1347-0x97a)]((0xdc3+4232-0x1e4a))=0.0f;z7bd9fa8427[(0x1797+342-0x18ed)](
(0x4a2+739-0x783))=-s;z7bd9fa8427[(0x256+8080-0x21e5)]((0x184f+591-0x1a9c))=0.0f
;z7bd9fa8427[(0x1e33+968-0x21f9)]((0x225+8936-0x250b))=c;}void ze2b7e09268::
z82b593ca65(float z6fafebb892){float c=(float)cos(z6fafebb892);float s=(float)
sin(z6fafebb892);z7bd9fa8427[(0x1022+5806-0x26d0)]((0x128f+1181-0x172c))=c;
z7bd9fa8427[(0x6cc+2116-0xf0f)]((0xbd5+6626-0x25b7))=-s;z7bd9fa8427[
(0xaf+3718-0xf33)]((0x9f5+2727-0x149c))=0.0f;z7bd9fa8427[(0x628+912-0x9b8)](
(0x15ad+2740-0x2060))=s;z7bd9fa8427[(0x55c+643-0x7de)]((0x1e9+3520-0xfa8))=c;
z7bd9fa8427[(0xb6d+3034-0x1745)]((0x46c+8619-0x2616))=0.0f;z7bd9fa8427[
(0x550+5618-0x1b42)]((0x5d9+7539-0x234a))=0.0f;z7bd9fa8427[(0x106c+4621-0x2278)]
((0x1945+1501-0x1f20))=0.0f;z7bd9fa8427[(0x9d+2959-0xc2a)]((0x925+6314-0x21cd))=
1.0f;}z43c30c772b ze2b7e09268::zb60b86f6eb()const{
z43c30c772b zd1edcde5e1(z7bd9fa8427[(0x5ab+6294-0x1e41)]-z7bd9fa8427[
(0x1615+1456-0x1bc4)]);z43c30c772b z7b058c25be(z7bd9fa8427[(0x3ca+3715-0x124c)]-
z7bd9fa8427[(0x7d6+5274-0x1c6e)]);return((zd1edcde5e1^z7b058c25be).zce732648bf()
);}
