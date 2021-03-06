#include "MoMtGeom.h"
#include "MoCmLanguage.h"

MO_NAMESPACE_BEGIN

//============================================================
// <T>序列化数据内容到输出流。</T>
// 
// @param pOutput 输出流
// @return 处理结果
//============================================================
TResult SFloatRectangle::Serialize(IDataOutput* pOutput){
   MO_CHECK(pOutput, return ENull);
   pOutput->WriteFloat(left);
   pOutput->WriteFloat(top);
   pOutput->WriteFloat(width);
   pOutput->WriteFloat(height);
   return ESuccess;
}

//============================================================
// <T>从输入流反序列化数据内容。</T>
// 
// @param pInput 输入流
// @return 处理结果
//============================================================
TResult SFloatRectangle::Unserialize(IDataInput* pInput){
   MO_CHECK(pInput, return ENull);
   left = pInput->ReadFloat();
   top = pInput->ReadFloat();
   width = pInput->ReadFloat();
   height = pInput->ReadFloat();
   return ESuccess;
}

MO_NAMESPACE_END
