//============================================================
// <T>共通定义。</T>
//============================================================
#ifndef __MO_FR_PUBLIC_H__
#define __MO_FR_PUBLIC_H__

#ifndef __MO_COMMON_H__
#include <MoCommon.h>
#endif // __MO_COMMON_H__

#ifndef __MO_CORE_H__
#include <MoCore.h>
#endif // __MO_CORE_H__

#ifndef __MO_MATH_H__
#include <MoMath.h>
#endif // __MO_MATH_H__

//============================================================
/// @define 导出定义
#ifdef _MO_FR_EXPORTS
#define MO_FR_DECLARE MO_EXPORT
#else
#define MO_FR_DECLARE MO_IMPORT
#endif // _MO_FR_EXPORTS

MO_NAMESPACE_BEGIN

MO_NAMESPACE_END

#endif // __MO_FR_PUBLIC_H__
