#include "MoE2Display.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>构造显示精灵。</T>
//============================================================
FSprite::FSprite(){
   //_objectCd |= EComponent_Renderable;
   _typeCd = EDisplayType_Sprite;
}

//============================================================
// <T>析构显示精灵。</T>
//============================================================
FSprite::~FSprite(){
}

MO_NAMESPACE_END
