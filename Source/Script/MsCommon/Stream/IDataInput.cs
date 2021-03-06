﻿namespace MS.Common.IO
{
   //============================================================
   // <T>数据输入流。</T>
   //
   // @history MAOCY 140414
   //============================================================
   public interface IDataInput : IInput
   {
      //============================================================
      // <T>读取一个布尔值。</T>
      //
      // @return 布尔值
      //============================================================
      bool ReadBool();

      //============================================================
      // <T>读取一个有符号8位整数。</T>
      //
      // @return 有符号8位整数
      //============================================================
      sbyte ReadInt8();

      //============================================================
      // <T>读取一个有符号16位整数。</T>
      //
      // @return 有符号16位整数
      //============================================================
      short ReadInt16();

      //============================================================
      // <T>读取一个有符号32位整数。</T>
      //
      // @return 有符号32位整数
      //============================================================
      int ReadInt32();

      //============================================================
      // <T>读取一个有符号64位整数。</T>
      //
      // @return 有符号64位整数
      //============================================================
      long ReadInt64();

      //============================================================
      // <T>读取一个无符号8位整数。</T>
      //
      // @return 无符号8位整数
      //============================================================
      byte ReadUint8();

      //============================================================
      // <T>读取一个无符号16位整数。</T>
      //
      // @return 无符号16位整数
      //============================================================
      ushort ReadUint16();

      //============================================================
      // <T>读取一个无符号32位整数。</T>
      //
      // @return 无符号32位整数
      //============================================================
      uint ReadUint32();

      //============================================================
      // <T>读取一个无符号64位整数。</T>
      //
      // @return 无符号64位整数
      //============================================================
      ulong ReadUint64();

      //============================================================
      // <T>读取一个单精度浮点数。</T>
      //
      // @return 单精度浮点数
      //============================================================
      float ReadFloat();

      //============================================================
      // <T>读取一个双精度浮点数。</T>
      //
      // @return 双精度浮点数
      //============================================================
      double ReadDouble();

      //============================================================
      // <T>读取一个字符串。</T>
      //
      // @return 字符串
      //============================================================
      string ReadString();
   }
}
