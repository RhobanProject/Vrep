

#include "Vector.h"
ze230f62758::ze230f62758(){}ze230f62758::ze230f62758(int z608e81f32d):data(new 
float[z608e81f32d]),z564abe0129(z608e81f32d){}ze230f62758::ze230f62758(const 
z43c30c772b&z37ef40bf5d){data=new float[(0x14bc+2957-0x2046)];z564abe0129=
(0x375+5865-0x1a5b);(*this)=z37ef40bf5d;}ze230f62758::ze230f62758(const 
zc996524f70&z37ef40bf5d){data=new float[(0x10c4+5450-0x260a)];z564abe0129=
(0x384+6697-0x1da9);(*this)=z37ef40bf5d;}ze230f62758::ze230f62758(const 
z0b9a2fd2df&z37ef40bf5d){data=new float[(0x733+2265-0x1006)];z564abe0129=
(0x5d3+2743-0x1084);(*this)=z37ef40bf5d;}ze230f62758::ze230f62758(const 
zcab2ae559c&z37ef40bf5d){data=new float[(0x144b+1792-0x1b44)];z564abe0129=
(0x16eb+764-0x19e0);(*this)=z37ef40bf5d;}ze230f62758::ze230f62758(const 
ze230f62758&z37ef40bf5d){data=new float[z37ef40bf5d.z564abe0129];z564abe0129=
z37ef40bf5d.z564abe0129;(*this)=z37ef40bf5d;}ze230f62758::~ze230f62758(){delete[
]data;}ze230f62758&ze230f62758::operator=(const z43c30c772b&z37ef40bf5d){for(int
 i=(0x53f+5270-0x19d5);i<(0x823+1370-0xd7a);i++)data[i]=z37ef40bf5d(i);return(*
this);}ze230f62758&ze230f62758::operator=(const zc996524f70&z37ef40bf5d){for(int
 i=(0x12c7+550-0x14ed);i<(0x1241+4088-0x2235);i++)data[i]=z37ef40bf5d(i);return(
*this);}ze230f62758&ze230f62758::operator=(const z0b9a2fd2df&z37ef40bf5d){for(
int i=(0x1c03+2633-0x264c);i<(0x490+6439-0x1db1);i++)data[i]=z37ef40bf5d(i);
return(*this);}ze230f62758&ze230f62758::operator=(const zcab2ae559c&z37ef40bf5d)
{for(int i=(0xe25+5133-0x2232);i<(0x13b0+3482-0x2143);i++)data[i]=z37ef40bf5d(i)
;return(*this);}ze230f62758&ze230f62758::operator=(const ze230f62758&z37ef40bf5d
){for(int i=(0xfc7+1740-0x1693);i<z564abe0129;i++)data[i]=z37ef40bf5d.data[i];
return(*this);}ze230f62758 ze230f62758::operator*(float z9aabdad99d)const{
ze230f62758 zd094a88178(z564abe0129);for(int i=(0x7a0+3334-0x14a6);i<z564abe0129
;i++)zd094a88178.data[i]=data[i]*z9aabdad99d;return(zd094a88178);}ze230f62758 
ze230f62758::operator/(float z9aabdad99d)const{ze230f62758 zd094a88178(
z564abe0129);for(int i=(0xb0d+3801-0x19e6);i<z564abe0129;i++)zd094a88178.data[i]
=data[i]/z9aabdad99d;return(zd094a88178);}ze230f62758 ze230f62758::operator+(
const ze230f62758&z37ef40bf5d)const{ze230f62758 zd094a88178(z564abe0129);for(int
 i=(0x404+4695-0x165b);i<z564abe0129;i++)zd094a88178.data[i]=data[i]+z37ef40bf5d
.data[i];return(zd094a88178);}ze230f62758 ze230f62758::operator-(const 
ze230f62758&z37ef40bf5d)const{ze230f62758 zd094a88178(z564abe0129);for(int i=
(0x1fc+2289-0xaed);i<z564abe0129;i++)zd094a88178.data[i]=data[i]-z37ef40bf5d.
data[i];return(zd094a88178);}float ze230f62758::operator*(const z43c30c772b&
z37ef40bf5d)const{float retVal=0.0f;for(int i=(0xab7+2363-0x13f2);i<
(0x1774+667-0x1a0c);i++)retVal+=(data[i]*z37ef40bf5d(i));return(retVal);}float 
ze230f62758::operator*(const zc996524f70&z37ef40bf5d)const{float retVal=0.0f;for
(int i=(0x993+2370-0x12d5);i<(0x36+4875-0x133d);i++)retVal+=(data[i]*z37ef40bf5d
(i));return(retVal);}float ze230f62758::operator*(const z0b9a2fd2df&z37ef40bf5d)
const{float retVal=0.0f;for(int i=(0x1bf3+1339-0x212e);i<(0x1835+3483-0x25ca);i
++)retVal+=(data[i]*z37ef40bf5d(i));return(retVal);}float ze230f62758::operator*
(const zcab2ae559c&z37ef40bf5d)const{float retVal=0.0f;for(int i=
(0x1599+4275-0x264c);i<(0x1063+2031-0x184b);i++)retVal+=(data[i]*z37ef40bf5d(i))
;return(retVal);}float ze230f62758::operator*(const ze230f62758&z37ef40bf5d)
const{float retVal=0.0f;for(int i=(0x11e0+4575-0x23bf);i<z564abe0129;i++)retVal
+=(data[i]*z37ef40bf5d.data[i]);return(retVal);}void ze230f62758::operator*=(
float z9aabdad99d){for(int i=(0x1a47+10-0x1a51);i<z564abe0129;i++)data[i]*=
z9aabdad99d;}void ze230f62758::operator/=(float z9aabdad99d){for(int i=
(0x174+6741-0x1bc9);i<z564abe0129;i++)data[i]/=z9aabdad99d;}void ze230f62758::
operator+=(const ze230f62758&z37ef40bf5d){for(int i=(0x140b+505-0x1604);i<
z564abe0129;i++)data[i]+=z37ef40bf5d.data[i];}void ze230f62758::operator-=(const
 ze230f62758&z37ef40bf5d){for(int i=(0x11d5+1587-0x1808);i<z564abe0129;i++)data[
i]-=z37ef40bf5d.data[i];}
