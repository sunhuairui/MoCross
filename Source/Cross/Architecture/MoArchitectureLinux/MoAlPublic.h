//============================================================
// <T>共通定义。</T>
//============================================================
#ifndef __MO_AL_PUBLIC_H__
#define __MO_AL_PUBLIC_H__

#ifndef __MO_COMMON_H__
#include <MoCommon.h>
#endif // __MO_COMMON_H__

//============================================================
/// @define 导出定义
#ifdef _MO_AL_EXPORTS
#define MO_AL_DECLARE MO_EXPORT
#else
#define MO_AL_DECLARE MO_IMPORT
#endif // _MO_AL_EXPORTS

MO_NAMESPACE_BEGIN

MO_NAMESPACE_END

#endif // __MO_AL_PUBLIC_H__
