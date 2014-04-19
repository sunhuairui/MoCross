package org.mo.data.logic;

import org.mo.com.lang.FObject;

//============================================================
// <T>逻辑表。</T>
//============================================================
public class FLogicTable
      extends FObject
{
   // 名称
   protected String _name;

   //============================================================
   // <T>构造逻辑表。</T>
   //============================================================
   public FLogicTable(){
   }

   //============================================================
   // <T>构造逻辑表。</T>
   //
   // @param name 字段名称
   //============================================================
   public FLogicTable(String name){
      _name = name;
   }

   //============================================================
   // <T>获得名称。</T>
   //
   // @param name 名称
   //============================================================
   public String name(){
      return _name;
   }

   //============================================================
   // <T>设置名称。</T>
   //
   // @param name 名称
   //============================================================
   public void setName(String name){
      _name = name;
   }
}
