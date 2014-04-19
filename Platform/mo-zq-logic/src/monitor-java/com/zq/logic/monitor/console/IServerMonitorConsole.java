package com.zq.logic.monitor.console;

//============================================================
// <T>服务器监视控制台接口。</T>
//============================================================ 
public interface IServerMonitorConsole{

   //============================================================
   // <T>注册监视器。</T>
   //
   // @param monitor 监视器
   //============================================================
   void register(IServerMonitor monitor);

   //============================================================
   // <T>启动处理。</T>
   //============================================================
   void startup();
}