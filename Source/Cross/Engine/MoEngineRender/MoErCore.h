#ifndef __MO_ER_CORE_H__
#define __MO_ER_CORE_H__
//************************************************************

#ifndef __MO_ER_COMMON_H__
#include "MoErCommon.h"
#endif // __MO_ER_COMMON_H__

#define MO_ER_EFFECT_PARAMETER_MAXCNT 256
#define MO_ER_EFFECT_ATTRIBUTE_MAXCNT 32
#define MO_ER_EFFECT_SAMPLER_MAXCNT   32

#define MO_ER_ATTRIBUTE_COLOR    TC("Color")
#define MO_ER_ATTRIBUTE_COORD    TC("Coord")
#define MO_ER_ATTRIBUTE_NORMAL   TC("Normal")
#define MO_ER_ATTRIBUTE_BINORMAL TC("Binormal")
#define MO_ER_ATTRIBUTE_TANGENT  TC("Tangent")

#define MO_ER_SAMPLER_DIFFUSE        TC("Diffuse")
#define MO_ER_SAMPLER_ALPHA          TC("Alpha")

#define MO_ER_SAMPLER_NORMAL         TC("Normal")
#define MO_ER_SAMPLER_SPECULAR_LEVEL TC("SpecularLevel")

#define MO_ER_SAMPLER_SPECULAR_COLOR TC("SpecularColor")
#define MO_ER_SAMPLER_HEIGHT         TC("Height")

#define MO_ER_SAMPLER_LIGHT          TC("Light")
#define MO_ER_SAMPLER_REFLECT        TC("Reflect")
#define MO_ER_SAMPLER_REFRACT        TC("Refract")
#define MO_ER_SAMPLER_EMISSIVE       TC("Emissive")

#define MO_ER_SAMPLER_ENVIRONMENT    TC("Environment")

MO_NAMESPACE_BEGIN

//============================================================
// <T>效果参数缓冲。</T>
//============================================================
enum EEffectParameterBuffer{
   EEffectParameterBuffer_Unknown,
   // 全局缓冲
   EEffectParameterBuffer_Global,
   // 效果缓冲
   EEffectParameterBuffer_EffectCamera,
   EEffectParameterBuffer_EffectLight,
   // 渲染缓冲
   EEffectParameterBuffer_RenderTramsform,
   EEffectParameterBuffer_RenderMaterial,
   EEffectParameterBuffer_Count,
};

//============================================================
// <T>效果参数工具。</T>
//============================================================
class MO_ER_DECLARE REffectParameterBuffer{
public:
   static TResult Parse(TCharC* pValue, EEffectParameterBuffer& bufferCd, TInt& slot);
   static TCharC* Format(EEffectParameterBuffer bufferCd);
};

//============================================================
// <T>效果参数。</T>
//============================================================
enum EEffectParameter{
   // 未知
   EEffectParameter_Unknown,
   // 变换参数
   EEffectParameter_VertexInstance,
   EEffectParameter_VertexModelMatrix,
   EEffectParameter_VertexViewMatrix,
   EEffectParameter_VertexProjectionMatrix,
   EEffectParameter_VertexViewProjectionMatrix,
   EEffectParameter_VertexModelViewProjectionMatrix,
   EEffectParameter_VertexBoneMatrix,
   // 相机参数
   EEffectParameter_VertexCameraPosition,
   //EEffectParameter_VertexCameraDirection,
   // 光源参数
   //EEffectParameter_VertexLightModelMatrix,
   //EEffectParameter_VertexLightModelViewMatrix,
   //EEffectParameter_VertexLightModelViewProjectionMatrix,
   //EEffectParameter_VertexLightPosition,
   EEffectParameter_VertexLightDirection,
   //............................................................
   // 相机参数
   //EEffectParameter_FragmentCamera,
   EEffectParameter_FragmentCameraPosition,
   //EEffectParameter_FragmentCameraDirection,
   //// 光源参数
   //EEffectParameter_FragmentLightModelMatrix4x4,
   //EEffectParameter_FragmentLightModelViewProjectrionMatrix4x4,
   //EEffectParameter_FragmentLightPosition,
   EEffectParameter_FragmentLightDirection,
   EEffectParameter_FragmentLightDepth,
   // 材质参数
   EEffectParameter_FragmentColor,
   EEffectParameter_FragmentAlpha,
   EEffectParameter_FragmentAmbientColor,
   EEffectParameter_FragmentDiffuseColor,
   EEffectParameter_FragmentDiffuseViewColor,
   EEffectParameter_FragmentSpecularColor,
   EEffectParameter_FragmentSpecularRate,
   EEffectParameter_FragmentSpecularViewColor,
   EEffectParameter_FragmentSpecularViewRate,
   EEffectParameter_FragmentReflectColor,
   EEffectParameter_FragmentShadowMaterial,
   EEffectParameter_FragmentShadowMaterialInv,
   //............................................................
   EEffectParameter_Count,
};

//============================================================
// <T>效果参数工具。</T>
//============================================================
class MO_ER_DECLARE REffectParameter{
public:
   static TResult Parse(TCharC* pValue, EEffectParameter& parameterCd, ERenderShader& shaderCd, ERenderParameterFormat& formatCd);
   static TCharC* Format(EEffectParameter parameterCd);
};

//============================================================
// <T>效果属性。</T>
//============================================================
enum EEffectAttribute{
   EEffectAttribute_Unknown,
   EEffectAttribute_Instance,
   EEffectAttribute_Position,
   EEffectAttribute_Color,
   EEffectAttribute_Coord,
   EEffectAttribute_CoordLight,
   EEffectAttribute_Normal,
   EEffectAttribute_Binormal,
   EEffectAttribute_Tangent,
   EEffectAttribute_BoneIndex,
   EEffectAttribute_BoneWeight,
   EEffectAttribute_Count,
};

//============================================================
// <T>效果属性工具。</T>
//============================================================
class MO_ER_DECLARE REffectAttribute{
public:
   static TResult Parse(TCharC* pValue, EEffectAttribute& attributeCd, ERenderAttributeFormat& formatCd);
   static TCharC* Format(EEffectAttribute attributeCd);
};

//============================================================
// <T>效果取样器类型。</T>
//============================================================
enum EEffectSampler{
   EEffectSampler_Diffuse,
   EEffectSampler_Normal,
   EEffectSampler_Specular,
   EEffectSampler_Light,
   EEffectSampler_Environment,
   EEffectSampler_LightDepth,
   EEffectSampler_Count,
};

//============================================================
// <T>效果取样器类型工具。</T>
//============================================================
class MO_ER_DECLARE REffectSampler{
public:
   static EEffectSampler Parse(TCharC* pValue, EEffectSampler samplerCd = EEffectSampler_Diffuse);
   static TCharC* Format(EEffectSampler samplerCd);
};

MO_NAMESPACE_END

//************************************************************
#endif // __MO_ER_CORE_H__
