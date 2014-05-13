#include "MoBfRender.h"

MO_NAMESPACE_BEGIN

MO_CLASS_IMPLEMENT_INHERITS(FBfRenderVertexShader, FRenderVertexShader);

//============================================================
// <T>������Ⱦ����</T>
//============================================================
FBfRenderVertexShader::FBfRenderVertexShader(){
   MO_CLEAR(_piData);
   MO_CLEAR(_piShader);
}

//============================================================
// <T>������Ⱦ����</T>
//============================================================
FBfRenderVertexShader::~FBfRenderVertexShader(){
   MO_RELEASE(_piData);
   MO_RELEASE(_piShader);
}

//============================================================
// <T>���ô�����</T>
//
// @return �������
//============================================================
TResult FBfRenderVertexShader::Setup(){
   return ESuccess;
}

//============================================================
// <T>���봦����</T>
//
// @param pSource �����ַ���
// @return �������
//============================================================
TResult FBfRenderVertexShader::Compile(TCharC* pSource){
   // ����豸��Ϣ
   MO_CHECK(_pDevice, return ENull);
   FBfRenderDevice* pRenderDevice = _pDevice->Convert<FBfRenderDevice>();
   FRenderCapability* pCapability = pRenderDevice->Capability();
   TCharC* pShaderVersion = pCapability->ShaderVertexVersion();
   // ���ñ�־
   //TUint32 shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
   TUint32 shaderFlags = 0;
#ifdef _MO_DEBUG
    shaderFlags |= D3DCOMPILE_DEBUG;
#endif // _MO_DEBUG
    // �ϴ�����
   TInt length = RString::Length(pSource);
   ID3D10Blob* piError = NULL;
   HRESULT shaderResult = S_OK;
   HRESULT dxResult = D3DX10CompileFromMemory(pSource, length, NULL, NULL, NULL, "main", pShaderVersion, shaderFlags, 0, NULL, &_piData, &piError, &shaderResult);
   if(FAILED(dxResult) || FAILED(shaderResult)){
      TCharC* pBuffer = (TCharC*)piError->GetBufferPointer();
      MO_ERROR("Compile from memory failure.\n%s", pBuffer);
      MO_RELEASE(piError);
      MO_FATAL("Compile failure.");
      return EFailure;
   }
   // ������Ⱦ��
   TAny* pData = _piData->GetBufferPointer();
   TInt dataSize = _piData->GetBufferSize();
   dxResult = pRenderDevice->NativeDevice()->CreateVertexShader(pData, dataSize, &_piShader);
   if(FAILED(dxResult)){
      MO_FATAL("Create vertex shader failure.");
      return EFailure;
   }
   MO_INFO("Create vertex shader success. (status=%d)\n%s", dxResult, pSource);
   return ESuccess;
}

//============================================================
// <T>��������</T>
//
// @return �������
//============================================================
TResult FBfRenderVertexShader::Suspend(){
   return ESuccess;
}

//============================================================
// <T>����������</T>
//
// @return �������
//============================================================
TResult FBfRenderVertexShader::Resume(){
   return ESuccess;
}

//============================================================
// <T>����������</T>
//
// @return �������
//============================================================
TResult FBfRenderVertexShader::Dispose(){
   return ESuccess;
}

MO_NAMESPACE_END