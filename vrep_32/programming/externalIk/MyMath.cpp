

#include "MyMath.h"


z16efbd9f9a::z16efbd9f9a(){}z16efbd9f9a::~z16efbd9f9a(){}void z16efbd9f9a::
zcaaed61082(float z377e41bed0,float z9454d262ab,float&value){if(value>
z9454d262ab)value=z9454d262ab;if(value<z377e41bed0)value=z377e41bed0;}void 
z16efbd9f9a::zcaaed61082(int z377e41bed0,int z9454d262ab,int&value){if(value>
z9454d262ab)value=z9454d262ab;if(value<z377e41bed0)value=z377e41bed0;}float 
z16efbd9f9a::zdd8ee54467(float z37ef40bf5d){if(!zf0149f1075(z37ef40bf5d)){


return(0.0f);}if(z37ef40bf5d>=1.0f)return(piVal*0.5f);if(z37ef40bf5d<=-1.0f)
return(-piVal*0.5f);return(asinf(z37ef40bf5d));}float z16efbd9f9a::zca43de2d36(
float z37ef40bf5d){if(!zf0149f1075(z37ef40bf5d)){


return(0.0f);}if(z37ef40bf5d>=1.0f)return(0.0f);if(z37ef40bf5d<=-1.0f)return(
piVal);return(acosf(z37ef40bf5d));}float z16efbd9f9a::zf85e575a7b(float 
z37ef40bf5d,float zf667805127){if((!zf0149f1075(z37ef40bf5d))||(!zf0149f1075(
zf667805127))){


return(0.0f);}if(zf667805127==0.0f)return(0.0f);return(fmod(z37ef40bf5d,
zf667805127));}double z16efbd9f9a::z009c5a5a9d(double z37ef40bf5d,double 
zf667805127){if((!z17974f893f(z37ef40bf5d))||(!z17974f893f(zf667805127))){


return(0.0);}if(zf667805127==0.0)return(0.0);return(fmod(z37ef40bf5d,zf667805127
));}bool z16efbd9f9a::zf0149f1075(float z37ef40bf5d){return((!VREP_IS_NAN(
z37ef40bf5d))&&(fabs(z37ef40bf5d)!=std::numeric_limits<float>::infinity()));}
bool z16efbd9f9a::z17974f893f(double z37ef40bf5d){return((!VREP_IS_NAN(
z37ef40bf5d))&&(fabs(z37ef40bf5d)!=std::numeric_limits<double>::infinity()));}
