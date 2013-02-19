

#include "7Vector.h"
#include "4X4Matrix.h"
zcab2ae559c::zcab2ae559c(){}zcab2ae559c::zcab2ae559c(const zcab2ae559c&
z37ef40bf5d){(*this)=z37ef40bf5d;}zcab2ae559c::zcab2ae559c(const zc996524f70&q){
Q=q;X.clear();}zcab2ae559c::zcab2ae559c(const z43c30c772b&x){X=x;Q.z8079139e84()
;}zcab2ae559c::zcab2ae559c(const zc996524f70&q,const z43c30c772b&x){Q=q;X=x;}
zcab2ae559c::zcab2ae559c(const float zcec140f672[(0xd85+743-0x1068)][
(0x168d+3484-0x2425)]){za35174b61d(zcec140f672);}zcab2ae559c::zcab2ae559c(const 
z38505d4d88&zcec140f672){za35174b61d(zcec140f672);}zcab2ae559c::zcab2ae559c(
float z6fafebb892,const z43c30c772b&z8a7e6753de,const z43c30c772b&z34a925d9ab){
zcab2ae559c ze2ae80e788;ze2ae80e788.z8079139e84();ze2ae80e788.X(
(0x1dd+7563-0x1f68))=-z8a7e6753de((0x1c78+565-0x1ead));ze2ae80e788.X(
(0x1434+3045-0x2018))=-z8a7e6753de((0x1932+1333-0x1e66));ze2ae80e788.X(
(0x1429+2093-0x1c54))=-z8a7e6753de((0x108c+494-0x1278));zcab2ae559c z35ba163b52;
z35ba163b52.z8079139e84();z35ba163b52.X=z8a7e6753de;zcab2ae559c z3c9bf1dbbf;
z3c9bf1dbbf.z8079139e84();z3c9bf1dbbf.Q.zd55d782e18(z6fafebb892,z34a925d9ab);(*
this)=z35ba163b52*z3c9bf1dbbf*ze2ae80e788;}zcab2ae559c::~zcab2ae559c(){}void 
zcab2ae559c::za35174b61d(float zcec140f672[(0xfc+3465-0xe81)][
(0x11e4+581-0x1425)]){z38505d4d88 zec880c2e91(zcec140f672);(*this)=zec880c2e91.
ze6bd9d7d6b();}void zcab2ae559c::za35174b61d(const z38505d4d88&zcec140f672){(*
this)=zcec140f672.ze6bd9d7d6b();}z43c30c772b zcab2ae559c::z8d8ecc4db8(int 
z93438c6aa1)const{return(Q.z8d8ecc4db8(z93438c6aa1));}void zcab2ae559c::
z8079139e84(){Q.z8079139e84();X.clear();}z38505d4d88 zcab2ae559c::zc48c746a21()
const{return(z38505d4d88(Q.zc48c746a21(),X));}void zcab2ae559c::z692df07ea8(
float zcec140f672[(0x8cc+2655-0x1327)][(0xeb2+808-0x11d6)])const{
z38505d4d88 z52754d10b7(zc48c746a21());for(int i=(0x8f6+1137-0xd67);i<
(0xb49+6908-0x2642);i++){for(int j=(0xe55+2097-0x1686);j<(0x147b+4533-0x262d);j
++)zcec140f672[i][j]=z52754d10b7.M(i,j);zcec140f672[i][(0xb1f+4138-0x1b46)]=
z52754d10b7.X(i);}zcec140f672[(0x72c+4287-0x17e8)][(0x12a9+5046-0x265f)]=0.0f;
zcec140f672[(0x21a8+842-0x24ef)][(0x46b+8786-0x26bc)]=0.0f;zcec140f672[
(0x8eb+720-0xbb8)][(0x549+5764-0x1bcb)]=0.0f;zcec140f672[(0xe7+7452-0x1e00)][
(0x452+5930-0x1b79)]=1.0f;}zcab2ae559c&zcab2ae559c::operator=(const zcab2ae559c&
z37ef40bf5d){Q=z37ef40bf5d.Q;X=z37ef40bf5d.X;return(*this);}void zcab2ae559c::
z8b98bfb2be(const zcab2ae559c&z7b058c25be,const zcab2ae559c&z6e0310fb34){X=
z7b058c25be.X+(z7b058c25be.Q*z6e0310fb34.X);Q=z7b058c25be.Q*z6e0310fb34.Q;}
zcab2ae559c zcab2ae559c::operator*(const zcab2ae559c&z37ef40bf5d)const{
zcab2ae559c zd094a88178;zd094a88178.X=X+(Q*z37ef40bf5d.X);zd094a88178.Q=Q*
z37ef40bf5d.Q;zd094a88178.Q.normalize();return(zd094a88178);}void zcab2ae559c::
operator*=(const zcab2ae559c&z37ef40bf5d){X+=(Q*z37ef40bf5d.X);Q*=z37ef40bf5d.Q;
}z43c30c772b zcab2ae559c::operator*(const z43c30c772b&z37ef40bf5d)const{
return(X+(Q*z37ef40bf5d));}void zcab2ae559c::z0d5a1d870e(){(*this)=z2a56b020d9()
;}zcab2ae559c zcab2ae559c::z2a56b020d9()const{zcab2ae559c zd094a88178;
zd094a88178.Q=Q.z2a56b020d9();zd094a88178.X=(zd094a88178.Q*X)*-1.0f;return(
zd094a88178);}void zcab2ae559c::z4174ee2a49(const zcab2ae559c&z0755af5496,const 
zcab2ae559c&z8930959f0b,float t){
Q.z4174ee2a49(z0755af5496.Q,z8930959f0b.Q,t);X.z4174ee2a49(z0755af5496.X,
z8930959f0b.X,t);}const zcab2ae559c zcab2ae559c::z22ca8a1799(zc996524f70::
z6dbe01008c,z43c30c772b::z69267038d3);
