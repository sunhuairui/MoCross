#include "MoScript.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FScriptObject, FInstance);

//============================================================
// <T>构造脚本对象。</T>
//============================================================
FScriptObject::FScriptObject(){
}

//============================================================
// <T>析构脚本对象。</T>
//============================================================
FScriptObject::~FScriptObject(){
}

//============================================================
// <T>打开处理。</T>
//
// @return 处理结果
//============================================================
TResult FScriptObject::Open(){
   return ESuccess;
}

//============================================================
// <T>关闭处理。</T>
//
// @return 处理结果
//============================================================
TResult FScriptObject::Close(){
   return ESuccess;
}

MO_NAMESPACE_END
