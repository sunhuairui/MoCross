#include "MoPd10Render.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FPd10RenderDevice, FPdxRenderDevice);

//============================================================
// <T>构造渲染设备。</T>
//============================================================
FPd10RenderDevice::FPd10RenderDevice(){
   // 初始化能力描述
   _pCapability = MO_CREATE(FRenderCapability);
   _pCapability->SetCode("dx10");
   _pCapability->SetLabel("DirectX 10.0");
   _pCapability->SetShaderVertexVersion("vs_4_0");
   _pCapability->SetShaderFragmentVersion("ps_4_0");
   // 初始化纹理数据
   _optionTexture = EFalse;
   //_textureLimit = 0;
   // 初始化关联集合
   _pLinkFlatTextures = MO_CREATE(FRenderFlatTextureList);
   _pLinkCubeTextures = MO_CREATE(FRenderCubeTextureList);
   // 初始化接口指针
   MO_CLEAR(_piSwapChain);
   MO_CLEAR(_piDevice);
   // 注册类集合
   _pClassFactory->Register(MO_RENDEROBJECT_PROGRAM_BUFFER,    FPd10RenderShaderBuffer::Class());
   _pClassFactory->Register(MO_RENDEROBJECT_PROGRAM_ATTRIBUTE, FRenderProgramAttribute::Class());
   _pClassFactory->Register(MO_RENDEROBJECT_PROGRAM_PARAMETER, FPd10RenderShaderParameter::Class());
   _pClassFactory->Register(MO_RENDEROBJECT_PROGRAM_SAMPLER,   FRenderProgramSampler::Class());
   _pClassFactory->Register(MO_RENDEROBJECT_LAYOUT,            FPd10RenderLayout::Class());
   _pClassFactory->Register(MO_RENDEROBJECT_BUFFER_VERTEX,     FPd10RenderVertexBuffer::Class());
   _pClassFactory->Register(MO_RENDEROBJECT_BUFFER_INDEX,      FPd10RenderIndexBuffer::Class());
   _pClassFactory->Register(MO_RENDEROBJECT_PROGRAM,           FPd10RenderProgram::Class());
   _pClassFactory->Register(MO_RENDEROBJECT_TARGET,            FPd10RenderTarget::Class());
   _pClassFactory->Register(MO_RENDEROBJECT_TEXTURE_2D,        FPd10RenderFlatTexture::Class());
   _pClassFactory->Register(MO_RENDEROBJECT_TEXTURE_CUBE,      FPd10RenderCubeTexture::Class());
   // 清空变量
   MO_CLEAR(_piRasterizerState);
   MO_CLEAR(_piBlendEnableState);
   MO_CLEAR(_piBlendDisableState);
}

//============================================================
// <T>析构渲染设备。</T>
//============================================================
FPd10RenderDevice::~FPd10RenderDevice(){
   MO_DELETE(_pCapability);
   MO_RELEASE(_piBlendEnableState);
   MO_RELEASE(_piBlendDisableState);
   // 删除关联集合
   MO_DELETE(_pLinkFlatTextures);
   MO_DELETE(_pLinkCubeTextures);
   // 释放内存
   MO_RELEASE(_piSwapChain);
   MO_RELEASE(_piDevice);
}

//============================================================
// <T>更新环境。</T>
//============================================================
TBool FPd10RenderDevice::UpdateContext(){
   TBool result = EFalse;
   // 设置激活的程序
   if(_pActiveProgram != _pProgram){
      //FPd10RenderProgram* pProgrom = (FPd10RenderProgram*)_pProgram;
      //glUseProgram(pProgrom->ProgramId());
      //_pProgram = _pActiveProgram;
      result = ETrue;
   }
   return result;
}

//============================================================
// <T>配置处理。</T>
//
// @return 处理结果
//============================================================
TResult FPd10RenderDevice::Setup(){
   // 父配置处理
   TResult result = FRenderDevice::Setup();
   // 获得屏幕设备
   FScreenDevice* pScreenDevice = RDeviceManager::Instance().Find<FScreenDevice>();
   SIntSize2& screenSize = pScreenDevice->Size();
   //............................................................
   RECT rect;
   GetClientRect(_windowHandle, &rect);
   TInt width = rect.right - rect.left;
   TInt height = rect.bottom - rect.top;
   //............................................................
   D3D10_DRIVER_TYPE driverTypes[] = {
      D3D10_DRIVER_TYPE_HARDWARE,
      D3D10_DRIVER_TYPE_WARP,
      D3D10_DRIVER_TYPE_SOFTWARE
   };
   TInt driverTypesCount = ARRAYSIZE(driverTypes);
   //............................................................
   // 创建设备和交换链
   //UINT creationFlags = D3D10_CREATE_DEVICE_BGRA_SUPPORT;
   UINT creationFlags = 0;
#ifdef _MO_DEBUG
   creationFlags |= D3D10_CREATE_DEVICE_DEBUG;
#endif
   D3D_FEATURE_LEVEL featureLevels[] = {
      D3D_FEATURE_LEVEL_10_1,
      D3D_FEATURE_LEVEL_10_0,
      D3D_FEATURE_LEVEL_9_3,
      D3D_FEATURE_LEVEL_9_1
   };
   DXGI_SWAP_CHAIN_DESC descriptor = {0};
   descriptor.BufferCount = 1;
   descriptor.BufferDesc.Width = width;
   descriptor.BufferDesc.Height = height;
   descriptor.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
   TBool m_vsync_enabled = ETrue;
   if(m_vsync_enabled){
      descriptor.BufferDesc.RefreshRate.Numerator = 60;
      descriptor.BufferDesc.RefreshRate.Denominator = 1;
   }else{
      descriptor.BufferDesc.RefreshRate.Numerator = 0;
      descriptor.BufferDesc.RefreshRate.Denominator = 1;
   }
   descriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
   descriptor.OutputWindow = _windowHandle;
   descriptor.Windowed = ETrue;
   descriptor.SampleDesc.Count = 1;
   descriptor.SampleDesc.Quality = 0;
   //descriptor.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
   //descriptor.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
   //descriptor.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
   //descriptor.Flags = 0;
   HRESULT dxResult = S_OK;
   TBool deviceSetuped = EFalse;
   for(TInt n = 0; n < driverTypesCount; n++){
      D3D10_DRIVER_TYPE driverType = driverTypes[n];
      dxResult = D3D10CreateDeviceAndSwapChain(
            NULL, driverType, NULL, creationFlags, D3D10_SDK_VERSION, &descriptor, &_piSwapChain, &_piDevice);
      if(FAILED(dxResult)){
         MO_ERROR("Create directx device failure. (driver=%d)", driverType);
      }else{
         deviceSetuped = ETrue;
         _driverType = driverType;
         break;
      }
   }
   if(!deviceSetuped){
       MO_FATAL("Create directx device failure.");
       return EFailure;
   }
   //............................................................
   // 创建渲染目标
   ID3D10Texture2D* piBackBuffer = NULL;
   dxResult = _piSwapChain->GetBuffer(0, IID_ID3D10Texture2D, (LPVOID*)&piBackBuffer);
   if(FAILED(dxResult)){
      MO_FATAL("Get back buffer failure.");
      return EFailure;
   }
   ID3D10RenderTargetView* piRenderTarget = NULL;
   dxResult = _piDevice->CreateRenderTargetView(piBackBuffer, NULL, &piRenderTarget);
   if(FAILED(dxResult)){
      MO_FATAL("Create render target view failure.");
      return EFailure;
   }else{
      MO_RELEASE(piBackBuffer);
   }
   //............................................................
   // 创建深度缓冲
   D3D10_TEXTURE2D_DESC depthDescriptor = {0};
   depthDescriptor.Width = screenSize.width;
   depthDescriptor.Height = screenSize.height;
   depthDescriptor.MipLevels = 1;
   depthDescriptor.ArraySize = 1;
   depthDescriptor.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
   depthDescriptor.SampleDesc.Count = 1;
   depthDescriptor.SampleDesc.Quality = 0;
   depthDescriptor.Usage = D3D10_USAGE_DEFAULT;
   depthDescriptor.BindFlags = D3D10_BIND_DEPTH_STENCIL;
   depthDescriptor.CPUAccessFlags = 0;
   depthDescriptor.MiscFlags = 0;
   ID3D10Texture2D* piDepthStencilBuffer = NULL;
   dxResult = _piDevice->CreateTexture2D(&depthDescriptor, NULL, &piDepthStencilBuffer);
   if(FAILED(dxResult)){
      MO_FATAL("Get backbugger failure.");
      return EFailure;
   }
   //............................................................
   // 设置测试缓冲
   //D3D10_DEPTH_STENCIL_DESC depthStencilDesc;
   //RType<D3D10_DEPTH_STENCIL_DESC>::Clear(&depthStencilDesc);
   //depthStencilDesc.DepthEnable = true;
   //depthStencilDesc.DepthWriteMask = D3D10_DEPTH_WRITE_MASK_ALL;
   //depthStencilDesc.DepthFunc = D3D10_COMPARISON_LESS;
   //depthStencilDesc.StencilEnable = true;
   //depthStencilDesc.StencilReadMask = 0xFF;
   //depthStencilDesc.StencilWriteMask = 0xFF;
   //depthStencilDesc.FrontFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
   //depthStencilDesc.FrontFace.StencilDepthFailOp = D3D10_STENCIL_OP_INCR;
   //depthStencilDesc.FrontFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
   //depthStencilDesc.FrontFace.StencilFunc = D3D10_COMPARISON_ALWAYS;
   //depthStencilDesc.BackFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
   //depthStencilDesc.BackFace.StencilDepthFailOp = D3D10_STENCIL_OP_DECR;
   //depthStencilDesc.BackFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
   //depthStencilDesc.BackFace.StencilFunc = D3D10_COMPARISON_ALWAYS;
   //ID3D10DepthStencilState* _pDepthStencilState = NULL;
   //dxResult = _piDevice->CreateDepthStencilState(&depthStencilDesc, &_pDepthStencilState);
   //if(FAILED(dxResult)){
   //   MO_FATAL("Create depth stencil state failure.");
   //   return EFailure;
   //}
   //............................................................
   // 设置深度缓冲
   D3D10_DEPTH_STENCIL_VIEW_DESC depthViewDescriptor;
   RType<D3D10_DEPTH_STENCIL_VIEW_DESC>::Clear(&depthViewDescriptor);
   depthViewDescriptor.Format = depthDescriptor.Format;
   depthViewDescriptor.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
   depthViewDescriptor.Texture2D.MipSlice = 0;
   ID3D10DepthStencilView* piDepthStencilView = NULL;
   dxResult = _piDevice->CreateDepthStencilView(piDepthStencilBuffer, &depthViewDescriptor, &piDepthStencilView);
   if(FAILED(dxResult)){
      MO_FATAL("Create depth stencil view failure.");
      return EFailure;
   }
   //............................................................
   _defaultRenderTarget = FPd10RenderTarget::InstanceCreate();
   _defaultRenderTarget->SetDevice(this);
   _defaultRenderTarget->Setup();
   _defaultRenderTarget->SetNativeRenderTarget(piRenderTarget);
   _defaultRenderTarget->SetOptionDepth(ETrue);
   _defaultRenderTarget->SetNativeDepthStencil(piDepthStencilView);
   _pActiveRenderTarget = _defaultRenderTarget;
   //............................................................
   _piDevice->OMSetRenderTargets(1, &piRenderTarget, piDepthStencilView);
   //............................................................
   // 设置光栅描述
   D3D10_RASTERIZER_DESC rasterDesc;
   RType<D3D10_RASTERIZER_DESC>::Clear(&rasterDesc);
   rasterDesc.AntialiasedLineEnable = EFalse;
   //rasterDesc.CullMode = D3D10_CULL_BACK;
   rasterDesc.CullMode = D3D10_CULL_NONE;
   rasterDesc.DepthBias = 0;
   rasterDesc.DepthBiasClamp = 0.0f;
   rasterDesc.DepthClipEnable = EFalse;
   rasterDesc.FillMode = D3D10_FILL_SOLID;
   rasterDesc.FrontCounterClockwise = EFalse;
   rasterDesc.MultisampleEnable = EFalse;
   rasterDesc.ScissorEnable = EFalse;
   rasterDesc.SlopeScaledDepthBias = 0.0f;
   ID3D10RasterizerState* _pRasterState = NULL;
   dxResult = _piDevice->CreateRasterizerState(&rasterDesc, &_pRasterState);
   if(FAILED(dxResult)){
      MO_FATAL("Create rasterizer state view failure.");
      return EFailure;
   }
   _piDevice->RSSetState(_pRasterState);
   //............................................................
   // 设置视角
   D3D10_VIEWPORT viewport = {0};
   viewport.Width = width;
   viewport.Height = height;
   viewport.MinDepth = 0.0f;
   viewport.MaxDepth = 1.0f;
   _piDevice->RSSetViewports(1, &viewport);
   //............................................................
   D3D10_BLEND_DESC blendDescriptor = {0};
   blendDescriptor.BlendEnable[0] = EFalse;
   dxResult = _piDevice->CreateBlendState(&blendDescriptor, &_piBlendDisableState);
   if(FAILED(dxResult)){
      MO_FATAL("Create blend state failure.");
   }
   blendDescriptor.BlendEnable[0] = ETrue;
   blendDescriptor.SrcBlend = D3D10_BLEND_SRC_ALPHA;
   blendDescriptor.DestBlend = D3D10_BLEND_INV_SRC_ALPHA;
   blendDescriptor.BlendOp = D3D10_BLEND_OP_ADD;
   blendDescriptor.SrcBlendAlpha = D3D10_BLEND_ONE;
   blendDescriptor.DestBlendAlpha = D3D10_BLEND_ZERO;
   blendDescriptor.BlendOpAlpha = D3D10_BLEND_OP_ADD;
   blendDescriptor.RenderTargetWriteMask[0] = D3D10_COLOR_WRITE_ENABLE_ALL;  
   dxResult = _piDevice->CreateBlendState(&blendDescriptor, &_piBlendEnableState);
   if(FAILED(dxResult)){
      MO_FATAL("Create blend state failure.");
   }
   return ESuccess;
}

//============================================================
// <T>暂停处理。</T>
//
// @return 处理结果
//============================================================
TResult FPd10RenderDevice::Suspend(){
   // 暂停处理
   FRenderDevice::Suspend();
   return ESuccess;
}

//============================================================
// <T>继续处理。</T>
//
// @return 处理结果
//============================================================
TResult FPd10RenderDevice::Resume(){
   FRenderDevice::Resume();
   return ESuccess;
}

//============================================================
// <T>检查执行错误。</T>
//
// @param pCode 代码
// @return 处理结果
//============================================================
TResult FPd10RenderDevice::CheckError(TCharC* pCode, TCharC* pMessage, ...){
   // 获得错误原因
   TBool result = EFalse;
//   GLenum errorCode = 0;
//   TCharC* pErrorReason = NULL;
//   while(ETrue){
//      // 获得错误
//      GLenum code = glGetError();
//      if(code == GL_NO_ERROR){
//         break;
//      }
//      // 获得原因
//      switch(code){
//         case GL_INVALID_OPERATION:
//            pErrorReason = "Invalid operation.";
//            break;
//         case GL_INVALID_ENUM:
//            pErrorReason = "Invalid enum.";
//            break;
//         case GL_INVALID_VALUE:
//            pErrorReason = "Invalid value.";
//            break;
//         case GL_INVALID_FRAMEBUFFER_OPERATION:
//            pErrorReason = "Invalid paramebuffer opeartion."; 
//            break;
//         case GL_OUT_OF_MEMORY:
//            pErrorReason = "Out of memory.";
//            break;
//         default:
//            pErrorReason = "Unknown"; 
//            break;
//      }
//      result = ETrue;
//      errorCode = code;
//#ifdef _MO_WINDOWS
//      break;
//#endif // _MO_WINDOWS
//   }
//   //............................................................
//   // 输出错误信息
//   if(result){
//      // 格式化可变参数字符串信息
//      TFsText message;
//      va_list params;
//      va_start(params, pMessage);
//      message.AppendFormatParameters(pMessage, params);
//      va_end(params);
//      // 输出错误信息
//      MO_ERROR("%s (code=%s, error=0x%04X(%d), reason=%s)", (TCharC*)message, pCode, errorCode, errorCode, pErrorReason);
//   }
   return result;
}

//============================================================
// <T>设置背景缓冲。</T>
//
// @return 处理结果
//============================================================
TResult FPd10RenderDevice::SetBackBuffer(TInt width, TInt height, TInt antiAlias, TBool depthed){
   return ESuccess;
}

//============================================================
// <T>设置填充模式。</T>
//
// @param fillModeCd 填充模式
// @return 处理结果
//============================================================
TResult FPd10RenderDevice::SetFillMode(ERenderFillMode fillModeCd){
   // 检查状态
   if(_fillModeCd == fillModeCd){
      return EContinue;
   }
   //D3D10_RASTERIZER_DESC description;
   //RType<D3D10_RASTERIZER_DESC>::Clear(&description);
   //description.FillMode = RDirectX10::ConvertFillMode(fillModeCd);
   //ID3D10RasterizerState* pRasterizerState = NULL;
   //_piDevice->CreateRasterizerState(&description, &pRasterizerState);
   //_piDevice->RSSetState(pRasterizerState);
//   // 设置内容
//#ifndef _MO_ANDROID
//   switch(fillModeCd){
//      case ERenderFillMode_Point:
//         glPolygonMode(GL_FRONT, GL_POINT);
//         glPolygonMode(GL_BACK, GL_POINT);
//         break;
//      case ERenderFillMode_Line:
//         glPolygonMode(GL_FRONT, GL_LINE);
//         glPolygonMode(GL_BACK, GL_LINE);
//         break;
//      case ERenderFillMode_Fill:
//         glPolygonMode(GL_FRONT, GL_FILL);
//         glPolygonMode(GL_BACK, GL_FILL);
//         break;
//   }
//#endif // _MO_ANDROID
//   _fillModeCd = fillModeCd;
//   _statistics->UpdateOptionFillCount();
   return ESuccess;
}

//============================================================
// <T>设置深度模式。</T>
//
// @param depth 深度开关
// @param depthCd 深度模式
// @return 处理结果
//============================================================
TResult FPd10RenderDevice::SetDepthMode(TBool depth, ERenderDepthMode depthCd){
   // 检查状态
   if((_optionDepth == depth) && (_depthModeCd == depthCd)){
      return EContinue;
   }
   //// 设置开关
   //if(_optionDepth != depth){
   //   if(depth){
   //      glEnable(GL_DEPTH_TEST);
   //   }else{
   //      glDisable(GL_DEPTH_TEST);
   //   }
   //   _optionDepth = depth;
   //   _statistics->UpdateOptionDeepCount();
   //}
   //// 设置内容
   //if(depth && _depthModeCd != depthCd){
   //   switch(depthCd){
   //      case ERenderDepthMode_Equal:
   //         glDepthFunc(GL_EQUAL);
   //         break;
   //      case ERenderDepthMode_NotEqual:
   //         glDepthFunc(GL_NOTEQUAL);
   //         break;
   //      case ERenderDepthMode_Less:
   //         glDepthFunc(GL_LESS);
   //         break;
   //      case ERenderDepthMode_LessEqual:
   //         glDepthFunc(GL_LEQUAL);
   //         break;
   //      case ERenderDepthMode_Greater:
   //         glDepthFunc(GL_GREATER);
   //         break;
   //      case ERenderDepthMode_GreaterEqual:
   //         glDepthFunc(GL_GEQUAL);
   //         break;
   //      case ERenderDepthMode_Always:
   //         glDepthFunc(GL_ALWAYS);
   //         break;
   //   }
   //   _depthModeCd = depthCd;
   //}
   return ESuccess;
}

//============================================================
// <T>设置剪裁模式。</T>
//
// @param cull 剪裁开关
// @param cullCd 剪裁模式
// @return 处理结果
//============================================================
TResult FPd10RenderDevice::SetCullingMode(TBool cull, ERenderCullMode cullCd){
   // 检查状态
   if((_optionCull == cull) && (_optionCull == cullCd)){
      return EContinue;
   }
   //RDirectX10::ConvertCullMode(cullCd);
   //if(_piRasterizerState == NULL){
   //   D3D10_RASTERIZER_DESC descriptor;
   //   RType<D3D10_RASTERIZER_DESC>::Clear(&descriptor);
   //   descriptor.FillMode = D3D10_FILL_SOLID;
   //   descriptor.CullMode = D3D10_CULL_NONE;
   //   HRESULT dxResult = _piDevice->CreateRasterizerState(&descriptor, &_piRasterizerState);
   //   if(FAILED(dxResult)){
   //      MO_FATAL("Create rasterizer state failure.");
   //      return EFailure;
   //   }
   //}
   //_piDevice->RSSetState(_piRasterizerState);
   //// 设置开关
   //if(_optionCull != cull){
   //   if(cull){
   //      glEnable(GL_CULL_FACE);
   //   }else{
   //      glDisable(GL_CULL_FACE);
   //   }
   //   _optionCull = cull;
   //   _statistics->UpdateOptionCullCount();
   //}
   //// 设置内容
   //if(cull && _cullModeCd != cullCd){
   //   switch(cullCd){
   //      case ERenderCullMode_Front:
   //         glCullFace(GL_FRONT);
   //         break;
   //      case ERenderCullMode_Back:
   //         glCullFace(GL_BACK);
   //         break;
   //      case ERenderCullMode_Both:
   //         glCullFace(GL_FRONT_AND_BACK);
   //         break;
   //   }
   //   _cullModeCd = cullCd;
   //}
   return ESuccess;
}

//============================================================
// <T>设置合成方式。</T>
//
// @param blend 混合方式
// @param sourceCd 来源类型
// @param targetCd 目标类型
// @return 处理结果
//============================================================
TResult FPd10RenderDevice::SetBlendFactors(TBool blend, ERenderBlendMode sourceCd, ERenderBlendMode targetCd){
   TFloat blendFactors[4] = {0};
   if(blend == ETrue){
      //_piDevice->OMSetBlendState(_piBlendEnableState, blendFactors, 0XFFFFFFFF);
   }else{
      //_piDevice->OMSetBlendState(_piBlendDisableState, blendFactors, 0XFFFFFFFF);
   }
   _piDevice->OMSetBlendState(_piBlendEnableState, blendFactors, 0XFFFFFFFF);
   //// 设置开关
   //if(_statusBlend != blend){
   //   if(blend){
   //      glEnable(GL_BLEND);
   //   }else{
   //      glDisable(GL_BLEND);
   //   }
   //   _statusBlend = blend;
   //   _statistics->UpdateOptionBlendCount();
   //}
   //// 设置效果
   //if(blend && ((_blendSourceCd != sourceCd) || (_blendTargetCd != targetCd))){
   //   GLenum source = ConvertBlendFactors(sourceCd);
   //   GLenum target = ConvertBlendFactors(targetCd);
   //   glBlendFunc(source, target);
   //   _blendSourceCd = sourceCd;
   //   _blendTargetCd = targetCd;
   //}
   return ETrue;
}

//============================================================
// <T>设置有效区域。</T>
//
// @param left 左位置
// @param top 上位置
// @param width 宽度
// @param height 高度
// @return 处理结果
//============================================================
TResult FPd10RenderDevice::SetScissorRectangle(TInt left, TInt top, TInt width, TInt height){
   D3D10_RECT rect;
   rect.left = left;
   rect.top = top;
   rect.right = left + width;
   rect.bottom = top + height;
   _piDevice->RSSetScissorRects(1, &rect);
   return ETrue;
}

//============================================================
// <T>设置渲染目标。</T>
//
// @param pRenderTarget 渲染目标
// @return 处理结果
//============================================================
TResult FPd10RenderDevice::SetRenderTarget(FRenderTarget* pRenderTarget){
   TResult result = ESuccess;
   //if(pRenderTarget == NULL){
   //   // 解除渲染目标
   //   glBindFramebuffer(GL_FRAMEBUFFER, 0);
   //   result = CheckError("glBindFramebuffer", "Bind frame buffer. (buffer_id=%d)", 0);
   //   if(result != ESuccess){
   //      return result;
   //   }
   //   // 修改视角
   //   FScreenDevice* pScreenDevice = RDeviceManager::Instance().Find<FScreenDevice>();
   //   SIntSize2& screenSize = pScreenDevice->Size();
   //   glViewport(0, 0, screenSize.width, screenSize.height);
   //   return ESuccess;
   //}else{
   //   // 绑定渲染目标
   //   GLuint frameBufferId = pRenderTarget->RenderId().uint32;
   //   glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);
   //   result = CheckError("glBindFramebuffer", "Bind frame buffer. (buffer_id=%d)", frameBufferId);
   //   if(result != ESuccess){
   //      return result;
   //   }
   //   // 修改视角
   //   SIntSize2& size = pRenderTarget->Size();
   //   glViewport(0, 0, size.width, size.height);
   //   // 清空颜色
   //   SFloatColor4& backgroundColor = pRenderTarget->BackgroundColor();
   //   glClearColor(backgroundColor.red, backgroundColor.green, backgroundColor.blue, backgroundColor.alpha);
   //   //glClearDepth(1.0f);
   //   glClearStencil(0);
   //   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   //}
   //_pActiveRenderTarget = pRenderTarget;
   return ESuccess;
}

//============================================================
// <T>设置程序。</T>
//
// @param pProgram 程序
// @return 处理结果
//============================================================
TResult FPd10RenderDevice::SetProgram(FRenderProgram* pProgram){
   TResult resultCd = ESuccess;
   // 检查程序
   //if(_pProgram == pProgram){
   //   return EContinue;
   //}
   // 设置程序
   if(pProgram != NULL){
      // 设置顶点脚本
      FPd10RenderVertexShader* pVertexShader = pProgram->VertexShader()->Convert<FPd10RenderVertexShader>();
      ID3D10VertexShader* piVertexShader = pVertexShader->NativeShader();
      _piDevice->VSSetShader(piVertexShader);
      //MO_DEBUG("Set vertex shader. (shader=0x%08X)", piVertexShader);
      // 设置像素脚本
      FPd10RenderFragmentShader* pFragmentShader = pProgram->FragmentShader()->Convert<FPd10RenderFragmentShader>();
      ID3D10PixelShader* piFragmentShader = pFragmentShader->NativeShader();
      _piDevice->PSSetShader(piFragmentShader);
      //MO_DEBUG("Set pixel shader. (shader=0x%08X)", piFragmentShader);
      // 设置输入层次
      FPd10RenderProgram* pRenderProgram = pProgram->Convert<FPd10RenderProgram>();
      ID3D10InputLayout* piInputLayout = pRenderProgram->NativeInputLayout();
      _piDevice->IASetInputLayout(piInputLayout);
      //MO_DEBUG("Set input layout. (layout=0x%08X)", piInputLayout);
   }
   _pProgram = pProgram;
   // 检查是否可以执行
   _statistics->UpdateProgramCount();
   return resultCd;
}

//============================================================
// <T>设置布局。</T>
//
// @parma pLayout 布局
// @return 处理结果
//============================================================
TResult FPd10RenderDevice::SetLayout(FRenderLayout* pLayout){
   MO_CHECK(pLayout, return ENull);
   // 获得顶点流
   TResult result = ESuccess;
   FPd10RenderLayout* pRenderLayout = pLayout->Convert<FPd10RenderLayout>();
   // 获得信息
   TInt count = pRenderLayout->Count();
   ID3D10Buffer** piBuffer = pRenderLayout->Buffer();
   UINT* bufferStride = pRenderLayout->Stride();
   UINT* bufferOffset = pRenderLayout->Offset();
   // 设置内容
   _piDevice->IASetVertexBuffers(0, count, piBuffer, bufferStride, bufferOffset);
   //MO_DEBUG("Set vertex buffers. (slot=%d, count=%d)", 0, count);
   return ESuccess;
}

//============================================================
// <T>绑定常量数据。</T>
//
// @parma shaderCd 渲染类型
// @parma slot 插槽
// @parma formatCd 格式
// @parma pData 数据
// @parma length 长度
// @return 处理结果
//============================================================
TResult FPd10RenderDevice::BindConst(ERenderShader shaderCd, TInt slot, ERenderParameterFormat formatCd, TAnyC* pData, TInt length){
   MO_FATAL_UNSUPPORT();
   return ESuccess;
}

//============================================================
// <T>绑定渲染缓冲。</T>
//
// @param pBuffer 渲染缓冲
// @return 处理结果
//============================================================
TResult FPd10RenderDevice::BindConstBuffer(FRenderProgramBuffer* pBuffer){
   MO_CHECK(pBuffer, return ENull);
   if(!pBuffer->IsStatusUsed()){
      return EContinue;
   }
   // 更新数据
   FPd10RenderShaderBuffer* pRenderBuffer = pBuffer->Convert<FPd10RenderShaderBuffer>();
   TInt slot = pRenderBuffer->Slot();
   ERenderShader shaderCd = pRenderBuffer->ShaderCd();
   ERenderShaderBuffer groupCd = pRenderBuffer->GroupCd();
   ID3D10Buffer* piBuffer = pRenderBuffer->NativeiBuffer();
   if((groupCd == ERenderShaderBuffer_Global) || (groupCd == ERenderShaderBuffer_Technique) || (groupCd == ERenderShaderBuffer_Effect)){
      _piDevice->VSSetConstantBuffers(slot, 1, &piBuffer);
      _piDevice->PSSetConstantBuffers(slot, 1, &piBuffer);
   }else if(groupCd == ERenderShaderBuffer_Renderable){
      // 更新显示相关
      if(shaderCd == ERenderShader_Vertex){
         _piDevice->VSSetConstantBuffers(slot, 1, &piBuffer);
      }else if(shaderCd == ERenderShader_Fragment){
         _piDevice->PSSetConstantBuffers(slot, 1, &piBuffer);
      }else{
         MO_FATAL("Render shader type is unknown. (shader=%d)", shaderCd);
      }
   }else{
      MO_FATAL("Render shader group is unknown. (group=%d)", groupCd);
   }
   return ESuccess;
}

//============================================================
// <T>绑定顶点缓冲。</T>
//
// @param slot 插槽
// @param pVertexBuffer 顶点缓冲
// @param offset 偏移位置
// @param formatCd 格式
// @return 处理结果
//============================================================
TResult FPd10RenderDevice::BindVertexBuffer(TInt slot, FRenderVertexBuffer* pVertexBuffer, TInt offset, ERenderAttributeFormat formatCd){
   MO_ERROR_CHECK(slot >= 0, return EFailure, "Slot value is invalid. (slot=%d)", slot);
   // 获得顶点流
   TResult result = ESuccess;
   FPd10RenderVertexBuffer* pBuffer = pVertexBuffer->Convert<FPd10RenderVertexBuffer>();
   //// 获得信息
   //ID3D10Buffer* piBuffer = pBuffer->NativeBuffer();
   //UINT bufferStride = pVertexBuffer->Stride();
   //UINT bufferOffset = offset;
   //// 设置内容
   //_piDevice->IASetVertexBuffers(slot, 1, &piBuffer, &bufferStride, &bufferOffset);
   //MO_DEBUG("Set vertex buffer. (slot=%d, buffer=0x%08X, stride=%d, offset=%d)", slot, piBuffer, bufferStride, bufferOffset);
   return result;
}

//============================================================
// <T>绑定纹理。</T>
//
// @param slot 插槽
// @param index 索引
// @param pTexture 纹理
// @return 处理结果
//============================================================
TResult FPd10RenderDevice::BindTexture(TInt slot, TInt index, FRenderTexture* pTexture){
   TResult result = ESuccess;
   //............................................................
   // 绑定纹理
   ERenderTexture textureCd = pTexture->TextureCd();
   switch (textureCd){
      case ERenderTexture_Flat2d:{
         FPd10RenderFlatTexture* pFlatTexture = (FPd10RenderFlatTexture*)pTexture;
         ID3D10ShaderResourceView* piTextureView = pFlatTexture->NativeView();
         ID3D10SamplerState* piState = pFlatTexture->NativeState();
         _piDevice->PSSetShaderResources(slot, 1, &piTextureView);
         _piDevice->PSSetSamplers(slot, 1, &piState);
         //MO_DEBUG("Set texture 2d. (slot=%d, texture=0x%08X)", slot, pTexture);
         break;
      }
      case ERenderTexture_Cube:{
         FPd10RenderCubeTexture* pCubeTexture = (FPd10RenderCubeTexture*)pTexture;
         ID3D10ShaderResourceView* piTextureView = pCubeTexture->NativeView();
         ID3D10SamplerState* piState = pCubeTexture->NativeState();
         _piDevice->PSSetShaderResources(slot, 1, &piTextureView);
         _piDevice->PSSetSamplers(slot, 1, &piState);
         //MO_DEBUG("Set texture cube. (slot=%d, texture=0x%08X)", slot, pTexture);
         break;
      }
      default:{
         MO_FATAL("Unknown texture type.");
         break;
      }
   }
   //............................................................
   // 统计数据
   _statistics->UpdateSamplerCount();
   return result;
}

//============================================================
// <T>清空内容。</T>
//
// @param red 红色
// @param green 绿色
// @param blue 蓝色
// @param alpha 透明
// @param depth 深度
// @return 处理结果
//============================================================
TResult FPd10RenderDevice::Clear(TFloat red, TFloat green, TFloat blue, TFloat alpha, TFloat depth){
   MO_CHECK(_pActiveRenderTarget, return ENull);
   FPd10RenderTarget* pRenderTarget = _pActiveRenderTarget->Convert<FPd10RenderTarget>();
   // 清空颜色
   FLOAT color[4] = {red, green, blue, alpha};
   ID3D10RenderTargetView* pRenderTargetView = pRenderTarget->NativeRenderTarget();
   _piDevice->ClearRenderTargetView(pRenderTargetView, color);
   // 清空深度
   if(pRenderTarget->OptionDepth()){
      ID3D10DepthStencilView* piDepthStencil = pRenderTarget->NativeDepthStencil();
      _piDevice->ClearDepthStencilView(piDepthStencil, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, depth, 0);
   }
   //_piDevice->ClearState();
   return ETrue;
}

//============================================================
// <T>绘制三角形。</T>
//
// @param pIndexBuffer 索引缓冲
// @param offset 开始位置
// @param count 索引总数
// @return 处理结果
//============================================================
TResult FPd10RenderDevice::DrawTriangles(FRenderIndexBuffer* pIndexBuffer, TInt offset, TInt count){
   MO_CHECK(pIndexBuffer, return ENull);
   MO_CHECK(offset >= 0, return EOutRange);
   MO_CHECK(count > 0, return EOutRange);
   TResult resultCd = ESuccess;
   // 程序绘制开始
   _pProgram->DrawBegin();
   // 设置索引流
   FPd10RenderIndexBuffer* pBuffer = pIndexBuffer->Convert<FPd10RenderIndexBuffer>();
   ID3D10Buffer* piBuffer = pBuffer->NativeBuffer();
   if(piBuffer == NULL){
      MO_FATAL("Index buffer is null.");
      return ENull;
   }
   DXGI_FORMAT strideCd = RDirectX10::ConvertIndexStride(pIndexBuffer->StrideCd());
   _piDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
   _piDevice->IASetIndexBuffer(piBuffer, strideCd, 0);
   // 绘制三角形
   _renderDrawStatistics->Begin();
   _piDevice->DrawIndexed(count, offset, 0);
   //MO_DEBUG("Draw indexed. (offset=%d, count=%d)", offset, count);
   _renderDrawStatistics->Finish();
   // 程序绘制结束
   _pProgram->DrawEnd();
   // 检查错误
   _statistics->UpdateDraw(count);
   return resultCd;
}

//============================================================
// <T>显示画面。</T>
//
// @return 处理结果
//============================================================
TResult FPd10RenderDevice::Present(){
   _piSwapChain->Present(0, 0);
   return ESuccess;
}

MO_NAMESPACE_END
