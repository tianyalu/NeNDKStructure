# NeNDKStructure AndroidStudio下搭建NDK环境 
1. 将在Linux下编译好的lib目录下的.a静态库文件复制到项目的`app/libs/armeabi-v7a`目录下.  
2. 将在Linux下编译好的include目录复制到项目的`app/src/main/cpp`目录下.  
3. 配置build.gradle文件:  
```groovy
defaultConfig {
    applicationId "com.sty.ne.player"
    minSdkVersion 21  //这里的最低版本最好不小于21，否则可能编译出错
    targetSdkVersion 28
    versionCode 1
    versionName "1.0"
    testInstrumentationRunner "androidx.test.runner.AndroidJUnitRunner"
    externalNativeBuild {
        cmake {
            cppFlags ""
            //abiFilters "armeabi-v7a"  //错误的坑爹写法
        }
        ndk {
            abiFilters "armeabi-v7a"
        }
    }
}
```
4. 配置CMAkeLists.txt文件：  
```cmake
cmake_minimum_required(VERSION 3.4.1)

add_library( # Sets the name of the library.
        native-lib
        SHARED
        native-lib.cpp)
# include_directories(src/main/cpp/include) # 错误的坑爹写法
include_directories(${PROJECT_SOURCE_DIR}/include) # ${PROJECT_SOURCE_DIR} = E:/AndroidWangYiCloud/NDKWorkspace/NePlayer/app/src/main/cpp

message(WARNING "path = ${PROJECT_SOURCE_DIR}")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}") # 错误的坑爹写法
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/../../../libs/${CMAKE_ANDROID_ARCH_ABI}")
find_library( # Sets the name of the path variable.
        log-lib
        log)
target_link_libraries( # Specifies the target library.
        native-lib
        avcodec avfilter avformat avutil swresample swscale
        ${log-lib})
```
5. 修改native-lib.cpp文件
```c++
#include <jni.h>
#include <string>

//混合式编译
extern "C" {
#include <libavcodec/avcodec.h>
}
extern "C" JNIEXPORT jstring JNICALL
Java_com_sty_ne_player_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(av_version_info()); //4.0.5
}
```
~~**疑惑：**~~  
~~虽然经过一些采坑以及修改代码，最终运行成功了，但是`#include <libavcodec/avcodec.h>`和`av_version_info()`这两处依旧报红，不知何故？~~  

