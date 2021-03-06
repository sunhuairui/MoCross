#include "MoFrContent3dMaterial.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRs3dMaterialTexture, FInstance);

//============================================================
// <T>构造资源3D材质纹理。</T>
//============================================================
FRs3dMaterialTexture::FRs3dMaterialTexture(){
}

//============================================================
// <T>析构资源3D材质纹理。</T>
//============================================================
FRs3dMaterialTexture::~FRs3dMaterialTexture(){
}

//============================================================
// <T>从输入流里反序列化信息内容</T>
//
// @param pInput 输入流
// @return 处理结果
//============================================================
TResult FRs3dMaterialTexture::Unserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   // 读取代码
   _code.Unserialize(pInput);
   _packCode.Unserialize(pInput);
   // 读取纹理名称
   _textureName.UnserializeAutomatic(pInput);
   return ESuccess;
}

MO_NAMESPACE_END
