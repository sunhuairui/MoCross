#include "MoEgFont.h"

MO_NAMESPACE_BEGIN

MO_CLASS_ABSTRACT_IMPLEMENT_INHERITS(FFont, FInstance);

//============================================================
// <T>构造字体。</T>
//============================================================
FFont::FFont(){
   _code = 0;
   _statusOpen = EFalse;
   MO_CLEAR(_pConsole);
}

//============================================================
// <T>析构字体。</T>
//============================================================
FFont::~FFont(){
}

//============================================================
// <T>打开处理。</T>
//
// @return 处理结果
//============================================================
TResult FFont::Open(){
   _statusOpen = ETrue;
   return ESuccess;
}

//============================================================
// <T>关闭处理。</T>
//
// @return 处理结果
//============================================================
TResult FFont::Close(){
   _statusOpen = EFalse;
   return ESuccess;
}

MO_NAMESPACE_END
