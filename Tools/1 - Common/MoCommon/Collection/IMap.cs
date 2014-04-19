﻿using System.Collections;

namespace MO.Common.Collection
{
   //============================================================
   // <T>哈希集合接口。</T>
   //============================================================
   public interface IMap<N, V> : IEnumerable
   {
      //============================================================
      // <T>获得总数。</T>
      //
      // @return 总数
      //============================================================
      int Count { get; }

      //============================================================
      // <T>根据名称获得和设置内容。</T>
      //
      // @param name 名称
      // @return 内容
      //============================================================
      V this[N name] { get; set; }

      //============================================================
      // <T>是否含有名称。</T>
      //
      // @param name 名称
      // @return 是否含有
      //============================================================
      bool Contains(N name);
      
      //============================================================
      // <T>根据指定名称，获得内容。</T>
      //
      // @param name 名称
      // @return 内容
      //============================================================
      V Get(N name);

      //============================================================
      // <T>根据指定名称，设置内容。</T>
      //
      // @param name 名称
      // @param value 内容
      //============================================================
      void Set(N name, V value);
   }
}