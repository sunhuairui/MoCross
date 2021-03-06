package mo.android.common;

import android.opengl.GLSurfaceView.Renderer;
import android.util.Log;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import mo.android.api.RNativeApi;

//============================================================
// <T>表面渲染器。</T>
//============================================================
public class FSurfaceRender
      implements
         Renderer
{
   protected int _frames = 0;

   protected long _startTime = System.currentTimeMillis();

   protected boolean _optionSetup;

   protected boolean _statusSetup;

   protected int _width;

   protected int _height;

   //============================================================
   // <T>创建表面处理。</T>
   //============================================================
   @Override
   public void onSurfaceCreated(GL10 gl,
                                EGLConfig config){
      _optionSetup = true;
   }

   //============================================================
   // <T>设置大小。</T>
   //============================================================
   @Override
   public void onSurfaceChanged(GL10 gl,
                                int width,
                                int height){
      _width = width;
      _height = height;
      if(_statusSetup){
         RNativeApi.resize(width, height);
      }
   }

   //============================================================
   // <T>绘制帧。</T>
   //============================================================
   @Override
   public void onDrawFrame(GL10 gl){
      long processStart = System.currentTimeMillis();
      // 配置处理
      if(_optionSetup && !_statusSetup){
         RNativeApi.setEnvironment("screen.width", String.valueOf(_width));
         RNativeApi.setEnvironment("screen.height", String.valueOf(_height));
         RNativeApi.setup();
         _statusSetup = true;
      }
      // 运行处理
      RNativeApi.process();
      // 帧速统计
      _frames++;
      long currentTick = System.currentTimeMillis();
      if(currentTick - _startTime >= 1000){
         Log.d("FPSCounter", "fps=" + _frames + " span=" + (currentTick - processStart));
         _frames = 0;
         _startTime = currentTick;
      }
   }
}
