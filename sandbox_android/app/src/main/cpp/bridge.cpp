#include <jni.h>
#include <string>
#include <android/log.h>
#include <android/bitmap.h>
#include <memory>

#include "AndroidApplication.h"
#include "resource/asset_manager.h"

#define  LOG_TAG    "purple"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

std::shared_ptr<AndroidApplication> app = nullptr;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved){
    LOGI("jni onload called");
    JNIEnv* env = nullptr; //注册时在JNIEnv中实现的，所以必须首先获取它
    if(vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) { //从JavaVM获取JNIEnv，一般使用1.4的版本
        return -1;
    }
//    app = std::make_shared<AndroidApplication>();
    return JNI_VERSION_1_4; //
}

extern "C"
JNIEXPORT void JNICALL
Java_panyi_xyz_textrender_NativeBridge_init(JNIEnv *env, jclass clazz) {
    app = std::make_shared<AndroidApplication>();
    LOGI("app init");
    app->init();
}

extern "C"
JNIEXPORT void JNICALL
Java_panyi_xyz_textrender_NativeBridge_tick(JNIEnv *env, jclass clazz) {
    //LOGI("app tick");
    app->tick();
}

extern "C"
JNIEXPORT void JNICALL
Java_panyi_xyz_textrender_NativeBridge_free(JNIEnv *env, jclass clazz) {
    LOGI("app free");
    app->dispose();
}

extern "C"
JNIEXPORT void JNICALL
Java_panyi_xyz_textrender_NativeBridge_resize(JNIEnv *env, jclass clazz, jint width, jint height) {
    LOGI("app resize %d , %d" , width , height);
    app->resize(width , height);
}

extern "C"
JNIEXPORT void JNICALL
Java_panyi_xyz_textrender_NativeBridge_setAndroidAssetManager(JNIEnv *env, jclass clazz,
                                                              jobject mgr) {
    purple::AndroidAssetManager::AndroidAssetManagerInstance = AAssetManager_fromJava(env , mgr);
//    AndroidApplication::AndroidAssetManagerInstance = AAssetManager_fromJava(env , mgr);
}

extern "C"
JNIEXPORT void JNICALL
Java_panyi_xyz_textrender_NativeBridge_handleOnAction(JNIEnv *env, jclass clazz, jint action,
                                                      jfloat x, jfloat y) {
    // LOGI("onAction: %d , %f , %f" , action , x , y);
    if(app != nullptr){
        int transformAction = -1;
//        switch (action) {
//            case 0://down
//                transformAction = ACTION_DOWN;
//                break;
//            case 1://up
//                transformAction = ACTION_UP;
//                break;
//            case 2://move
//                transformAction = ACTION_MOVE;
//                break;
//            default:
//                break;
//        }//end switch
//        if(transformAction >= 0){
//            app->onTouchEvent(action , x , y);
//        }
        app->onTouchEvent(action , x , y);
    }//end if
}