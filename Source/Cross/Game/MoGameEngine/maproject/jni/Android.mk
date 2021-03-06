LOCAL_PATH := $(call my-dir)

#------------------------------------------------------------
include $(CLEAR_VARS)

# MO_COMPILER_FLAG       := -g -D_MO_DEBUG -D_MO_ANDROID -D_MO_X86
MO_COMPILER_FLAG       := -D_MO_ANDROID -D_MO_X86

LOCAL_MODULE           := MoGameEngine
LOCAL_ARM_MODE         := arm # thumb(2字节指令)/arm(4字节指令)
LOCAL_CFLAGS           := $(MO_COMPILER_FLAG)
LOCAL_CXXFLAGS         := $(MO_COMPILER_FLAG)
LOCAL_CPPFLAGS         := $(MO_COMPILER_FLAG)
LOCAL_CPP_EXTENSION    := .cpp
#............................................................
LOCAL_C_INCLUDES       := \
   $(LOCAL_PATH)/../../../../../Library/LibJpeg \
   $(LOCAL_PATH)/../../../../../Library/LibLzma \
   $(LOCAL_PATH)/../../../../../Library/LibFreeType \
   $(LOCAL_PATH)/../../../../Common/MoCommon \
   $(LOCAL_PATH)/../../../../Common/MoCore \
   $(LOCAL_PATH)/../../../../Common/MoMath \
   $(LOCAL_PATH)/../../../../Feature/MoFeatureLogger \
   $(LOCAL_PATH)/../../../../Feature/MoFeatureInput \
   $(LOCAL_PATH)/../../../../Feature/MoFeatureGraphic \
   $(LOCAL_PATH)/../../../../Feature/MoFeatureParticle \
   $(LOCAL_PATH)/../../../../Feature/MoFeaturePhysics \
   $(LOCAL_PATH)/../../../../Feature/MoFeatureResource \
   $(LOCAL_PATH)/../../../../Feature/MoFeatureSound \
   $(LOCAL_PATH)/../../../../Feature/MoFeatureScript \
   $(LOCAL_PATH)/../../../../Engine/MoEngine \
   $(LOCAL_PATH)/../../../../Engine/MoEngine2d \
   $(LOCAL_PATH)/../../../../Engine/MoEngine3d \
   $(LOCAL_PATH)/../../../../Engine/MoEngineFace \
   $(LOCAL_PATH)/../../../../Engine/MoEngineRender \
   $(LOCAL_PATH)/../../../../Platform/MoPlatformAndroid \
   $(LOCAL_PATH)/../../../../Platform/MoPlatformOpenGLES2 \

#............................................................
LOCAL_SRC_FILES :=

# Display
LOCAL_SRC_FILES += \
   ../../FGameStage.cpp \
   ../../FGameScene.cpp \
   ../../FGameSceneConsole.cpp \

# Library
LOCAL_SRC_FILES += \
   ../../MoGameEngine.cpp \
#............................................................
include $(BUILD_STATIC_LIBRARY)
