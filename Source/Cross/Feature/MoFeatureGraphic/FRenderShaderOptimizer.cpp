#include "MoFgRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FRenderShaderOptimizer, FInstance);

//============================================================
// <T>构造渲染脚本优化器。</T>
//============================================================
FRenderShaderOptimizer::FRenderShaderOptimizer(){
}

//============================================================
// <T>析构渲染脚本优化器。</T>
//============================================================
FRenderShaderOptimizer::~FRenderShaderOptimizer(){
}

//============================================================
// <T>转换脚本。</T>
//
// @param pOutputScript 输出脚本
// @param pInputScript 输入脚本
// @return 处理结果
//============================================================
TResult FRenderShaderOptimizer::Convert(MString* pOutputScript, MString* pInputScript){
   pOutputScript->AssignPointer(pInputScript);
   return ESuccess;
}

MO_NAMESPACE_END
