#ifndef __MO_PO_RENDER_H__
#define __MO_PO_RENDER_H__
//************************************************************

#ifndef __MO_PO_COMMON_H__
#include "MoPoCommon.h"
#endif // __MO_PO_COMMON_H__

#ifndef __MO_PO_CORE_H__
#include "MoPoCore.h"
#endif // __MO_PO_CORE_H__

MO_NAMESPACE_BEGIN

#define MO_RENDER_ATTRIBUTE_MAXCNT 64

//============================================================
// <T>渲染层信息。</T>
//============================================================
class MO_PO_DECLARE FPoRenderLayout : public FRenderLayout
{
   MO_CLASS_DECLARE_INHERITS(FPoRenderLayout, FRenderLayout);
protected:
   TInt _count;
   TInt _slots[MO_RENDER_ATTRIBUTE_MAXCNT];
   FRenderVertexBuffer* _pBuffers[MO_RENDER_ATTRIBUTE_MAXCNT];
   TInt _offsets[MO_RENDER_ATTRIBUTE_MAXCNT];
   ERenderAttributeFormat _formats[MO_RENDER_ATTRIBUTE_MAXCNT];
public:
   FPoRenderLayout();
   MO_ABSTRACT ~FPoRenderLayout();
public:
   //------------------------------------------------------------
   // <T>获得总数。</T>
   MO_INLINE TInt Count(){
      return _count;
   }
   //------------------------------------------------------------
   // <T>获得插槽集合。</T>
   MO_INLINE TInt* Slots(){
      return _slots;
   }
   //------------------------------------------------------------
   // <T>获得数据。</T>
   MO_INLINE FRenderVertexBuffer** Buffers(){
      return _pBuffers;
   }
   //------------------------------------------------------------
   // <T>获得位置。</T>
   MO_INLINE TInt* Offset(){
      return _offsets;
   }
   //------------------------------------------------------------
   // <T>获得格式集合。</T>
   MO_INLINE ERenderAttributeFormat* Formats(){
      return _formats;
   }
public:
   MO_OVERRIDE TResult OnSetup();
};

//============================================================
// <T>渲染顶点缓冲。</T>
//============================================================
class MO_PO_DECLARE FPoRenderVertexBuffer : public FRenderVertexBuffer
{
   MO_CLASS_DECLARE_INHERITS(FPoRenderVertexBuffer, FRenderVertexBuffer);
protected:
   GLuint _bufferId;
public:
   FPoRenderVertexBuffer();
   MO_ABSTRACT ~FPoRenderVertexBuffer();
public:
   //------------------------------------------------------------
   // <T>获得代码。</T>
   MO_INLINE GLuint BufferId(){
      return _bufferId;
   }
public:
   MO_OVERRIDE TResult OnSetup();
public:
   MO_OVERRIDE TResult Upload(TByteC* pData, TInt length);
public:
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
   MO_OVERRIDE TResult Dispose();
};

//============================================================
// <T>渲染索引缓冲。</T>
//============================================================
class MO_PO_DECLARE FPoRenderIndexBuffer : public FRenderIndexBuffer
{
   MO_CLASS_DECLARE_INHERITS(FPoRenderIndexBuffer, FRenderVertexBuffer);
protected:
   GLuint _bufferId;
public:
   FPoRenderIndexBuffer();
   MO_ABSTRACT ~FPoRenderIndexBuffer();
public:
   //------------------------------------------------------------
   // <T>获得代码。</T>
   MO_INLINE GLuint BufferId(){
      return _bufferId;
   }
public:
   MO_OVERRIDE TResult OnSetup();
public:
   MO_OVERRIDE TResult Upload(TByteC* pMemory, TInt length);
public:
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
   MO_OVERRIDE TResult Dispose();
};

//============================================================
// <T>顶点渲染器。</T>
//============================================================
class MO_PO_DECLARE FPoRenderVertexShader : public FRenderVertexShader
{
   MO_CLASS_DECLARE_INHERITS(FPoRenderVertexShader, FRenderVertexShader);
protected:
   GLuint _nativeCode;
public:
   FPoRenderVertexShader();
   MO_ABSTRACT ~FPoRenderVertexShader();
public:
   //------------------------------------------------------------
   // <T>获得本地代码。</T>
   MO_INLINE GLuint NativeCode(){
      return _nativeCode;
   }
public:
   MO_OVERRIDE TResult Setup();
public:
   MO_OVERRIDE TResult Compile(TCharC* pSource);
public:
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
   MO_OVERRIDE TResult Dispose();
};

//============================================================
// <T>像素渲染器。</T>
//============================================================
class MO_PO_DECLARE FPoRenderFragmentShader : public FRenderFragmentShader
{
   MO_CLASS_DECLARE_INHERITS(FPoRenderFragmentShader, FRenderVertexShader);
protected:
   GLuint _nativeCode;
public:
   FPoRenderFragmentShader();
   MO_ABSTRACT ~FPoRenderFragmentShader();
public:
   //------------------------------------------------------------
   // <T>获得本地代码。</T>
   MO_INLINE GLuint NativeCode(){
      return _nativeCode;
   }
public:
   MO_OVERRIDE TResult Setup();
public:
   MO_OVERRIDE TResult Compile(TCharC* pSource);
public:
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
   MO_OVERRIDE TResult Dispose();
};

//============================================================
// <T>渲染器参数。</T>
//============================================================
class MO_PO_DECLARE FPoRenderProgramParameter : public FRenderProgramParameter
{
   MO_CLASS_DECLARE_INHERITS(FPoRenderProgramParameter, FRenderProgramParameter);
public:
   FPoRenderProgramParameter();
   MO_ABSTRACT ~FPoRenderProgramParameter();
public:
   MO_ABSTRACT TResult Get(TAny* pData, TInt capacity);
   MO_ABSTRACT TResult Set(TAny* pData, TInt length);
};

//============================================================
// <T>渲染脚本变换器。</T>
//============================================================
class MO_PO_DECLARE FPoRenderShaderTransformer : public FRenderShaderTransformer
{
   MO_CLASS_DECLARE_INHERITS(FPoRenderShaderTransformer, FRenderShaderTransformer);
protected:
public:
   FPoRenderShaderTransformer();
   MO_ABSTRACT ~FPoRenderShaderTransformer();
public:
   MO_OVERRIDE TResult Convert(MString* pOutputScript, MString* pInputScript);
};

//============================================================
// <T>渲染脚本优化器。</T>
//============================================================
class MO_PO_DECLARE FPoRenderShaderOptimizer : public FRenderShaderOptimizer
{
   MO_CLASS_DECLARE_INHERITS(FPoRenderShaderOptimizer, FRenderShaderOptimizer);
protected:
public:
   FPoRenderShaderOptimizer();
   MO_ABSTRACT ~FPoRenderShaderOptimizer();
public:
   MO_OVERRIDE TResult Convert(MString* pOutputScript, MString* pInputScript);
};

//============================================================
// <T>渲染程序。</T>
//============================================================
class MO_PO_DECLARE FPoRenderProgram : public FRenderProgram
{
   MO_CLASS_DECLARE_INHERITS(FPoRenderProgram, FRenderProgram);
protected:
   GLuint _nativeCode;
public:
   FPoRenderProgram();
   MO_ABSTRACT ~FPoRenderProgram();
public:
   //------------------------------------------------------------
   // <T>获得本地代码。</T>
   MO_INLINE GLuint NativeCode(){
      return _nativeCode;
   }
public:
   MO_OVERRIDE TInt FindDefine(TCharC* pCode);
   MO_OVERRIDE TInt FindAttribute(TCharC* pCode);
   MO_OVERRIDE TResult BindAttribute(TInt slot, TCharC* pCode);
public:
   MO_OVERRIDE TResult Setup();
   MO_OVERRIDE TResult Build();
   MO_OVERRIDE TResult Link();
public:
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
   MO_OVERRIDE TResult Dispose();
};

//============================================================
// <T>渲染目标。</T>
//============================================================
class MO_PO_DECLARE FPoRenderTarget : public FRenderTarget
{
   MO_CLASS_DECLARE_INHERITS(FPoRenderTarget, FRenderTarget);
protected:
   GLuint _nativeCode;
   GLuint _depthStencilId;
   GLuint _depthBufferId;
public:
   FPoRenderTarget();
   MO_ABSTRACT ~FPoRenderTarget();
public:
   //------------------------------------------------------------
   // <T>获得本地代码。</T>
   MO_INLINE GLuint NativeCode(){
      return _nativeCode;
   }
   //------------------------------------------------------------
   // <T>获得深度模板编号。</T>
   MO_INLINE GLuint DepthStencilId(){
      return _depthStencilId;
   }
   //------------------------------------------------------------
   // <T>获得深度缓冲编号。</T>
   MO_INLINE GLuint DepthBufferId(){
      return _depthBufferId;
   }
public:
   MO_OVERRIDE TResult OnSetup();
public:
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
   MO_OVERRIDE TResult Dispose();
};

//============================================================
// <T>渲染平面纹理。</T>
//============================================================
class MO_PO_DECLARE FPoRenderFlatTexture : public FRenderFlatTexture
{
   MO_CLASS_DECLARE_INHERITS(FPoRenderFlatTexture, FRenderFlatTexture);
protected:
   GLuint _textureId;
public:
   FPoRenderFlatTexture();
   MO_ABSTRACT ~FPoRenderFlatTexture();
public:
   //------------------------------------------------------------
   // <T>获得代码。</T>
   MO_INLINE GLuint TextureId(){
      return _textureId;
   }
public:
   MO_OVERRIDE TResult OnSetup();
public:
   MO_OVERRIDE TResult Resize(TInt width, TInt height);
   MO_OVERRIDE TResult Unserialize(IDataInput* pInput);
   MO_OVERRIDE TResult Upload(TByteC* pData, TInt length);
   TResult LoadDataFile(TCharC* pFileName);
public:
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
   MO_OVERRIDE TResult Dispose();
};

//============================================================
// <T>渲染CUBE纹理。</T>
//============================================================
class MO_PO_DECLARE FPoRenderCubeTexture : public FRenderCubeTexture
{
   MO_CLASS_DECLARE_INHERITS(FPoRenderCubeTexture, FRenderFlatTexture);
protected:
   GLuint _textureId;
public:
   FPoRenderCubeTexture();
   MO_ABSTRACT ~FPoRenderCubeTexture();
public:
   //------------------------------------------------------------
   // <T>获得代码。</T>
   MO_INLINE GLuint TextureId(){
      return _textureId;
   }
public:
   MO_OVERRIDE TResult OnSetup();
public:
   MO_OVERRIDE TResult Resize(TInt size);
   MO_OVERRIDE TResult Unserialize(IDataInput* pInput);
   MO_OVERRIDE TResult Upload(TByteC* pData, TInt length);
   TResult LoadDataFile(TCharC* pFileName);
public:
   MO_OVERRIDE TResult Suspend();
   MO_OVERRIDE TResult Resume();
   MO_OVERRIDE TResult Dispose();
};

//============================================================
// <T>渲染设备。</T>
//============================================================
class MO_PO_DECLARE FPoRenderDevice : public FRenderDevice
{
   MO_CLASS_DECLARE_INHERITS(FPoRenderDevice, FRenderDevice);
protected:
   // 运行信息
   TInt _renderTextureActiveSlot;
   // 纹理信息
   TBool _optionTexture;
   GLint _vertexConstLimit;
   GLint _vertexAttributeLimit;
   GLint _fragmentConstLimit;
   GLint _varyingLimit;
   GLint _textureLimit;
   GLint _textureSizeLimit;
   GLint _textureTotalLimit;
   GLint _renderTargetLimit;
   // 关联顶点缓冲集合
   FRenderFlatTextureList* _pLinkFlatTextures;
   FRenderCubeTextureList* _pLinkCubeTextures;
public:
   FPoRenderDevice();
   MO_ABSTRACT ~FPoRenderDevice();
protected:
   TBool UpdateContext();
public:
   MO_OVERRIDE TResult Setup();
   MO_ABSTRACT TResult Suspend();
   MO_ABSTRACT TResult Resume();
public:
   MO_OVERRIDE TResult CheckError(TCharC* pCode, TCharC* pMessage, ...);
public:
   MO_OVERRIDE TResult SetBackBuffer(TInt width, TInt height, TInt antiAlias, TBool depthed = ETrue);
   MO_OVERRIDE TResult SetFillMode(ERenderFillMode fillModeCd);
   MO_OVERRIDE TResult SetDepthMode(TBool depth, ERenderDepthMode depthCd = ERenderDepthMode_None);
   MO_OVERRIDE TResult SetCullingMode(TBool cull, ERenderCullMode cullCd = ERenderCullMode_None);
   MO_OVERRIDE TResult SetBlendFactors(TBool blend, ERenderBlendMode sourceCd = ERenderBlendMode_None, ERenderBlendMode targetCd = ERenderBlendMode_None);
   MO_OVERRIDE TResult SetScissorRectangle(TInt left, TInt top, TInt width, TInt height);
   MO_OVERRIDE TResult SetRenderTarget(FRenderTarget* pRenderTarget = NULL);
   MO_OVERRIDE TResult SetProgram(FRenderProgram* pProgram);
   MO_OVERRIDE TResult SetLayout(FRenderLayout* pLayout);
public:
   MO_OVERRIDE TResult BindConst(ERenderShader shaderCd, TInt slot, ERenderParameterFormat formatCd, TAnyC* pData, TInt length);
   MO_OVERRIDE TResult BindConstBuffer(FRenderProgramBuffer* pBuffer);
   MO_OVERRIDE TResult BindVertexBuffer(TInt slot, FRenderVertexBuffer* pVertexBuffer, TInt offset, ERenderAttributeFormat formatCd);
   MO_OVERRIDE TResult BindTexture(TInt slot, TInt index, FRenderTexture* pTexture);
public:
   MO_OVERRIDE TResult Clear(TFloat red = 0.0f, TFloat green = 0.0f, TFloat blue = 0.0f, TFloat alpha = 1.0f, TFloat depth = 1.0f);
   MO_OVERRIDE TResult DrawTriangles(FRenderIndexBuffer* pIndexBuffer, TInt offset, TInt count);
   MO_OVERRIDE TResult Present();
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_PO_RENDER_H__
