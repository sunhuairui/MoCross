package org.mo.script.as.converter;

import org.mo.com.lang.FObject;
import org.mo.com.xml.FXmlNode;

//============================================================
// <T>AS类转换器。</T>
//============================================================
public class FAsClassConvert
      extends FObject
{
   // Java类名称
   protected String _javaClassName;

   // As类名称
   protected String _asClassName;

   //============================================================
   // <T>构造AS类转换器。</T>
   //============================================================
   public FAsClassConvert(){
   }

   //============================================================
   // <T>获得AS类名称。</T>
   //
   // @return 类名称
   //============================================================
   public String asClassName(){
      return _asClassName;
   }

   //============================================================
   // <T>设置AS类名称。</T>
   //
   // @param className 类名称
   //============================================================
   public void setAsClassName(String className){
      _asClassName = className;
   }

   //============================================================
   // <T>获得Java类名称。</T>
   //
   // @return 类名称
   //============================================================
   public String javaClassName(){
      return _javaClassName;
   }

   //============================================================
   // <T>设置Java类名称。</T>
   //
   // @param className 类名称
   //============================================================
   public void setJavaClassName(String className){
      _javaClassName = className;
   }

   //============================================================
   // <T>设置配置信息。</T>
   //
   // @param xconfig 配置节点
   //============================================================
   public void loadConfig(FXmlNode xconfig){
      _asClassName = xconfig.get("as_class");
      _javaClassName = xconfig.get("java_class");
   }
}
