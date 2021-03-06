#include "MoFgRender.h"
#include "MoFgTechnique.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FEffect, FInstance);

//============================================================
// <T>构造渲染效果。</T>
//============================================================
FEffect::FEffect(){
}

//============================================================
// <T>析构渲染效果。</T>
//============================================================
FEffect::~FEffect(){
}

//============================================================
// <T>配置处理。</T>
//
// @return 处理结果
//============================================================
TResult FEffect::Setup(){
   // 创建程序
   _program = _renderDevice->CreateProgrom();
   _program->Setup();
   return ESuccess;
}

//============================================================
// <T>加载配置信息。</T>
//
// @param pConfig 配置处理
// @return 处理结果
//============================================================
TResult FEffect::LoadConfig(FXmlNode* pConfig){
   // 描述器加载信息
   _descriptor.LoadConfig(pConfig);
   //............................................................
   // 建立配置信息
   TXmlNodeIteratorC iterator = pConfig->NodeIteratorC();
   while(iterator.Next()){
      FXmlNode* pNode = *iterator;
      //............................................................
      // 建立参数定义集合
      if(pNode->IsName("Buffer")){
         FRenderProgramBuffer* pBuffer = _renderDevice->CreateObject<FRenderProgramBuffer>(MO_RENDEROBJECT_PROGRAM_BUFFER);
         pBuffer->LoadConfig(pNode);
         _program->BufferPush(pBuffer);
         continue;
      }
      //............................................................
      // 建立参数定义集合
      if(pNode->IsName("Parameter")){
         FRenderProgramParameter* pParameter = _renderDevice->CreateObject<FRenderProgramParameter>(MO_RENDEROBJECT_PROGRAM_PARAMETER);
         pParameter->LoadConfig(pNode);
         _program->ParameterPush(pParameter);
         //MO_DEBUG("Build shader parameter. (name=%s, format=%d)", pParameter->Name(), pParameter->FormatCd());
         continue;
      }
      //............................................................
      // 建立属性定义集合
      if(pNode->IsName("Attribute")){
         FRenderProgramAttribute* pAttribute = _renderDevice->CreateObject<FRenderProgramAttribute>(MO_RENDEROBJECT_PROGRAM_ATTRIBUTE);
         pAttribute->LoadConfig(pNode);
         _program->AttributePush(pAttribute);
         continue;
      }
      //............................................................
      // 建立取样器定义集合
      if(pNode->IsName("Sampler")){
         FRenderProgramSampler* pSampler = _renderDevice->CreateObject<FRenderProgramSampler>(MO_RENDEROBJECT_PROGRAM_SAMPLER);
         pSampler->LoadConfig(pNode);
         _program->SamplerPush(pSampler);
         continue;
      }
   }
   return ESuccess;
}

//============================================================
// <T>建立模板环境。</T>
//
// @param pContext 环境
// @return 处理结果
//============================================================
TResult FEffect::BuildContext(SEffectContext* pContext){
   return ESuccess;
}

//============================================================
// <T>建立处理。</T>
//
// @return 处理结果
//============================================================
TResult FEffect::Build(){
   // 编译代码
   _program->VertexShader()->Build(_vertexSource);
   _program->FragmentShader()->Build(_fragmentSource);
   // 创建程序
   _program->Build();
   _program->Link();
   return ESuccess;
}

//============================================================
// <T>变更大小。</T>
//
// @return 处理结果
//============================================================
TResult FEffect::Resize(TInt width, TInt height){
   return ESuccess;
}

//============================================================
// <T>绘制处理。</T>
//
// @return 处理结果
//============================================================
TResult FEffect::DrawRenderable(FRenderRegion* pRegion, FRenderable* pRenderable){
   return ESuccess;
}

//============================================================
// <T>绘制处理。</T>
//
// @return 处理结果
//============================================================
TResult FEffect::DrawGroup(FRenderRegion* pRegion, TInt offset, TInt count){
   MO_CHECK(pRegion, return ENull);
   FRenderableCollection* pRenderables = pRegion->VisibleRenderables();
   for(TInt n = 0; n < count; n++){
      FRenderable* pRenderable = pRenderables->Get(offset + n);
      DrawRenderable(pRegion, pRenderable);
   }
   return ESuccess;
}

MO_NAMESPACE_END
