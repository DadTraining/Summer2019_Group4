LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
				   $(LOCAL_PATH)/../../../Classes/Alita.cpp \
				   $(LOCAL_PATH)/../../../Classes/Bullet.cpp \
				   $(LOCAL_PATH)/../../../Classes/Kaisa_Monster.cpp \
				   $(LOCAL_PATH)/../../../Classes/LoadingScene.cpp \
				   $(LOCAL_PATH)/../../../Classes/MenuScene.cpp \
				   $(LOCAL_PATH)/../../../Classes/Objects.cpp \
				   $(LOCAL_PATH)/../../../Classes/SettingScene.cpp \
				   $(LOCAL_PATH)/../../../Classes/Murad_Monster.cpp \
				   $(LOCAL_PATH)/../../../Classes/Darts.cpp \
				   $(LOCAL_PATH)/../../../Classes/OverScene.cpp \
				   $(LOCAL_PATH)/../../../Classes/ResourceManager.cpp \
				   $(LOCAL_PATH)/../../../Classes/PlayGameScene.cpp \
				   $(LOCAL_PATH)/../../../Classes/ControlMusic.cpp \
				   $(LOCAL_PATH)/../../../Classes/Gold.cpp \
				   $(LOCAL_PATH)/../../../Classes/WinScene.cpp \
				   $(LOCAL_PATH)/../../../Classes/PlayGameScene2.cpp \
				   $(LOCAL_PATH)/../../../Classes/SaveBloodGold.cpp \
				   $(LOCAL_PATH)/../../../Classes/Item.cpp \
				   $(LOCAL_PATH)/../../../Classes/MyItems.cpp \
				    $(LOCAL_PATH)/../../../Classes/ShopScene.cpp 


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, $(LOCAL_PATH)/../../../cocos2d)
$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
