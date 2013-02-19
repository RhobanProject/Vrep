

#include "4X4Matrix.h"
#include "4X4FullMatrix.h"
#include "MMatrix.h"
z38505d4d88::z38505d4d88(){}z38505d4d88::z38505d4d88(const ze2b7e09268&
zcec140f672,const z43c30c772b&x){M=zcec140f672;X=x;}z38505d4d88::z38505d4d88(
const zcab2ae559c&zf2dc2f6435){M=zf2dc2f6435.Q.zc48c746a21();X=zf2dc2f6435.X;}
z38505d4d88::z38505d4d88(const z38505d4d88&zcec140f672){(*this)=zcec140f672;}
z38505d4d88::z38505d4d88(const z957fc62c41&zcec140f672){(*this)=zcec140f672;}
z38505d4d88::z38505d4d88(const float zcec140f672[(0x47f+8004-0x23bf)][
(0x741+6467-0x2080)]){for(int i=(0x442+2372-0xd86);i<(0x925+1658-0xf9c);i++){for
(int j=(0x173+3206-0xdf9);j<(0xb07+3123-0x1737);j++)M(i,j)=zcec140f672[i][j];X(i
)=zcec140f672[i][(0x3a6+5778-0x1a35)];}}z38505d4d88::z38505d4d88(const 
z43c30c772b&x,const z43c30c772b&y,const z43c30c772b&zf4af1ac000,const 
z43c30c772b&z8a7e6753de){M.za35174b61d(x,y,zf4af1ac000);X=z8a7e6753de;}
z38505d4d88::~z38505d4d88(){}void z38505d4d88::z8079139e84(){M.z8079139e84();X.
clear();}z38505d4d88 z38505d4d88::operator*(const z957fc62c41&zcec140f672)const{
z38505d4d88 zc025341aa2((*this)*z38505d4d88(zcec140f672));return(zc025341aa2);}
z38505d4d88&z38505d4d88::operator=(const z957fc62c41&zcec140f672){M.z7bd9fa8427[
(0xb68+2430-0x14e6)]((0x31c+6683-0x1d37))=zcec140f672((0x1c9f+2358-0x25d5),
(0xdc7+3298-0x1aa9));M.z7bd9fa8427[(0xa26+5826-0x20e8)]((0x4c+7729-0x1e7c))=
zcec140f672((0x1420+4026-0x23d9),(0x17c6+176-0x1876));M.z7bd9fa8427[
(0xc53+2970-0x17ed)]((0x7bb+2151-0x1020))=zcec140f672((0x6e2+5494-0x1c56),
(0x190f+2268-0x21eb));M.z7bd9fa8427[(0x131a+1383-0x1880)]((0x4f9+3854-0x1407))=
zcec140f672((0xc0c+4300-0x1cd8),(0x91b+2444-0x12a6));M.z7bd9fa8427[
(0xb6f+765-0xe6b)]((0xb3c+1168-0xfcb))=zcec140f672((0x465+7769-0x22bd),
(0x686+3420-0x13e1));M.z7bd9fa8427[(0xaa+3783-0xf70)]((0x1aea+866-0x1e4a))=
zcec140f672((0x1319+3718-0x219d),(0x165a+1825-0x1d7a));M.z7bd9fa8427[
(0x671+3693-0x14dc)]((0x1056+5273-0x24ef))=zcec140f672((0x15a1+4350-0x269f),
(0x60a+6038-0x1d9e));M.z7bd9fa8427[(0x17a4+1029-0x1ba7)]((0x473+2064-0xc82))=
zcec140f672((0x1cc+1797-0x8d0),(0x59d+293-0x6c0));M.z7bd9fa8427[
(0x1851+34-0x1871)]((0x531+7703-0x2346))=zcec140f672((0x1e84+186-0x1f3c),
(0x12e1+1428-0x1873));X((0x11df+2762-0x1ca9))=zcec140f672((0x175+6612-0x1b49),
(0x1656+2116-0x1e97));X((0x1f80+1535-0x257e))=zcec140f672((0x11a4+2879-0x1ce2),
(0xdab+1422-0x1336));X((0x959+6869-0x242c))=zcec140f672((0x8d8+725-0xbab),
(0x6d9+3190-0x134c));return(*this);}z38505d4d88&z38505d4d88::operator=(const 
zefb78627df&zcec140f672){M.z7bd9fa8427[(0xc52+5766-0x22d8)]((0xea+9575-0x2651))=
zcec140f672((0x1d3a+1936-0x24ca),(0x5c+1187-0x4ff));M.z7bd9fa8427[
(0x570+1891-0xcd3)]((0x1fd4+1137-0x2444))=zcec140f672((0x546+3776-0x1405),
(0x199+9051-0x24f4));M.z7bd9fa8427[(0x17b5+2309-0x20ba)]((0x19fb+1345-0x1f3a))=
zcec140f672((0x10c4+3292-0x1d9e),(0x7ea+3650-0x162c));M.z7bd9fa8427[
(0xe91+2713-0x1929)]((0x417+2882-0xf59))=zcec140f672((0x1439+200-0x1501),
(0x13c4+2371-0x1d06));M.z7bd9fa8427[(0xdc0+6170-0x25d9)]((0x1a+9006-0x2347))=
zcec140f672((0xf17+4804-0x21da),(0x2648+183-0x26fe));M.z7bd9fa8427[
(0x4b1+1819-0xbcb)]((0x132d+3884-0x2257))=zcec140f672((0x2396+774-0x269a),
(0x200+1119-0x65e));M.z7bd9fa8427[(0x11d6+3833-0x20cd)]((0x1bc+8201-0x21c5))=
zcec140f672((0x1b12+190-0x1bd0),(0x5d4+3662-0x1420));M.z7bd9fa8427[
(0x1649+3507-0x23fa)]((0x3c2+2851-0xee4))=zcec140f672((0xa38+4767-0x1cd6),
(0x364+3262-0x1020));M.z7bd9fa8427[(0xc22+2075-0x143b)]((0x7e6+7121-0x23b5))=
zcec140f672((0xe49+4445-0x1fa4),(0x1a75+2815-0x2572));X((0x1423+4739-0x26a6))=
zcec140f672((0x16e5+2966-0x227b),(0x1f8a+632-0x21ff));X((0x209c+1534-0x2699))=
zcec140f672((0xcda+317-0xe16),(0x23d1+105-0x2437));X((0x544+1849-0xc7b))=
zcec140f672((0x108f+2978-0x1c2f),(0xd22+3903-0x1c5e));return(*this);}zcab2ae559c
 z38505d4d88::ze6bd9d7d6b()const{return(zcab2ae559c(M.z56ed45e3d1(),X));}void 
z38505d4d88::z4174ee2a49(const z38505d4d88&z0755af5496,const z38505d4d88&
z8930959f0b,float t){
zcab2ae559c out;out.z4174ee2a49(z0755af5496.ze6bd9d7d6b(),z8930959f0b.
ze6bd9d7d6b(),t);(*this)=out;}void z38505d4d88::za07e5c055e(float z6fafebb892){
z38505d4d88 z3c9bf1dbbf;z3c9bf1dbbf.z8079139e84();z3c9bf1dbbf.M.z313e3777ba(
z6fafebb892);(*this)=z3c9bf1dbbf*(*this);}void z38505d4d88::z55c3aec048(float 
z6fafebb892){z38505d4d88 z3c9bf1dbbf;z3c9bf1dbbf.z8079139e84();z3c9bf1dbbf.M.
z515ae34e81(z6fafebb892);(*this)=z3c9bf1dbbf*(*this);}void z38505d4d88::
z762049183a(float z6fafebb892){z38505d4d88 z3c9bf1dbbf;z3c9bf1dbbf.z8079139e84()
;z3c9bf1dbbf.M.z82b593ca65(z6fafebb892);(*this)=z3c9bf1dbbf*(*this);}void 
z38505d4d88::z313e3777ba(float z6fafebb892){z8079139e84();M.z313e3777ba(
z6fafebb892);}void z38505d4d88::z515ae34e81(float z6fafebb892){z8079139e84();M.
z515ae34e81(z6fafebb892);}void z38505d4d88::z82b593ca65(float z6fafebb892){
z8079139e84();M.z82b593ca65(z6fafebb892);}void z38505d4d88::zd9b62f8bf4(float x,
float y,float zf4af1ac000){z8079139e84();X((0x71b+2980-0x12bf))=x;X(
(0x25c4+288-0x26e3))=y;X((0x51+7480-0x1d87))=zf4af1ac000;}void z38505d4d88::
zefff9b5aa4(float x,float y,float zf4af1ac000){X((0x1bb4+770-0x1eb6))+=x;X(
(0x1c01+1387-0x216b))+=y;X((0x141c+1935-0x1ba9))+=zf4af1ac000;}
