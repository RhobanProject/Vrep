

#include "MMatrix.h"
#include "mathDefines.h"
z957fc62c41::z957fc62c41(){}z957fc62c41::z957fc62c41(int z24dcc27d94,int 
zf6188af592):data(new float[z24dcc27d94*zf6188af592]),z3b6bdfe927(z24dcc27d94),
z2468d7d02c(zf6188af592){}z957fc62c41::z957fc62c41(const ze2b7e09268&zcec140f672
):data(new float[(0x757+6613-0x2123)]){z3b6bdfe927=(0xb04+3359-0x1820);
z2468d7d02c=(0x6f2+7359-0x23ae);(*this)=zcec140f672;}z957fc62c41::z957fc62c41(
const z38505d4d88&zcec140f672):data(new float[(0xaf9+3936-0x1a49)]){z3b6bdfe927=
(0x161c+3809-0x24f9);z2468d7d02c=(0x2b+1030-0x42d);(*this)=zcec140f672;}
z957fc62c41::z957fc62c41(const z11fde56c28&zcec140f672):data(new float[
(0x125+4239-0x1190)]){z3b6bdfe927=(0xfcb+5471-0x2524);z2468d7d02c=
(0xb7c+2864-0x16a6);(*this)=zcec140f672;}z957fc62c41::z957fc62c41(const 
z957fc62c41&zcec140f672):data(new float[zcec140f672.z3b6bdfe927*zcec140f672.
z2468d7d02c]){z3b6bdfe927=zcec140f672.z3b6bdfe927;z2468d7d02c=zcec140f672.
z2468d7d02c;(*this)=zcec140f672;}z957fc62c41::~z957fc62c41(){delete[]data;}void 
z957fc62c41::clear(){for(int i=(0x9d6+6965-0x250b);i<(z2468d7d02c*z3b6bdfe927);i
++)data[i]=0.0f;}void z957fc62c41::z8079139e84(){for(int i=(0xbd6+3586-0x19d8);i
<z3b6bdfe927;i++){for(int j=(0x1596+2245-0x1e5b);j<z2468d7d02c;j++){if(i!=j)(*
this)(i,j)=0.0f;else(*this)(i,j)=1.0f;}}}z957fc62c41 z957fc62c41::operator*(
const ze2b7e09268&zcec140f672)const{z957fc62c41 zc025341aa2(z3b6bdfe927,
(0x9b9+2671-0x1425));for(int i=(0x5d2+6667-0x1fdd);i<z3b6bdfe927;i++){for(int j=
(0x869+5914-0x1f83);j<(0x634+5761-0x1cb2);j++){zc025341aa2(i,j)=0.0f;for(int k=
(0x206d+1532-0x2669);k<(0x110b+4684-0x2354);k++)zc025341aa2(i,j)+=((*this)(i,k)*
zcec140f672.z7bd9fa8427[j](k));}}return(zc025341aa2);}z957fc62c41 z957fc62c41::
operator*(const z38505d4d88&zcec140f672)const{z957fc62c41 zc025341aa2(
z3b6bdfe927,(0x22a6+816-0x25d2));for(int i=(0x1d53+2039-0x254a);i<z3b6bdfe927;i
++){for(int j=(0xc43+1787-0x133e);j<(0xf51+989-0x132b);j++){zc025341aa2(i,j)=
0.0f;for(int k=(0x1ae3+1620-0x2137);k<(0x262+4047-0x122e);k++)zc025341aa2(i,j)+=
((*this)(i,k)*zcec140f672.M.z7bd9fa8427[j](k));}zc025341aa2(i,
(0x8b0+3671-0x1704))=(*this)(i,(0xde5+3341-0x1aef));for(int k=
(0xd76+2370-0x16b8);k<(0x220a+768-0x2507);k++)zc025341aa2(i,(0x904+7081-0x24aa))
+=((*this)(i,k)*zcec140f672.X(k));}return(zc025341aa2);}z957fc62c41 z957fc62c41
::operator*(const z11fde56c28&zcec140f672)const{z957fc62c41 zc025341aa2(
z3b6bdfe927,(0xb07+4113-0x1b12));for(int i=(0x8e7+1961-0x1090);i<z3b6bdfe927;i++
){for(int j=(0x17f3+624-0x1a63);j<(0x3c9+1151-0x842);j++){zc025341aa2(i,j)=0.0f;
for(int k=(0x6af+3083-0x12ba);k<(0x834+1365-0xd83);k++)zc025341aa2(i,j)+=((*this
)(i,k)*zcec140f672(k,j));}}return(zc025341aa2);}z957fc62c41 z957fc62c41::
operator*(const z957fc62c41&zcec140f672)const{z957fc62c41 zc025341aa2(
z3b6bdfe927,zcec140f672.z2468d7d02c);for(int i=(0x1893+2788-0x2377);i<
z3b6bdfe927;i++){for(int j=(0xb53+4882-0x1e65);j<zcec140f672.z2468d7d02c;j++){
zc025341aa2(i,j)=0.0f;for(int k=(0x1af6+558-0x1d24);k<z2468d7d02c;k++)
zc025341aa2(i,j)+=((*this)(i,k)*zcec140f672(k,j));}}return(zc025341aa2);}
z957fc62c41 z957fc62c41::operator+(const z957fc62c41&zcec140f672)const{
z957fc62c41 zc025341aa2(z3b6bdfe927,z2468d7d02c);for(int i=(0x487+8542-0x25e5);i
<(z3b6bdfe927*z2468d7d02c);i++)zc025341aa2.data[i]=data[i]+zcec140f672.data[i];
return(zc025341aa2);}z957fc62c41 z957fc62c41::operator-(const z957fc62c41&
zcec140f672)const{z957fc62c41 zc025341aa2(z3b6bdfe927,z2468d7d02c);for(int i=
(0xb4c+5789-0x21e9);i<(z3b6bdfe927*z2468d7d02c);i++)zc025341aa2.data[i]=data[i]-
zcec140f672.data[i];return(zc025341aa2);}z957fc62c41 z957fc62c41::operator*(
float z9aabdad99d)const{z957fc62c41 zc025341aa2(z3b6bdfe927,z2468d7d02c);for(int
 i=(0x8f9+2500-0x12bd);i<(z3b6bdfe927*z2468d7d02c);i++)zc025341aa2.data[i]=data[
i]*z9aabdad99d;return(zc025341aa2);}z957fc62c41 z957fc62c41::operator/(float 
z9aabdad99d)const{z957fc62c41 zc025341aa2(z3b6bdfe927,z2468d7d02c);for(int i=
(0x519+7037-0x2096);i<(z3b6bdfe927*z2468d7d02c);i++)zc025341aa2.data[i]=data[i]/
z9aabdad99d;return(zc025341aa2);}void z957fc62c41::operator*=(const z957fc62c41&
zcec140f672){(*this)=(*this)*zcec140f672;}void z957fc62c41::operator+=(const 
z957fc62c41&zcec140f672){for(int i=(0x874+1757-0xf51);i<(z3b6bdfe927*z2468d7d02c
);i++)data[i]+=zcec140f672.data[i];}void z957fc62c41::operator-=(const 
z957fc62c41&zcec140f672){for(int i=(0x93a+32-0x95a);i<(z3b6bdfe927*z2468d7d02c);
i++)data[i]-=zcec140f672.data[i];}void z957fc62c41::operator*=(float z9aabdad99d
){for(int i=(0x1a26+2511-0x23f5);i<(z3b6bdfe927*z2468d7d02c);i++)data[i]*=
z9aabdad99d;}void z957fc62c41::operator/=(float z9aabdad99d){for(int i=
(0xbd1+6487-0x2528);i<(z3b6bdfe927*z2468d7d02c);i++)data[i]/=z9aabdad99d;}
ze230f62758 z957fc62c41::operator*(const ze230f62758&z37ef40bf5d)const{
ze230f62758 zd094a88178(z37ef40bf5d.z564abe0129);for(int i=(0x193b+1645-0x1fa8);
i<z3b6bdfe927;i++){zd094a88178(i)=0.0f;for(int k=(0x10bb+1868-0x1807);k<
z2468d7d02c;k++)zd094a88178(i)+=((*this)(i,k)*z37ef40bf5d(k));}return(
zd094a88178);}z957fc62c41&z957fc62c41::operator=(const ze2b7e09268&zcec140f672){
for(int i=(0x1d6b+893-0x20e8);i<(0x1dfc+395-0x1f84);i++){for(int j=
(0x699+4001-0x163a);j<(0xa08+3670-0x185b);j++)(*this)(i,j)=zcec140f672.
z7bd9fa8427[j](i);}return(*this);}z957fc62c41&z957fc62c41::operator=(const 
z38505d4d88&zcec140f672){for(int i=(0x1702+1419-0x1c8d);i<(0x710+7054-0x229b);i
++){for(int j=(0x8b+8622-0x2239);j<(0x1206+721-0x14d4);j++)(*this)(i,j)=
zcec140f672.M.z7bd9fa8427[j](i);(*this)(i,(0x268c+97-0x26ea))=zcec140f672.X(i);}
(*this)((0x3d5+2810-0xecc),(0xd78+4775-0x201f))=0.0f;(*this)((0x2f0+2814-0xdeb),
(0x1f25+1806-0x2632))=0.0f;(*this)((0xd81+6012-0x24fa),(0x8ac+6897-0x239b))=0.0f
;(*this)((0x857+5624-0x1e4c),(0x1b37+1257-0x201d))=1.0f;return(*this);}
z957fc62c41&z957fc62c41::operator=(const z11fde56c28&zcec140f672){for(int i=
(0x2c9+791-0x5e0);i<(0x84b+6913-0x2346);i++){for(int j=(0x722+2078-0xf40);j<
(0x1c63+601-0x1eb6);j++)(*this)(i,j)=zcec140f672(i,j);}return(*this);}
z957fc62c41&z957fc62c41::operator=(const z957fc62c41&zcec140f672){int t=
z3b6bdfe927*z2468d7d02c;for(int i=(0x1aa3+1411-0x2026);i<t;i++)data[i]=
zcec140f672.data[i];return(*this);}void z957fc62c41::z9b0b4ab621(){
z957fc62c41 n(z2468d7d02c,z3b6bdfe927);for(int i=(0x99d+6968-0x24d5);i<
z3b6bdfe927;i++){for(int j=(0x981+6949-0x24a6);j<z2468d7d02c;j++)n(j,i)=(*this)(
i,j);}z3b6bdfe927=n.z3b6bdfe927;z2468d7d02c=n.z2468d7d02c;(*this)=n;}bool 
z957fc62c41::z0d5a1d870e(){

int n=z3b6bdfe927;int i,zbbbe02f214,j,k,l,z1b71a707c2;float ze1cfbd21e7,
zeb9fa2b8fc,zfd4dc5c06c;int*ze26290c3cc=new int[n+(0x3d0+2129-0xc20)];int*
z0ac3bba742=new int[n+(0x1236+1200-0x16e5)];int*zf9635b9851=new int[n+
(0x699+6327-0x1f4f)];for(j=(0xc04+5201-0x2054);j<=n;j++)zf9635b9851[j]=
(0xae1+7066-0x267b);for(i=(0x730+6698-0x2159);i<=n;i++){int z7e215d3461=-
(0x412+7364-0x20d5);ze1cfbd21e7=0.0f;for(j=(0x12d9+3849-0x21e1);j<=n;j++){if(
zf9635b9851[j]!=(0x1f1d+428-0x20c8)){for(k=(0x1128+2374-0x1a6d);k<=n;k++){if(
zf9635b9851[k]==(0x35a+7568-0x20ea)){if(fabs((*this)(j-(0x10a7+1729-0x1767),k-
(0x488+7722-0x22b1)))>=ze1cfbd21e7){ze1cfbd21e7=(float)fabs((*this)(j-
(0x1dd0+529-0x1fe0),k-(0x863+10-0x86c)));zbbbe02f214=j;z7e215d3461=k;}}else if(
zf9635b9851[k]>(0x13d2+1054-0x17ef)){
delete[]zf9635b9851;delete[]z0ac3bba742;delete[]ze26290c3cc;return(false);}}}}if
(z7e215d3461==-(0xb38+6826-0x25e1)){
delete[]zf9635b9851;delete[]z0ac3bba742;delete[]ze26290c3cc;return(false);}++(
zf9635b9851[z7e215d3461]);if(zbbbe02f214!=z7e215d3461){for(l=(0xaa1+1377-0x1001)
;l<=n;l++){float z52754d10b7=(*this)(zbbbe02f214-(0x30a+6098-0x1adb),l-
(0x183b+3255-0x24f1));(*this)(zbbbe02f214-(0x4+6120-0x17eb),l-(0x5b+1616-0x6aa))
=(*this)(z7e215d3461-(0xe27+1473-0x13e7),l-(0x845+4602-0x1a3e));(*this)(
z7e215d3461-(0x1266+2322-0x1b77),l-(0x9f0+2834-0x1501))=z52754d10b7;}}
z0ac3bba742[i]=zbbbe02f214;ze26290c3cc[i]=z7e215d3461;if((*this)(z7e215d3461-
(0x1394+3960-0x230b),z7e215d3461-(0x18d4+1872-0x2023))==0.0f){
delete[]zf9635b9851;delete[]z0ac3bba742;delete[]ze26290c3cc;return(false);}
zfd4dc5c06c=1.0f/(*this)(z7e215d3461-(0x54b+664-0x7e2),z7e215d3461-
(0x19eb+557-0x1c17));(*this)(z7e215d3461-(0xca4+1366-0x11f9),z7e215d3461-
(0x1541+1968-0x1cf0))=1.0f;for(l=(0x7fa+635-0xa74);l<=n;l++)(*this)(z7e215d3461-
(0xe94+3281-0x1b64),l-(0x1878+581-0x1abc))*=zfd4dc5c06c;for(z1b71a707c2=
(0x860+290-0x981);z1b71a707c2<=n;z1b71a707c2++){if(z1b71a707c2!=z7e215d3461){
zeb9fa2b8fc=(*this)(z1b71a707c2-(0x121f+4225-0x229f),z7e215d3461-
(0xfb9+3138-0x1bfa));(*this)(z1b71a707c2-(0x11aa+78-0x11f7),z7e215d3461-
(0x125a+4740-0x24dd))=0.0f;for(l=(0x103c+4972-0x23a7);l<=n;l++)(*this)(
z1b71a707c2-(0x34b+3430-0x10b0),l-(0x1e96+1574-0x24bb))-=(*this)(z7e215d3461-
(0x104f+895-0x13cd),l-(0x12ca+3988-0x225d))*zeb9fa2b8fc;}}}for(l=n;l>=
(0x1a9d+270-0x1baa);l--){if(z0ac3bba742[l]!=ze26290c3cc[l]){for(k=
(0x225+7295-0x1ea3);k<=n;k++){float z52754d10b7=(*this)(k-(0xf3f+2235-0x17f9),
z0ac3bba742[l]-(0xc8d+4759-0x1f23));(*this)(k-(0x1b40+1803-0x224a),z0ac3bba742[l
]-(0x566+6532-0x1ee9))=(*this)(k-(0xda+8314-0x2153),ze26290c3cc[l]-
(0x5db+1861-0xd1f));(*this)(k-(0x2d5+2173-0xb51),ze26290c3cc[l]-
(0x119+7486-0x1e56))=z52754d10b7;}}}delete[]zf9635b9851;delete[]z0ac3bba742;
delete[]ze26290c3cc;return(true);}
