package org.mo.core.aop.descriptor;

import org.mo.com.lang.reflect.FClass;

//============================================================
// <T>AOP描述器接口。</T>
//============================================================
public interface IAopDescriptor
{
   //============================================================
   // <T>关联类对象。</T>
   //
   // @param clazz 类对象
   //============================================================
   public void linkClass(FClass<?> clazz);

   //============================================================
   // <T>创建实例。</T>
   //
   // @return 实例
   //============================================================
   public <V> V newInstance();
}