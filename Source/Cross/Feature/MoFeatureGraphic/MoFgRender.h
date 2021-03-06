#ifndef __MO_FG_RENDER_H__
#define __MO_FG_RENDER_H__
//************************************************************

#ifndef __MO_FG_COMMON_H__
#include "MoFgCommon.h"
#endif // __MO_FG_COMMON_H__

#ifndef __MO_FG_CORE_H__
#include "MoFgCore.h"
#endif // __MO_FG_CORE_H__

#ifndef __MO_FG_BASE_H__
#include "MoFgBase.h"
#endif // __MO_FG_BASE_H__

#ifndef __MO_FG_VISUAL_H__
#include "MoFgVisual.h"
#endif // __MO_FG_VISUAL_H__

#define MO_EG_RENDER_STS_GROUP   0x0001
#define MO_EG_RENDER_STS_DEVICE  0x0001
#define MO_EG_CONST_RESERVE      12
#define MO_EG_CONST_MATRIX_MAX   1024
#define MO_EG_CONST_INSTANCE_MAX 256

MO_NAMESPACE_BEGIN

//============================================================
// <T>类定义。</T>
//============================================================
class FRenderShader;
class FRenderProgramBuffer;
class FRenderProgramParameter;
class FRenderProgramAttribute;
class FRenderProgramSampler;
class FRenderProgram;
class FRenderVertexStream;
class FRenderVertexBuffer;
class FRenderIndexBuffer;
class FRenderTexture;
class FRenderTextures;
class FRenderFlatTexture;
class FRenderCubeTexture;
class FRenderDevice;
class FEffect;
class FPipelinePass;
class FPipeline;

//============================================================
// <T>渲染能力。</T>
//============================================================
struct MO_FG_DECLARE FRenderCapability : FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRenderCapability, FInstance);
protected:
   TString _code;
   TString _label;
   TString _vendor;
   TString _version;
   TString _shaderVertexVersion;
   TString _shaderFragmentVersion;
protected:
   TInt _vertexCountLimit;
   TInt _vertexConstLimit;
   TInt _vertexAttributeLimit;
   TInt _vertexTemporaryLimit;
   TInt _vertexOpcodeLimit;
   TInt _fragmentConstLimit;
   TInt _fragmentTemporaryLimit;
   TInt _fragmentOpcodeLimit;
   TInt _varyingLimit;
   TInt _samplerLimit;
   TInt _samplerSizeLimit;
   TInt _renderTargetLimit;
public:
   FRenderCapability();
   MO_ABSTRACT ~FRenderCapability();
public:
   //------------------------------------------------------------
   // <T>获得代码。</T>
   MO_INLINE TCharC* Code(){
      return _code;
   }
   //------------------------------------------------------------
   // <T>设置代码。</T>
   MO_INLINE void SetCode(TCharC* pCode){
      _code = pCode;
   }
   //------------------------------------------------------------
   // <T>获得标签。</T>
   MO_INLINE TCharC* Label(){
      return _label;
   }
   //------------------------------------------------------------
   // <T>设置标签。</T>
   MO_INLINE void SetLabel(TCharC* pLabel){
      _label = pLabel;
   }
   //------------------------------------------------------------
   // <T>获得提供商。</T>
   MO_INLINE TCharC* Vendor(){
      return _vendor;
   }
   //------------------------------------------------------------
   // <T>设置提供商。</T>
   MO_INLINE void SetVendor(TCharC* pVendor){
      _vendor = pVendor;
   }
   //------------------------------------------------------------
   // <T>获得版本。</T>
   MO_INLINE TCharC* Version(){
      return _version;
   }
   //------------------------------------------------------------
   // <T>设置版本。</T>
   MO_INLINE void SetVersion(TCharC* pVersion){
      _version = pVersion;
   }
   //------------------------------------------------------------
   // <T>获得顶点脚本版本。</T>
   MO_INLINE TCharC* ShaderVertexVersion(){
      return _shaderVertexVersion;
   }
   //------------------------------------------------------------
   // <T>设置顶点脚本版本。</T>
   MO_INLINE void SetShaderVertexVersion(TCharC* pShaderVertexVersion){
      _shaderVertexVersion = pShaderVertexVersion;
   }
   //------------------------------------------------------------
   // <T>获得像素脚本版本。</T>
   MO_INLINE TCharC* ShaderFragmentVersion(){
      return _shaderFragmentVersion;
   }
   //------------------------------------------------------------
   // <T>设置像素脚本版本。</T>
   MO_INLINE void SetShaderFragmentVersion(TCharC* pShaderFragmentVersion){
      _shaderFragmentVersion = pShaderFragmentVersion;
   }
public:
   //------------------------------------------------------------
   // <T>获得顶点个数限制。</T>
   MO_INLINE TInt VertexCountLimit(){
      return _vertexCountLimit;
   }
   //------------------------------------------------------------
   // <T>设置顶点个数限制。</T>
   MO_INLINE void SetVertexCountLimit(TInt vertexCountLimit){
      _vertexCountLimit = vertexCountLimit;
   }
   //------------------------------------------------------------
   // <T>获得顶点常量限制。</T>
   MO_INLINE TInt VertexConstLimit(){
      return _vertexConstLimit;
   }
   //------------------------------------------------------------
   // <T>设置顶点常量限制。</T>
   MO_INLINE void SetVertexConstLimit(TInt vertexConstLimit){
      _vertexConstLimit = vertexConstLimit;
   }
   //------------------------------------------------------------
   // <T>获得顶点属性限制。</T>
   MO_INLINE TInt VertexAttributeLimit(){
      return _vertexAttributeLimit;
   }
   //------------------------------------------------------------
   // <T>设置顶点属性限制。</T>
   MO_INLINE void SetVertexAttributeLimit(TInt vertexAttributeLimit){
      _vertexAttributeLimit = vertexAttributeLimit;
   }
   //------------------------------------------------------------
   // <T>获得顶点临时变量限制。</T>
   MO_INLINE TInt VertexTemporaryLimit(){
      return _vertexTemporaryLimit;
   }
   //------------------------------------------------------------
   // <T>设置顶点临时变量限制。</T>
   MO_INLINE void SetVertexTemporaryLimit(TInt vertexTemporaryLimit){
      _vertexTemporaryLimit = vertexTemporaryLimit;
   }
   //------------------------------------------------------------
   // <T>获得顶点代码限制。</T>
   MO_INLINE TInt VertexOpcodeLimit(){
      return _vertexOpcodeLimit;
   }
   //------------------------------------------------------------
   // <T>设置顶点代码限制。</T>
   MO_INLINE void SetVertexOpcodeLimit(TInt vertexOpcodeLimit){
      _vertexOpcodeLimit = vertexOpcodeLimit;
   }
   //------------------------------------------------------------
   // <T>获得像素常量限制。</T>
   MO_INLINE TInt FragmentConstLimit(){
      return _fragmentConstLimit;
   }
   //------------------------------------------------------------
   // <T>设置像素常量限制。</T>
   MO_INLINE void SetFragmentConstLimit(TInt fragmentConstLimit){
      _fragmentConstLimit = fragmentConstLimit;
   }
   //------------------------------------------------------------
   // <T>获得像素临时变量限制。</T>
   MO_INLINE TInt FragmentTemporaryLimit(){
      return _fragmentTemporaryLimit;
   }
   //------------------------------------------------------------
   // <T>设置像素临时变量限制。</T>
   MO_INLINE void SetFragmentTemporaryLimit(TInt fragmentTemporaryLimit){
      _fragmentTemporaryLimit = fragmentTemporaryLimit;
   }
   //------------------------------------------------------------
   // <T>获得像素代码限制。</T>
   MO_INLINE TInt FragmentOpcodeLimit(){
      return _fragmentOpcodeLimit;
   }
   //------------------------------------------------------------
   // <T>设置像素代码限制。</T>
   MO_INLINE void SetFragmentOpcodeLimit(TInt fragmentOpcodeLimit){
      _fragmentOpcodeLimit = fragmentOpcodeLimit;
   }
   //------------------------------------------------------------
   // <T>获得插值器限制。</T>
   MO_INLINE TInt VaryingLimit(){
      return _varyingLimit;
   }
   //------------------------------------------------------------
   // <T>设置插值器限制。</T>
   MO_INLINE void SetVaryingLimit(TInt varyingLimit){
      _varyingLimit = varyingLimit;
   }
   //------------------------------------------------------------
   // <T>获得采样器限制。</T>
   MO_INLINE TInt SamplerLimit(){
      return _samplerLimit;
   }
   //------------------------------------------------------------
   // <T>设置采样器限制。</T>
   MO_INLINE void SetSamplerLimit(TInt samplerLimit){
      _samplerLimit = samplerLimit;
   }
   //------------------------------------------------------------
   // <T>获得采样器尺寸限制。</T>
   MO_INLINE TInt SamplerSizeLimit(){
      return _samplerSizeLimit;
   }
   //------------------------------------------------------------
   // <T>设置采样器尺寸限制。</T>
   MO_INLINE void SetSamplerSizeLimit(TInt samplerSizeLimit){
      _samplerSizeLimit = samplerSizeLimit;
   }
   //------------------------------------------------------------
   // <T>获得渲染目标个数限制。</T>
   MO_INLINE TInt RenderTargetLimit(){
      return _renderTargetLimit;
   }
   //------------------------------------------------------------
   // <T>设置渲染目标个数限制。</T>
   MO_INLINE void SetRenderTargetLimit(TInt renderTargetLimit){
      _renderTargetLimit = renderTargetLimit;
   }
public:
   void Track();
};

//============================================================
// <T>渲染统计器。</T>
//============================================================
class MO_FG_DECLARE FRenderStatistics : public FStatistics
{
   MO_CLASS_DECLARE_INHERITS(FRenderStatistics, FStatistics);
protected:
   TSpeedStatistics _frameStatistics;
   TSpeedStatistics _frameDrawStatistics;
   TInt _optionFillCount;
   TInt _optionDeepCount;
   TInt _optionCullCount;
   TInt _optionBlendCount;
   TInt _programCount;
   TInt _programConstLength;
   TInt _programConstCount;
   TInt _vertexBufferCount;
   TInt _samplerCount;
   TInt _drawFaceCount;
   TInt _drawCount;
public:
   FRenderStatistics();
   MO_ABSTRACT ~FRenderStatistics();
public:
   //------------------------------------------------------------
   // <T>获得帧信息统计。</T>
   MO_INLINE TSpeedStatistics& FrameStatistics(){
      return _frameStatistics;
   }
   //------------------------------------------------------------
   // <T>获得帧绘制统计。</T>
   MO_INLINE TSpeedStatistics& FrameDrawStatistics(){
      return _frameDrawStatistics;
   }
   //------------------------------------------------------------
   // <T>获得填充次数。</T>
   MO_INLINE TInt OptionFillCount(){
      return _optionFillCount;
   }
   //------------------------------------------------------------
   // <T>获得深度次数。</T>
   MO_INLINE TInt OptionDeepCount(){
      return _optionDeepCount;
   }
   //------------------------------------------------------------
   // <T>获得剪裁次数。</T>
   MO_INLINE TInt OptionCullCount(){
      return _optionCullCount;
   }
   //------------------------------------------------------------
   // <T>获得融合次数。</T>
   MO_INLINE TInt OptionBlendCount(){
      return _optionBlendCount;
   }
   //------------------------------------------------------------
   // <T>获得程序次数。</T>
   MO_INLINE TInt ProgramCount(){
      return _programCount;
   }
   //------------------------------------------------------------
   // <T>获得程序常量长度。</T>
   MO_INLINE TInt ProgramConstLength(){
      return _programCount;
   }
   //------------------------------------------------------------
   // <T>获得程序常量次数。</T>
   MO_INLINE TInt ProgramConstCount(){
      return _programConstCount;
   }
   //------------------------------------------------------------
   // <T>获得顶点缓冲次数。</T>
   MO_INLINE TInt VertexBufferCount(){
      return _vertexBufferCount;
   }
   //------------------------------------------------------------
   // <T>获得取样器次数。</T>
   MO_INLINE TInt SamplerCount(){
      return _samplerCount;
   }
   //------------------------------------------------------------
   // <T>获得绘制面总数。</T>
   MO_INLINE TInt DrawFaceCount(){
      return _drawFaceCount;
   }
   //------------------------------------------------------------
   // <T>获得绘制次数。</T>
   MO_INLINE TInt DrawCount(){
      return _drawCount;
   }
public:
   void UpdateOptionFillCount();
   void UpdateOptionDeepCount();
   void UpdateOptionCullCount();
   void UpdateOptionBlendCount();
   void UpdateProgramCount();
   void UpdateProgramCount(TInt constLength);
   void UpdateVertexBufferCount();
   void UpdateSamplerCount();
   void UpdateDraw(TInt faceCount);
public:
   MO_OVERRIDE TResult Reset();
public:
   MO_OVERRIDE TResult Dump(MString* pDump);
};

//============================================================
// <T>渲染实例。</T>
//============================================================
class MO_FG_DECLARE FRenderInstance : public FGraphicInstance
{
   MO_CLASS_DECLARE_INHERITS(FRenderInstance, FGraphicInstance);
protected:
   FRenderDevice* _pDevice;
public:
   FRenderInstance();
   MO_ABSTRACT ~FRenderInstance();
public:
   //------------------------------------------------------------
   // <T>获得设备。</T>
   MO_INLINE FRenderDevice* Device(){
      return _pDevice;
   }
   //------------------------------------------------------------
   // <T>设置设备。</T>
   MO_INLINE void SetDevice(FRenderDevice* pDevice){
      _pDevice = pDevice;
   }
public:
   MO_ABSTRACT TResult Suspend();
   MO_ABSTRACT TResult Resume();
};

//============================================================
// <T>渲染顶点缓冲。</T>
//============================================================
class MO_FG_DECLARE FRenderVertexBuffer : public FRenderInstance
{
   MO_CLASS_ABSTRACT_DECLARE_INHERITS(FRenderVertexBuffer, FRenderInstance);
protected:
   TInt _stride;
   TInt _count;
   TInt _dataLength;
   FDataStream* _pDataStream;
public:
   FRenderVertexBuffer();
   MO_ABSTRACT ~FRenderVertexBuffer();
public:
   //------------------------------------------------------------
   // <T>获得顶点字节数。</T>
   MO_INLINE TInt Stride(){
      return _stride;
   }
   //------------------------------------------------------------
   // <T>设置顶点字节数。</T>
   MO_INLINE void SetStride(TInt stride){
      _stride = stride;
   }
   //------------------------------------------------------------
   // <T>获得顶点个数。</T>
   MO_INLINE TInt Count(){
      return _count;
   }
   //------------------------------------------------------------
   // <T>设置顶点个数。</T>
   MO_INLINE void SetCount(TInt count){
      _count = count;
   }
   //------------------------------------------------------------
   // <T>获得数据长度。</T>
   MO_INLINE TInt DataLength(){
      return _dataLength;
   }
   //------------------------------------------------------------
   // <T>获得数据流。</T>
   MO_INLINE FDataStream* DataStream(){
      return _pDataStream;
   }
   //------------------------------------------------------------
   // <T>获得数据内存。</T>
   MO_INLINE TAny* DataMemory(){
      TAny* pMemory = NULL;
      if(_pDataStream != NULL){
         pMemory = _pDataStream->Memory();
      }
      return pMemory;
   }
   //------------------------------------------------------------
   // <T>获得数据内存。</T>
   template <class T>
   MO_INLINE T* DataMemory(){
      T* pMemory = NULL;
      if(_pDataStream != NULL){
         pMemory = (T*)_pDataStream->Memory();
      }
      return pMemory;
   }
public:
   MO_VIRTUAL TResult Upload(TByteC* pData, TInt length) = 0;
public:
   MO_ABSTRACT TResult BuildData();
   MO_ABSTRACT TResult UploadData(TBool reserve = EFalse);
};
//------------------------------------------------------------
typedef MO_FG_DECLARE FObjects<FRenderVertexBuffer*> FRenderVertexBufferCollection;
typedef MO_FG_DECLARE GPtrs<FRenderVertexBuffer> GRenderVertexBufferPtrs;
typedef MO_FG_DECLARE GPtrLooper<FRenderVertexBuffer> GRenderVertexBufferLooper;

//============================================================
// <T>渲染索引缓冲。</T>
//============================================================
class MO_FG_DECLARE FRenderIndexBuffer : public FRenderInstance
{
   MO_CLASS_ABSTRACT_DECLARE_INHERITS(FRenderIndexBuffer, FRenderInstance);
protected:
   ERenderIndexStride _strideCd;
   TInt _count;
   TInt _instanceStride;
   TInt _instanceCount;
   TInt _dataLength;
   FDataStream* _pDataStream;
public:
   FRenderIndexBuffer();
   MO_ABSTRACT ~FRenderIndexBuffer();
public:
   //------------------------------------------------------------
   // <T>获得索引宽度。</T>
   MO_INLINE ERenderIndexStride StrideCd(){
      return _strideCd;
   }
   //------------------------------------------------------------
   // <T>设置索引宽度。</T>
   MO_INLINE void SetStrideCd(ERenderIndexStride strideCd){
      _strideCd = strideCd;
   }
   //------------------------------------------------------------
   // <T>获得三角形个数。</T>
   MO_INLINE TInt Count(){
      return _count;
   }
   //------------------------------------------------------------
   // <T>设置三角形个数。</T>
   MO_INLINE void SetCount(TInt count){
      _count = count;
   }
   //------------------------------------------------------------
   // <T>获得实例宽度。</T>
   MO_INLINE TInt InstanceStride(){
      return _instanceStride;
   }
   //------------------------------------------------------------
   // <T>设置实例宽度。</T>
   MO_INLINE void SetInstanceStride(TInt instanceStride){
      _instanceStride = instanceStride;
   }
   //------------------------------------------------------------
   // <T>获得实例个数。</T>
   MO_INLINE TInt InstanceCount(){
      return _instanceCount;
   }
   //------------------------------------------------------------
   // <T>设置实例个数。</T>
   MO_INLINE void SetInstanceCount(TInt instanceCount){
      _instanceCount = instanceCount;
   }
   //------------------------------------------------------------
   // <T>获得数据长度。</T>
   MO_INLINE TInt DataLength(){
      return _dataLength;
   }
   //------------------------------------------------------------
   // <T>获得数据流。</T>
   MO_INLINE FDataStream* DataStream(){
      return _pDataStream;
   }
   //------------------------------------------------------------
   // <T>获得数据内存。</T>
   MO_INLINE TAny* DataMemory(){
      TAny* pMemory = NULL;
      if(_pDataStream != NULL){
         pMemory = _pDataStream->Memory();
      }
      return pMemory;
   }
   //------------------------------------------------------------
   // <T>获得数据内存。</T>
   template <class T>
   MO_INLINE T* DataMemory(){
      T* pMemory = NULL;
      if(_pDataStream != NULL){
         pMemory = (T*)_pDataStream->Memory();
      }
      return pMemory;
   }
public:
   MO_ABSTRACT TResult OnSetup();
public:
   MO_VIRTUAL TResult Upload(TByteC* pData, TInt count) = 0;
public:
   MO_ABSTRACT TResult BuildData();
   MO_ABSTRACT TResult UploadData(TBool reserve = EFalse);
};
//------------------------------------------------------------
typedef MO_FG_DECLARE GPtrs<FRenderIndexBuffer> GRenderIndexBufferPtrs;
typedef MO_FG_DECLARE GPtrLooper<FRenderIndexBuffer> GRenderIndexBufferPtrLooper;

//============================================================
// <T>渲染来源。</T>
//============================================================
class MO_FG_DECLARE FRenderSource : public FString{
public:
   FRenderSource();
   MO_ABSTRACT ~FRenderSource();
public:
   MO_ABSTRACT TResult AppendCommet(TChar8C* pFormat, ...);
   MO_ABSTRACT TResult AppendSource(TChar8C* pFormat, ...);
public:
   MO_ABSTRACT TCharC* Build();
};

//============================================================
// <T>渲染器缓冲。</T>
//============================================================
class MO_FG_DECLARE FRenderProgramBuffer : public FRenderInstance
{
   MO_CLASS_DECLARE_INHERITS(FRenderProgramBuffer, FRenderInstance);
protected:
   TString _name;
   TString _linker;
   ERenderShaderBuffer _groupCd;
   ERenderShaderBuffer _bufferCd;
   TInt _dataLength;
   TBool _statusUsed;
   TBool _statusChanged;
   FBytes* _pData;
   ERenderShader _shaderCd;
   TInt _slot;
public:
   FRenderProgramBuffer();
   MO_ABSTRACT ~FRenderProgramBuffer();
public:
   //------------------------------------------------------------
   // <T>获得名称。</T>
   MO_INLINE TCharC* Name(){
      return _name;
   }
   //------------------------------------------------------------
   // <T>设置名称。</T>
   MO_INLINE void SetName(TCharC* pName){
      _name = pName;
   }
   //------------------------------------------------------------
   // <T>获得关联器。</T>
   MO_INLINE TCharC* Linker(){
      return _linker;
   }
   //------------------------------------------------------------
   // <T>设置关联器。</T>
   MO_INLINE void SetLinker(TCharC* pLinker){
      _linker = pLinker;
   }
   //------------------------------------------------------------
   // <T>获得分组类型。</T>
   MO_INLINE ERenderShaderBuffer GroupCd(){
      return _groupCd;
   }
   //------------------------------------------------------------
   // <T>设置分组类型。</T>
   MO_INLINE void SetGroupCd(ERenderShaderBuffer groupCd){
      _groupCd = groupCd;
   }
   //------------------------------------------------------------
   // <T>获得缓冲类型。</T>
   MO_INLINE ERenderShaderBuffer BufferCd(){
      return _bufferCd;
   }
   //------------------------------------------------------------
   // <T>设置缓冲类型。</T>
   MO_INLINE void SetBufferCd(ERenderShaderBuffer bufferCd){
      _bufferCd = bufferCd;
   }
   //------------------------------------------------------------
   // <T>获得数据长度。</T>
   MO_INLINE TInt DataLength(){
      return _dataLength;
   }
   //------------------------------------------------------------
   // <T>设置数据长度。</T>
   MO_INLINE void SetDataLength(TInt dataLength){
      _dataLength = dataLength;
   }
   //------------------------------------------------------------
   // <T>获得状态是否被使用。</T>
   MO_INLINE TBool IsStatusUsed(){
      return _statusUsed;
   }
   //------------------------------------------------------------
   // <T>设置状态是否被使用。</T>
   MO_INLINE void SetStatusUsed(TBool statusUsed){
      _statusUsed = statusUsed;
   }
   //------------------------------------------------------------
   // <T>获得数据。</T>
   MO_INLINE FBytes* Data(){
      return _pData;
   }
   //------------------------------------------------------------
   // <T>获得渲染类型。</T>
   MO_INLINE ERenderShader ShaderCd(){
      return _shaderCd;
   }
   //------------------------------------------------------------
   // <T>设置渲染类型。</T>
   MO_INLINE void SetShaderCd(ERenderShader shaderCd){
      _shaderCd = shaderCd;
   }
   //------------------------------------------------------------
   // <T>获得插槽。</T>
   MO_INLINE TInt Slot(){
      return _slot;
   }
   //------------------------------------------------------------
   // <T>设置插槽。</T>
   MO_INLINE void SetSlot(TInt slot){
      _slot = slot;
   }
public:
   MO_ABSTRACT TResult LoadConfig(FXmlNode* pConfig);
   MO_OVERRIDE TResult OnSetup();
public:
   MO_ABSTRACT TResult Set(TInt slot, TAnyC* pData, TInt length);
public:
   MO_ABSTRACT TResult Commit();
   MO_ABSTRACT TResult Update();
   MO_ABSTRACT TResult Bind();
public:
   MO_ABSTRACT TResult Dump(MString* pDump, TBool detail = EFalse);
};
//------------------------------------------------------------
typedef MO_FG_DECLARE GPtr<FRenderProgramBuffer> GRenderShaderBufferPtr;
typedef MO_FG_DECLARE GPtrs<FRenderProgramBuffer> GRenderShaderBufferPtrs;

//============================================================
// <T>渲染器参数。</T>
//============================================================
class MO_FG_DECLARE FRenderProgramParameter : public FRenderInstance
{
   MO_CLASS_DECLARE_INHERITS(FRenderProgramParameter, FRenderInstance);
protected:
   // 名称
   TString _name;
   // 关联名称
   TString _linker;
   // 使用状态
   TBool _statusUsed;
   // 渲染类型
   ERenderShader _shaderCd;
   // 格式类型
   ERenderParameterFormat _formatCd;
   // 插槽
   TInt _slot;
   // 大小
   TInt _size;
   // 缓冲
   GRenderShaderBufferPtr _buffer;
   //FRenderShader* _pShader;
public:
   FRenderProgramParameter();
   MO_ABSTRACT ~FRenderProgramParameter();
public:
   //------------------------------------------------------------
   // <T>获得名称。</T>
   MO_INLINE TCharC* Name(){
      return _name;
   }
   //------------------------------------------------------------
   // <T>设置名称。</T>
   MO_INLINE void SetName(TCharC* pName){
      _name = pName;
   }
   //------------------------------------------------------------
   // <T>获得关联器。</T>
   MO_INLINE TCharC* Linker(){
      return _linker;
   }
   //------------------------------------------------------------
   // <T>设置关联器。</T>
   MO_INLINE void SetLinker(TCharC* pLinker){
      _linker = pLinker;
   }
   //------------------------------------------------------------
   // <T>获得状态是否被使用。</T>
   MO_INLINE TBool IsStatusUsed(){
      return _statusUsed;
   }
   //------------------------------------------------------------
   // <T>设置状态是否被使用。</T>
   MO_INLINE void SetStatusUsed(TBool statusUsed){
      _statusUsed = statusUsed;
   }
   //------------------------------------------------------------
   // <T>获得渲染类型。</T>
   MO_INLINE ERenderShader ShaderCd(){
      return _shaderCd;
   }
   //------------------------------------------------------------
   // <T>设置渲染类型。</T>
   MO_INLINE void SetShaderCd(ERenderShader shaderCd){
      _shaderCd = shaderCd;
   }
   //------------------------------------------------------------
   // <T>获得格式。</T>
   MO_INLINE ERenderParameterFormat FormatCd(){
      return _formatCd;
   }
   //------------------------------------------------------------
   // <T>设置格式。</T>
   MO_INLINE void SetFormatCd(ERenderParameterFormat formatCd){
      _formatCd = formatCd;
   }
   //------------------------------------------------------------
   // <T>获得插槽。</T>
   MO_INLINE TInt Slot(){
      return _slot;
   }
   //------------------------------------------------------------
   // <T>设置插槽。</T>
   MO_INLINE void SetSlot(TInt slot){
      _slot = slot;
   }
   //------------------------------------------------------------
   // <T>获得尺寸。</T>
   MO_INLINE TInt Size(){
      return _size;
   }
   //------------------------------------------------------------
   // <T>设置尺寸。</T>
   MO_INLINE void SetSize(TInt size){
      _size = size;
   }
   ////------------------------------------------------------------
   //// <T>获得渲染器。</T>
   //MO_INLINE FRenderShader* Shader(){
   //   return _pShader;
   //}
   ////------------------------------------------------------------
   //// <T>设置渲染器。</T>
   //MO_INLINE void SetShader(FRenderShader* pShader){
   //   _pShader = pShader;
   //}
   //------------------------------------------------------------
   // <T>获得缓冲。</T>
   MO_INLINE FRenderProgramBuffer* Buffer(){
      return _buffer;
   }
   //------------------------------------------------------------
   // <T>设置缓冲。</T>
   MO_INLINE void SetBuffer(FRenderProgramBuffer* pBuffer){
      _buffer = pBuffer;
   }
public:
   MO_ABSTRACT TResult Get(TAny* pData, TInt capacity);
   MO_ABSTRACT TResult Set(TAny* pData, TInt length);
public:
   TResult SetFloat3(TFloat x, TFloat y, TFloat z);
   TResult SetFloat4(TFloat x, TFloat y, TFloat z, TFloat w);
   TResult SetMatrix3x3(const SFloatMatrix3d* pMatrix, TInt count, TBool transpose = ETrue);
   TResult SetMatrix4x3(const SFloatMatrix3d* pMatrix, TInt count, TBool transpose = ETrue);
   TResult SetMatrix4x4(const SFloatMatrix3d* pMatrix, TInt count, TBool transpose = ETrue);
public:
   MO_ABSTRACT TResult LoadConfig(FXmlNode* pConfig);
public:
   MO_ABSTRACT TResult Dump(MString* pDump, TBool detail = EFalse);
};
//------------------------------------------------------------
typedef MO_FG_DECLARE FObjects<FRenderProgramParameter*> FRenderProgramParameterCollection;
typedef MO_FG_DECLARE GPtrs<FRenderProgramParameter> GRenderShaderParameterPtrs;

//============================================================
// <T>渲染器。</T>
//============================================================
class MO_FG_DECLARE FRenderShader :
      public FRenderInstance,
      public IDispose
{
   MO_CLASS_ABSTRACT_DECLARE_INHERITS(FRenderShader, FRenderInstance);
protected:
   ERenderShader _shaderCd;
   FRenderProgram* _pProgram;
   FRenderSource* _pSource;
   FRenderSource* _pCompileSource;
   GRenderShaderParameterPtrs _parameters;
public:
   FRenderShader();
   MO_ABSTRACT ~FRenderShader();
public:
   //------------------------------------------------------------
   // <T>获得渲染类型。</T>
   MO_INLINE ERenderShader ShaderCd(){
      return _shaderCd;
   }
   //------------------------------------------------------------
   // <T>获得程序。</T>
   MO_INLINE FRenderProgram* Program(){
      return _pProgram;
   }
   //------------------------------------------------------------
   // <T>设置程序。</T>
   MO_INLINE void SetProgram(FRenderProgram* pProgram){
      _pProgram = pProgram;
   }
   //------------------------------------------------------------
   // <T>获得脚本。</T>
   MO_INLINE FRenderSource* Source(){
      return _pSource;
   }
   //------------------------------------------------------------
   // <T>获得编译脚本。</T>
   MO_INLINE FRenderSource* CompileSource(){
      return _pCompileSource;
   }
   //------------------------------------------------------------
   // <T>获得渲染参数集合。</T>
   MO_INLINE GRenderShaderParameterPtrs& Parameters(){
      return _parameters;
   }
   ////------------------------------------------------------------
   //// <T>根据名称查找渲染参数。</T>
   //MO_INLINE FRenderProgramParameter* ParameterFind(TCharC* pName){
   //   return _parameters.Find(pName);
   //}
   ////------------------------------------------------------------
   //// <T>增加一个参数。</T>
   //MO_INLINE TResult ParameterPush(FRenderProgramParameter* pParameter){
   //   MO_CHECK(pParameter, return ENull);
   //   _parameters.Set(pParameter->Name(), pParameter);
   //   return ESuccess;
   //}
public:
   MO_VIRTUAL TResult Setup() = 0;
   MO_VIRTUAL TResult Compile(TCharC* pSource) = 0;
public:
   TResult Build(TCharC* pSource);
};

//============================================================
// <T>顶点渲染器。</T>
//============================================================
class MO_FG_DECLARE FRenderVertexShader : public FRenderShader
{
   MO_CLASS_ABSTRACT_DECLARE_INHERITS(FRenderVertexShader, FRenderShader);
public:
   FRenderVertexShader();
   MO_ABSTRACT ~FRenderVertexShader();
};
//------------------------------------------------------------
typedef MO_FG_DECLARE GPtr<FRenderVertexShader> GRenderVertexShaderPtr;

//============================================================
// <T>像素渲染器。</T>
//============================================================
class MO_FG_DECLARE FRenderFragmentShader : public FRenderShader
{
   MO_CLASS_ABSTRACT_DECLARE_INHERITS(FRenderFragmentShader, FRenderShader);
public:
   FRenderFragmentShader();
   MO_ABSTRACT ~FRenderFragmentShader();
};
//------------------------------------------------------------
typedef MO_FG_DECLARE GPtr<FRenderFragmentShader> GRenderFragmentShaderPtr;

//============================================================
// <T>渲染脚本变换器。</T>
//============================================================
class MO_FG_DECLARE FRenderShaderTransformer : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRenderShaderTransformer, FInstance);
protected:
public:
   FRenderShaderTransformer();
   MO_ABSTRACT ~FRenderShaderTransformer();
public:
   MO_ABSTRACT TResult Convert(MString* pOutputScript, MString* pInputScript);
};
//------------------------------------------------------------
typedef MO_FG_DECLARE GPtr<FRenderShaderTransformer> GRenderShaderTransformerPtr;

//============================================================
// <T>渲染脚本优化器。</T>
//============================================================
class MO_FG_DECLARE FRenderShaderOptimizer : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRenderShaderOptimizer, FInstance);
protected:
public:
   FRenderShaderOptimizer();
   MO_ABSTRACT ~FRenderShaderOptimizer();
public:
   MO_ABSTRACT TResult Convert(MString* pOutputScript, MString* pInputScript);
};
//------------------------------------------------------------
typedef MO_FG_DECLARE GPtr<FRenderShaderOptimizer> GRenderShaderOptimizerPtr;

//============================================================
// <T>渲染布局。</T>
//============================================================
class MO_FG_DECLARE FRenderLayout : public FRenderInstance
{
   MO_CLASS_DECLARE_INHERITS(FRenderLayout, FInstance);
protected:
   FRenderProgram* _pProgram;
   FRenderable* _pRenderable;
public:
   FRenderLayout();
   MO_ABSTRACT ~FRenderLayout();
public:
   //------------------------------------------------------------
   // <T>获得程序。</T>
   MO_INLINE FRenderProgram* Program(){
      return _pProgram;
   }
   //------------------------------------------------------------
   // <T>设置程序。</T>
   MO_INLINE void SetProgram(FRenderProgram* pProgram){
      _pProgram = pProgram;
   }
   //------------------------------------------------------------
   // <T>获得渲染对象。</T>
   MO_INLINE FRenderable* Renderable(){
      return _pRenderable;
   }
   //------------------------------------------------------------
   // <T>设置渲染对象。</T>
   MO_INLINE void SetRenderable(FRenderable* pRenderable){
      _pRenderable = pRenderable;
   }
};
//------------------------------------------------------------
typedef MO_FG_DECLARE GPtr<FRenderLayout> GRenderableLayoutPtr;

//============================================================
// <T>渲染器属性。</T>
//============================================================
class MO_FG_DECLARE FRenderProgramAttribute : public FRenderInstance
{
   MO_CLASS_DECLARE_INHERITS(FRenderProgramAttribute, FRenderInstance);
protected:
   TString _name;
   TString _linker;
   TBool _statusUsed;
   TInt _slot;
   TInt _index;
   ERenderAttributeFormat _formatCd;
public:
   FRenderProgramAttribute();
   MO_ABSTRACT ~FRenderProgramAttribute();
public:
   //------------------------------------------------------------
   // <T>获得名称。</T>
   MO_INLINE TCharC* Name(){
      return _name;
   }
   //------------------------------------------------------------
   // <T>设置名称。</T>
   MO_INLINE void SetName(TCharC* pName){
      _name = pName;
   }
   //------------------------------------------------------------
   // <T>获得关联器。</T>
   MO_INLINE TCharC* Linker(){
      return _linker;
   }
   //------------------------------------------------------------
   // <T>设置关联器。</T>
   MO_INLINE void SetLinker(TCharC* pLinker){
      _linker = pLinker;
   }
   //------------------------------------------------------------
   // <T>获得状态是否被使用。</T>
   MO_INLINE TBool IsStatusUsed(){
      return _statusUsed;
   }
   //------------------------------------------------------------
   // <T>设置状态是否被使用。</T>
   MO_INLINE void SetStatusUsed(TBool statusUsed){
      _statusUsed = statusUsed;
   }
   //------------------------------------------------------------
   // <T>获得插槽。</T>
   MO_INLINE TInt Slot(){
      return _slot;
   }
   //------------------------------------------------------------
   // <T>设置插槽。</T>
   MO_INLINE void SetSlot(TInt slot){
      _slot = slot;
   }
   //------------------------------------------------------------
   // <T>获得索引。</T>
   MO_INLINE TInt Index(){
      return _index;
   }
   //------------------------------------------------------------
   // <T>设置索引。</T>
   MO_INLINE void SetIndex(TInt index){
      _index = index;
   }
   //------------------------------------------------------------
   // <T>获得属性类型。</T>
   MO_INLINE ERenderAttributeFormat FormatCd(){
      return _formatCd;
   }
   //------------------------------------------------------------
   // <T>设置属性类型。</T>
   MO_INLINE void SetFormatCd(ERenderAttributeFormat formatCd){
      _formatCd = formatCd;
   }
public:
   MO_ABSTRACT TResult LoadConfig(FXmlNode* pConfig);
public:
   MO_ABSTRACT TResult Dump(MString* pDump, TBool detail = EFalse);
};
//------------------------------------------------------------
typedef MO_FG_DECLARE FObjects<FRenderProgramAttribute*> FRenderProgramAttributeCollection;
typedef MO_FG_DECLARE GPtrs<FRenderProgramAttribute> GRenderShaderAttributePtrs;

//============================================================
// <T>渲染器取样。</T>
//============================================================
class MO_FG_DECLARE FRenderProgramSampler : public FRenderInstance
{
   MO_CLASS_DECLARE_INHERITS(FRenderProgramSampler, FRenderInstance);
protected:
   TString _name;
   TString _linker;
   TString _source;
   TBool _statusUsed;
   TInt _slot;
   TInt _index;
public:
   FRenderProgramSampler();
   MO_ABSTRACT ~FRenderProgramSampler();
public:
   //------------------------------------------------------------
   // <T>获得名称。</T>
   MO_INLINE TCharC* Name(){
      return _name;
   }
   //------------------------------------------------------------
   // <T>设置名称。</T>
   MO_INLINE void SetName(TCharC* pName){
      _name = pName;
   }
   //------------------------------------------------------------
   // <T>获得关联器。</T>
   MO_INLINE TCharC* Linker(){
      return _linker;
   }
   //------------------------------------------------------------
   // <T>设置关联器。</T>
   MO_INLINE void SetLinker(TCharC* pLinker){
      _linker = pLinker;
   }
   //------------------------------------------------------------
   // <T>获得来源。</T>
   MO_INLINE TCharC* Source(){
      return _linker;
   }
   //------------------------------------------------------------
   // <T>设置来源。</T>
   MO_INLINE void SetSource(TCharC* pSource){
      _source = pSource;
   }
   //------------------------------------------------------------
   // <T>获得状态是否被使用。</T>
   MO_INLINE TBool IsStatusUsed(){
      return _statusUsed;
   }
   //------------------------------------------------------------
   // <T>设置状态是否被使用。</T>
   MO_INLINE void SetStatusUsed(TBool statusUsed){
      _statusUsed = statusUsed;
   }
   //------------------------------------------------------------
   // <T>获得插槽。</T>
   MO_INLINE TInt Slot(){
      return _slot;
   }
   //------------------------------------------------------------
   // <T>设置插槽。</T>
   MO_INLINE void SetSlot(TInt slot){
      _slot = slot;
   }
   //------------------------------------------------------------
   // <T>获得索引。</T>
   MO_INLINE TInt Index(){
      return _index;
   }
   //------------------------------------------------------------
   // <T>设置索引。</T>
   MO_INLINE void SetIndex(TInt index){
      _index = index;
   }
public:
   MO_ABSTRACT TResult LoadConfig(FXmlNode* pConfig);
public:
   MO_ABSTRACT TResult Dump(MString* pDump, TBool detail = EFalse);
};
//------------------------------------------------------------
typedef MO_FG_DECLARE FObjects<FRenderProgramSampler*> FRenderProgramSamplerCollection;
typedef MO_FG_DECLARE GPtrs<FRenderProgramSampler> GRenderProgramSamplerPtrs;

//============================================================
// <T>渲染程序。</T>
//============================================================
class MO_FG_DECLARE FRenderProgram :
      public FRenderInstance,
      public IDispose
{
   MO_CLASS_ABSTRACT_DECLARE_INHERITS(FRenderProgram, FRenderInstance);
protected:
   GRenderVertexShaderPtr _vertexShader;
   GRenderFragmentShaderPtr _fragmentShader;
   GRenderShaderBufferPtrs _buffers;
   GRenderShaderParameterPtrs _parameters;
   GRenderShaderAttributePtrs _attributes;
   GRenderProgramSamplerPtrs _samplers;
public:
   FRenderProgram();
   MO_ABSTRACT ~FRenderProgram();
public:
   //------------------------------------------------------------
   // <T>获得顶点渲染器。</T>
   MO_INLINE FRenderVertexShader* VertexShader(){
      return _vertexShader;
   }
   //------------------------------------------------------------
   // <T>获得像素渲染器。</T>
   MO_INLINE FRenderFragmentShader* FragmentShader(){
      return _fragmentShader;
   }
   //------------------------------------------------------------
   // <T>获得渲染缓冲集合。</T>
   MO_INLINE GRenderShaderBufferPtrs& Buffers(){
      return _buffers;
   }
   //------------------------------------------------------------
   // <T>获得渲染参数集合。</T>
   MO_INLINE GRenderShaderParameterPtrs& Parameters(){
      return _parameters;
   }
   //------------------------------------------------------------
   // <T>获得渲染属性集合。</T>
   MO_INLINE GRenderShaderAttributePtrs& Attributes(){
      return _attributes;
   }
   //------------------------------------------------------------
   // <T>获得渲染取样集合。</T>
   MO_INLINE GRenderProgramSamplerPtrs& Samplers(){
      return _samplers;
   }
public:
   FRenderProgramBuffer* BufferFindByName(TCharC* pName);
   FRenderProgramBuffer* BufferFindByLinker(TCharC* pLinker);
   TResult BufferPush(FRenderProgramBuffer* pBuffer);
public:
   FRenderProgramParameter* ParameterFind(ERenderShader shaderCd, TCharC* pName);
   FRenderProgramParameter* ParameterFindByName(TCharC* pName);
   FRenderProgramParameter* ParameterFindByLinker(TCharC* pLinker);
   TResult ParameterPush(FRenderProgramParameter* pParameter);
public:
   FRenderProgramAttribute* AttributeFind(TCharC* pName, TInt index);
   FRenderProgramAttribute* AttributeFindByName(TCharC* pName);
   FRenderProgramAttribute* AttributeFindByLinker(TCharC* pLinker);
   TResult AttributePush(FRenderProgramAttribute* pAttribute);
public:
   FRenderProgramSampler* SamplerFindByName(TCharC* pName);
   FRenderProgramSampler* SamplerFindByLinker(TCharC* pLinker);
   TResult SamplerPush(FRenderProgramSampler* pSampler);
public:
   MO_ABSTRACT TResult MakeVertexSource(FRenderSource* pSource);
   MO_ABSTRACT TResult MakeFragmentSource(FRenderSource* pSource);
public:
   MO_VIRTUAL TInt FindDefine(TCharC* pCode) = 0;
   MO_VIRTUAL TInt FindAttribute(TCharC* pCode) = 0;
   MO_VIRTUAL TResult BindAttribute(TInt slot, TCharC* pCode) = 0;
public:
   MO_VIRTUAL TResult Setup() = 0;
   MO_VIRTUAL TResult Build() = 0;
   MO_VIRTUAL TResult Link() = 0;
public:
   MO_ABSTRACT TResult DrawBegin();
   MO_ABSTRACT TResult DrawEnd();
public:
   MO_ABSTRACT TResult Track(TBool detail = EFalse);
};
//------------------------------------------------------------
typedef MO_FG_DECLARE GPtr<FRenderProgram> GRenderProgramPtr;
typedef MO_FG_DECLARE FVector<FRenderProgram*> FRenderProgramVector;
typedef MO_FG_DECLARE GPtrLooper<FRenderProgram> GRenderProgramPtrLooper;

//============================================================
// <T>渲染纹理。</T>
//============================================================
class MO_FG_DECLARE FRenderTexture : public FRenderInstance
{
   MO_CLASS_DECLARE_INHERITS(FRenderTexture, FRenderInstance);
protected:
   ERenderTexture _textureCd;
   ERenderTextureFormat _formatCd;
   ERenderTextureFilter _filterCd;
   ERenderTextureWrap _wrapCd;
   FBytes* _pData;
   SIntSize2 _size;
public:
   FRenderTexture();
   MO_ABSTRACT ~FRenderTexture();
public:
   //------------------------------------------------------------
   // <T>获得纹理类型。</T>
   MO_INLINE ERenderTexture TextureCd(){
      return _textureCd;
   }
   //------------------------------------------------------------
   // <T>获得纹理格式。</T>
   MO_INLINE ERenderTextureFormat FormatCd(){
      return _formatCd;
   }
   //------------------------------------------------------------
   // <T>设置纹理格式。</T>
   MO_INLINE void SetFormatCd(ERenderTextureFormat formatCd){
      _formatCd = formatCd;
   }
   //------------------------------------------------------------
   // <T>获得纹理过滤。</T>
   MO_INLINE ERenderTextureFilter FilterCd(){
      return _filterCd;
   }
   //------------------------------------------------------------
   // <T>设置纹理过滤。</T>
   MO_INLINE void SetFilterCd(ERenderTextureFilter filterCd){
      _filterCd = filterCd;
   }
   //------------------------------------------------------------
   // <T>获得纹理展开。</T>
   MO_INLINE ERenderTextureWrap WrapCd(){
      return _wrapCd;
   }
   //------------------------------------------------------------
   // <T>设置纹理展开。</T>
   MO_INLINE void SetWrapCd(ERenderTextureWrap wrapCd){
      _wrapCd = wrapCd;
   }
   //------------------------------------------------------------
   // <T>获得大小。</T>
   MO_INLINE SIntSize2& Size(){
      return _size;
   }
public:
   MO_ABSTRACT TResult OnSetup();
   MO_ABSTRACT TResult Suspend();
   MO_ABSTRACT TResult Resume();
   MO_ABSTRACT TResult Upload(TByteC* pData, TInt length);
   MO_ABSTRACT TResult Unserialize(IDataInput* pInput);
};
//------------------------------------------------------------
typedef MO_FG_DECLARE GPtr<FRenderTexture> GRenderTexturePtr;
typedef MO_FG_DECLARE GPtrLooper<FRenderTexture> GRenderTexturePtrLooper;

//============================================================
// <T>渲染平面纹理。</T>
//============================================================
class MO_FG_DECLARE FRenderFlatTexture : public FRenderTexture
{
   MO_CLASS_DECLARE_INHERITS(FRenderFlatTexture, FRenderTexture);
public:
   FRenderFlatTexture();
   MO_ABSTRACT ~FRenderFlatTexture();
public:
   MO_ABSTRACT TResult Resize(TInt width, TInt height);
};
//------------------------------------------------------------
typedef MO_FG_DECLARE FList<FRenderFlatTexture*> FRenderFlatTextureList;

//============================================================
// <T>渲染CUBE纹理。</T>
//============================================================
class MO_FG_DECLARE FRenderCubeTexture : public FRenderTexture
{
   MO_CLASS_DECLARE_INHERITS(FRenderCubeTexture, FRenderTexture);
public:
   FRenderCubeTexture();
   MO_ABSTRACT ~FRenderCubeTexture();
public:
   MO_ABSTRACT TResult Resize(TInt size);
};
//------------------------------------------------------------
typedef MO_FG_DECLARE FList<FRenderCubeTexture*> FRenderCubeTextureList;

//============================================================
// <T>渲染纹理。</T>
//============================================================
class MO_FG_DECLARE FRenderMaterialTexture : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRenderMaterialTexture, FInstance);
protected:
   TString _code;
   TString _packCode;
   GRenderTexturePtr _texture;
public:
   FRenderMaterialTexture();
   MO_ABSTRACT ~FRenderMaterialTexture();
public:
   //------------------------------------------------------------
   // <T>判断是否指定代码。</T>
   MO_INLINE TBool IsCode(TCharC* pCode){
      return _code.Equals(pCode);
   }
   //------------------------------------------------------------
   // <T>获得代码。</T>
   MO_INLINE TCharC* Code(){
      return _code;
   }
   //------------------------------------------------------------
   // <T>设置代码。</T>
   MO_INLINE void SetCode(TCharC* pCode){
      _code = pCode;
   }
   //------------------------------------------------------------
   // <T>判断是否指定代码。</T>
   MO_INLINE TBool IsPackCode(TCharC* pPackCode){
      return _packCode.Equals(pPackCode);
   }
   //------------------------------------------------------------
   // <T>获得打包代码。</T>
   MO_INLINE TCharC* PackCode(){
      return _packCode;
   }
   //------------------------------------------------------------
   // <T>设置打包代码。</T>
   MO_INLINE void SetPackCode(TCharC* pPackCode){
      _packCode = pPackCode;
   }
   //------------------------------------------------------------
   // <T>获得纹理。</T>
   MO_INLINE FRenderTexture* Texture(){
      return _texture;
   }
   //------------------------------------------------------------
   // <T>设置纹理。</T>
   MO_INLINE void SetFormatCd(FRenderTexture* pTexture){
      _texture = pTexture;
   }
};
//------------------------------------------------------------
typedef MO_FG_DECLARE GPtrs<FRenderMaterialTexture> GRenderMaterialTexturePtrs;

//============================================================
// <T>渲染材质。</T>
//============================================================
class MO_FG_DECLARE FRenderMaterial : public FMaterial
{
   MO_CLASS_DECLARE_INHERITS(FRenderMaterial, FMaterial);
protected:
   // 变换名称
   GRenderMaterialTexturePtrs _textures;
public:
   FRenderMaterial();
   MO_ABSTRACT ~FRenderMaterial();
public:
   //------------------------------------------------------------
   // <T>获得渲染效果名称。</T>
   MO_INLINE GRenderMaterialTexturePtrs& Textures(){
      return _textures;
   }
public:
   TResult TexturePush(FRenderMaterialTexture* pMaterialTexture);
   TResult TextureRemove(FRenderMaterialTexture* pMaterialTexture);
   TResult TextureClear();
};

//============================================================
// <T>渲染目标。</T>
//============================================================
class MO_FG_DECLARE FRenderTarget : public FRenderInstance
{
   MO_CLASS_DECLARE_INHERITS(FRenderTarget, FRenderInstance);
protected:
   TBool _optionDepth;
   TBool _optionStencil;
   SIntSize2 _size;
   ERenderUsage _usageCd;
   ERenderTexture _textureCd;
   ERenderTextureFormat _formatCd;
   SFloatColor4 _backgroundColor;
   FRenderTextureCollection* _pTextures;
public:
   FRenderTarget();
   MO_ABSTRACT ~FRenderTarget();
public:
   //------------------------------------------------------------
   // <T>获得支持深度。</T>
   MO_INLINE TBool OptionDepth(){
      return _optionDepth;
   }
   //------------------------------------------------------------
   // <T>设置支持深度。</T>
   MO_INLINE void SetOptionDepth(TBool optionDepth){
      _optionDepth = optionDepth;
   }
   //------------------------------------------------------------
   // <T>获得支持模板。</T>
   MO_INLINE TBool OptionStencil(){
      return _optionStencil;
   }
   //------------------------------------------------------------
   // <T>设置支持模板。</T>
   MO_INLINE void SetOptionStencil(TBool optionStencil){
      _optionStencil = optionStencil;
   }
   //------------------------------------------------------------
   // <T>获得大小。</T>
   MO_INLINE SIntSize2& Size(){
      return _size;
   }
   //------------------------------------------------------------
   // <T>获得使用方式。</T>
   MO_INLINE ERenderUsage UsageCd(){
      return _usageCd;
   }
   //------------------------------------------------------------
   // <T>设置使用方式。</T>
   MO_INLINE void SetUsageCd(ERenderUsage usageCd){
      _usageCd = usageCd;
   }
   //------------------------------------------------------------
   // <T>获得纹理格式。</T>
   MO_INLINE ERenderTexture TextureCd(){
      return _textureCd;
   }
   //------------------------------------------------------------
   // <T>设置纹理格式。</T>
   MO_INLINE void SetTextureCd(ERenderTexture textureCd){
      _textureCd = textureCd;
   }
   //------------------------------------------------------------
   // <T>获得格式类型。</T>
   MO_INLINE ERenderTextureFormat FormatCd(){
      return _formatCd;
   }
   //------------------------------------------------------------
   // <T>设置格式类型。</T>
   MO_INLINE void SetFormatCd(ERenderTextureFormat formatCd){
      _formatCd = formatCd;
   }
   //------------------------------------------------------------
   // <T>获得背景色。</T>
   MO_INLINE SFloatColor4& BackgroundColor(){
      return _backgroundColor;
   }
   //------------------------------------------------------------
   // <T>获得纹理集合。</T>
   MO_INLINE FRenderTextureCollection* Textures(){
      return _pTextures;
   }
};
//------------------------------------------------------------
typedef MO_FG_DECLARE FObjects<FRenderTarget*> FRenderTargetCollection;
typedef MO_FG_DECLARE FList<FRenderTarget*> FRenderTargetList;
typedef MO_FG_DECLARE GPtrLooper<FRenderTarget> GRenderTargetPtrLooper;

//============================================================
// <T>渲染视角。</T>
//============================================================
class MO_FG_DECLARE FRenderView : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRenderView, FInstance);
protected:
   GPtr<FCamera> _camera;
   GPtr<FProjection> _projection;
   GPtr<FViewport> _viewPort;
   FRenderableCollection* _pRenderables;
   FRenderTargetCollection* _pRenderTargets;
public:
   FRenderView();
   MO_ABSTRACT ~FRenderView();
public:
   //------------------------------------------------------------
   // <T>获得相机。</T>
   MO_INLINE FCamera* Camera(){
      return _camera;
   }
   //------------------------------------------------------------
   // <T>设置相机。</T>
   MO_INLINE void SetCamera(FCamera* pCamera){
      _camera = pCamera;
   }
   //------------------------------------------------------------
   // <T>获得投影。</T>
   MO_INLINE FProjection* Projection(){
      return _projection;
   }
   //------------------------------------------------------------
   // <T>设置投影。</T>
   MO_INLINE void SetProjection(FProjection* pProjection){
      _projection = pProjection;
   }
   //------------------------------------------------------------
   // <T>获得视角。</T>
   MO_INLINE FViewport* Viewport(){
      return _viewPort;
   }
   //------------------------------------------------------------
   // <T>设置视角。</T>
   MO_INLINE void SetViewport(FViewport* pViewPort){
      _viewPort = pViewPort;
   }
   //------------------------------------------------------------
   // <T>获得渲染集合。</T>
   MO_INLINE FRenderableCollection* Renderables(){
      return _pRenderables;
   }
   //------------------------------------------------------------
   // <T>获得渲染目标集合。</T>
   MO_INLINE FRenderTargetCollection* RenderTargets(){
      return _pRenderTargets;
   }
};
//------------------------------------------------------------
typedef MO_FG_DECLARE FObjects<FRenderView*> FRenderViewCollection;

//============================================================
// <T>渲染区域。</T>
//============================================================
class MO_FG_DECLARE FRenderRegion : public FInstance
{
   MO_CLASS_DECLARE_INHERITS(FRenderRegion, FInstance);
protected:
   TBool _optionRenderTarget;
   GPtr<FRenderView> _activeView;
   FPipeline* _pActivePipeline;
   FPipelinePass* _pActivePass;
   FRenderViewCollection* _pViews;
   GPtr<FDirectionalLight> _directionalLight;
   FLightCollection* _pLights;
   FRenderableCollection* _pRenderables;
   FRenderableCollection* _pVisibleRenderables;
   FRenderTextureCollection* _pTextures;
   FVisualRegion* _pVisualRegion;
public:
   FRenderRegion();
   MO_ABSTRACT ~FRenderRegion();
public:
   //------------------------------------------------------------
   // <T>获得配置渲染目标。</T>
   MO_INLINE TBool OptionRenderTarget(){
      return _optionRenderTarget;
   }
   //------------------------------------------------------------
   // <T>设置配置渲染目标。</T>
   MO_INLINE void SetOptionRenderTarget(TBool optionRenderTarget){
      _optionRenderTarget = optionRenderTarget;
   }
   //------------------------------------------------------------
   // <T>获得激活视角。</T>
   MO_INLINE FRenderView* ActiveView(){
      return _activeView;
   }
   //------------------------------------------------------------
   // <T>设置激活视角。</T>
   MO_INLINE void SetActiveView(FRenderView* pActiveView){
      _activeView = pActiveView;
   }
   //------------------------------------------------------------
   // <T>获得激活管道。</T>
   MO_INLINE FPipeline* ActivePipeline(){
      return _pActivePipeline;
   }
   //------------------------------------------------------------
   // <T>设置激活管道。</T>
   MO_INLINE void SetActivePipeline(FPipeline* pPipeline){
      _pActivePipeline = pPipeline;
   }
   //------------------------------------------------------------
   // <T>获得激活渲染过程。</T>
   MO_INLINE FPipelinePass* ActivePass(){
      return _pActivePass;
   }
   //------------------------------------------------------------
   // <T>设置激活渲染过程。</T>
   MO_INLINE void SetActivePass(FPipelinePass* pActivePass){
      _pActivePass = pActivePass;
   }
   //------------------------------------------------------------
   // <T>获得视角集合。</T>
   MO_INLINE FRenderViewCollection* Views(){
      return _pViews;
   }
   //------------------------------------------------------------
   // <T>获得方向光源。</T>
   MO_INLINE FDirectionalLight* DirectionalLight(){
      return _directionalLight;
   }
   //------------------------------------------------------------
   // <T>设置方向光源。</T>
   MO_INLINE void SetDirectionalLight(FDirectionalLight* pDirectionalLight){
      _directionalLight = pDirectionalLight;
   }
   //------------------------------------------------------------
   // <T>获得光源集合。</T>
   MO_INLINE FLightCollection* Lights(){
      return _pLights;
   }
   //------------------------------------------------------------
   // <T>获得渲染集合。</T>
   MO_INLINE FRenderableCollection* Renderables(){
      return _pRenderables;
   }
   //------------------------------------------------------------
   // <T>获得可见渲染集合。</T>
   MO_INLINE FRenderableCollection* VisibleRenderables(){
      return _pVisibleRenderables;
   }
   //------------------------------------------------------------
   // <T>获得纹理集合。</T>
   MO_INLINE FRenderTextureCollection* Textures(){
      return _pTextures;
   }
   //------------------------------------------------------------
   // <T>获得可见区域。</T>
   MO_INLINE FVisualRegion* VisualRegion(){
      return _pVisualRegion;
   }
   //------------------------------------------------------------
   // <T>设置可见区域。</T>
   MO_INLINE void SetVisualRegion(FVisualRegion* pVisualRegion){
      _pVisualRegion = pVisualRegion;
   }
public:
   TBool TestRenderable();
};
//------------------------------------------------------------
typedef MO_FG_DECLARE FObjects<FRenderRegion*> FRenderRegionCollection;

//============================================================
// <T>渲染设备。</T>
//============================================================
class MO_FG_DECLARE FRenderDevice : public FDevice
{
   MO_CLASS_ABSTRACT_DECLARE_INHERITS(FRenderDevice, FDevice);
protected:
   // 类工厂
   FClassFactory* _pClassFactory;
   // 渲染能力
   FRenderCapability* _pCapability;
   // 填充模式
   ERenderFillMode _fillModeCd;
   // 深度信息
   TBool _optionDepth;
   ERenderDepthMode _depthModeCd;
   // 剪裁信息
   TBool _optionCull;
   ERenderCullMode _cullModeCd;
   // 混合信息
   TBool _statusBlend;
   ERenderBlendMode _blendSourceCd;
   ERenderBlendMode _blendTargetCd;
   // 程序信息
   FRenderProgram* _pProgram;
   GRenderVertexBufferPtrs _vertexBuffers;
   FRenderTextureCollection* _pTextures;
   // 激活信息
   FRenderProgram* _pActiveProgram;
   FRenderTarget* _pActiveRenderTarget;
   FBytes* _pActiveVertexData;
   FBytes* _pActiveFragmentData;
   GRenderVertexBufferPtrs _activeVertexBuffers;
   FRenderTextureCollection* _pActiveTextures;
   // 缓冲数据
   FBytes* _pVertexConsts;
   FBytes* _pFragmentConsts;
   // 存储信息
   GRenderProgramPtrLooper _storagePrograms;
   GRenderVertexBufferLooper _storageVertexBuffers;
   GRenderIndexBufferPtrLooper _storageIndexBuffers;
   GRenderTexturePtrLooper _storageTextures;
   GRenderTargetPtrLooper _storageTargets;
   // 脚本处理器
   GRenderShaderTransformerPtr _shaderTransformer;
   GRenderShaderOptimizerPtr _shaderOptimizer;
   // 统计信息
   GPtr<FRenderStatistics> _statistics;
   // 绘制效率统计
   GStatisticsPtr _renderDrawStatistics;
public:
   FRenderDevice();
   MO_ABSTRACT ~FRenderDevice();
public:
   //------------------------------------------------------------
   // <T>获得类工厂。</T>
   MO_INLINE FClassFactory* ClassFactory(){
      return _pClassFactory;
   }
   //------------------------------------------------------------
   // <T>获得渲染能力。</T>
   MO_INLINE FRenderCapability* Capability(){
      return _pCapability;
   }
   //------------------------------------------------------------
   // <T>获得统计信息。</T>
   MO_INLINE FRenderStatistics* Statistics(){
      return _statistics;
   }
   //------------------------------------------------------------
   // <T>获得渲染程序。</T>
   MO_INLINE FRenderProgram* Program(){
      return _pProgram;
   }
   //------------------------------------------------------------
   // <T>获得脚本变换器。</T>
   MO_INLINE FRenderShaderTransformer* ShaderTransformer(){
      return _shaderTransformer;
   }
   //------------------------------------------------------------
   // <T>获得脚本优化器。</T>
   MO_INLINE FRenderShaderOptimizer* ShaderOptimizer(){
      return _shaderOptimizer;
   }
public:
   MO_ABSTRACT TResult Setup();
   MO_ABSTRACT TResult Suspend();
   MO_ABSTRACT TResult Resume();
   MO_ABSTRACT TResult FrameBegin();
   MO_ABSTRACT TResult FrameEnd();
public:
   TBool UpdateConsts(ERenderShader shaderCd, TInt slot, TAnyC* pData, TInt length);
   MO_VIRTUAL TResult CheckError(TCharC* pCode, TCharC* pMessage, ...) = 0;
public:
   MO_ABSTRACT FRenderInstance* CreateObject(TCharC* pName);
   //------------------------------------------------------------
   // <T>创建指定名称的对象。</T>
   template <class T>
   MO_INLINE T* CreateObject(TCharC* pName){
      FRenderInstance* pRenderObject = CreateObject(pName);
      return pRenderObject->Convert<T>();
   }
public:
   MO_ABSTRACT FRenderVertexBuffer* CreateVertexBuffer();
   MO_ABSTRACT FRenderIndexBuffer* CreateIndexBuffer();
   MO_ABSTRACT FRenderProgram* CreateProgrom();
   MO_ABSTRACT FRenderTarget* CreateTarget();
   MO_ABSTRACT FRenderFlatTexture* CreateFlatTexture();
   MO_ABSTRACT FRenderCubeTexture* CreateCubeTexture();
public:
   MO_VIRTUAL TResult SetBackBuffer(TInt width, TInt height, TInt antiAlias, TBool depthed = ETrue) = 0;
   MO_VIRTUAL TResult SetFillMode(ERenderFillMode fillModeCd) = 0;
   MO_VIRTUAL TResult SetDepthMode(TBool depth, ERenderDepthMode depthCd = ERenderDepthMode_None) = 0;
   MO_VIRTUAL TResult SetCullingMode(TBool cull, ERenderCullMode cullCd = ERenderCullMode_None) = 0;
   MO_VIRTUAL TResult SetBlendFactors(TBool blend, ERenderBlendMode sourceCd = ERenderBlendMode_None, ERenderBlendMode targetCd = ERenderBlendMode_None) = 0;
   MO_VIRTUAL TResult SetScissorRectangle(TInt left, TInt top, TInt width, TInt height) = 0;
   MO_VIRTUAL TResult SetRenderTarget(FRenderTarget* pRenderTarget = NULL) = 0;
   MO_VIRTUAL TResult SetProgram(FRenderProgram* pProgram) = 0;
   MO_VIRTUAL TResult SetLayout(FRenderLayout* pLayout) = 0;
public:
   MO_VIRTUAL TResult BindConst(ERenderShader shaderCd, TInt slot, ERenderParameterFormat formatCd, TAnyC* pData, TInt length) = 0;
   MO_VIRTUAL TResult BindConstBuffer(FRenderProgramBuffer* pBuffer) = 0;
   MO_VIRTUAL TResult BindVertexBuffer(TInt slot, FRenderVertexBuffer* pVertexBuffer, TInt offset, ERenderAttributeFormat formatCd) = 0;
   MO_VIRTUAL TResult BindTexture(TInt slot, TInt index, FRenderTexture* pTexture) = 0;
public:
   MO_VIRTUAL TResult Clear(TFloat red = 0.0f, TFloat green = 0.0f, TFloat blue = 0.0f, TFloat alpha = 1.0f, TFloat depth = 1.0f) = 0;
   MO_VIRTUAL TResult DrawTriangles(FRenderIndexBuffer* pIndexBuffer, TInt offset, TInt count) = 0;
   MO_VIRTUAL TResult Present() = 0;
public:
   MO_ABSTRACT TResult BindConstFloat3(ERenderShader shaderCd, TInt slot, TFloat x = 0.0f, TFloat y = 0.0f, TFloat z = 0.0f);
   MO_ABSTRACT TResult BindConstFloat4(ERenderShader shaderCd, TInt slot, TFloat x = 0.0f, TFloat y = 0.0f, TFloat z = 0.0f, TFloat w = 1.0f);
   MO_ABSTRACT TResult BindConstMatrix3x3(ERenderShader shaderCd, TInt slot, TInt count, const SFloatMatrix3d* pMatrix);
   MO_ABSTRACT TResult BindConstMatrix4x3(ERenderShader shaderCd, TInt slot, TInt count, const SFloatMatrix3d* pMatrix);
   MO_ABSTRACT TResult BindConstMatrix4x4(ERenderShader shaderCd, TInt slot, TInt count, const SFloatMatrix3d* pMatrix);
public:
   MO_ABSTRACT TResult DrawInstanceTriangles(FRenderIndexBuffer* pIndexBuffer, TInt offset, TInt count);
};
//------------------------------------------------------------
typedef MO_FG_DECLARE GPtr<FRenderDevice> GRenderDevicePtr;

//============================================================
// <T>渲染工具。</T>
//============================================================
class MO_FG_DECLARE RRenderUtil
{
public:
   static TInt CalculateMergeLimit();
   static TInt CalculateInstanceCount(TInt vertexCount, TInt boneCount);
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_FG_RENDER_H__
