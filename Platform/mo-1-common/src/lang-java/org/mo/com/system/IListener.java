package org.mo.com.system;

//============================================================
// <T>监听器接口。</T>
//============================================================
public interface IListener
{
   //============================================================
   // <T>获得拥有者。</T>
   //
   // @return 拥有者
   //============================================================
   Object owner();

   //============================================================
   // <T>执行处理。</T>
   //
   // @param sender 发送者
   // @param command 命令
   // @param params 参数
   // @return 执行结果
   //============================================================
   boolean process(Object sender,
                   int command,
                   Object params);
}
