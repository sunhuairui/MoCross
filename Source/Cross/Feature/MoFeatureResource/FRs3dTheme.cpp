#include "MoFrContent3dTheme.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>构造资源3D主题。</T>
//============================================================
FRs3dTheme::FRs3dTheme(){
}

//============================================================
// <T>析构资源3D主题。</T>
//============================================================
FRs3dTheme::~FRs3dTheme(){
}

//============================================================
// <T>从输入流里反序列化信息内容</T>
//
// @param pInput 输入流
// @return 处理结果
//============================================================
TResult FRs3dTheme::Unserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   return ESuccess;
}

MO_NAMESPACE_END
