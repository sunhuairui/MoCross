#include "MoFgBase.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderableAttribute, FInstance);

//============================================================
// <T>构造渲染对象属性。</T>
//============================================================
FRenderableAttribute::FRenderableAttribute(){
   _valid = EFalse;
   _formatCd = ERenderAttributeFormat_Unknown;
   _offset = -1;
   //_slot = -1;
}

//============================================================
// <T>析构渲染对象属性。</T>
//============================================================
FRenderableAttribute::~FRenderableAttribute(){
}

//============================================================
// <T>检查是否有效。</T>
//
// @return 是否有效
//============================================================
TBool FRenderableAttribute::CheckValid(){
   if(_valid){
      return ETrue;
   }
   // 检查代码
   if(_code.IsEmpty()){
      return EFalse;
   }
   // 检查格式
   if(_formatCd == ERenderAttributeFormat_Unknown){
      return EFalse;
   }
   // 检查偏移
   if(_offset < 0){
      return EFalse;
   }
   // 检查缓冲
   if(!_graphicsObject.IsValid()){
      return EFalse;
   }
   // 有效处理
   _valid = ETrue;
   return _valid;
}

MO_NAMESPACE_END
