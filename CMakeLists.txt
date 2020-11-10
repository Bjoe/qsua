cmake_minimum_required(VERSION 3.14)

project(Qsua LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

# To build for android:
# ANDROID_ABI here should be the same as TARGET_ABI for pjproject (configure-android)
# ANDROID_NATIVE_API_LEVEL here should be the same as APP_PLATFORM for pjproject (configure-andorid)
# Add pjproject library dir to CMAKE_FIND_ROOT_PATH for example: -DCMAKE_FIND_ROOT_PATH:PATH=%{Qt:QT_INSTALL_PREFIX};/home/developer/pj-2_10-android
# TARGET_ABI=armeabi-v7a APP_PLATFORM=android-16 ./configure-android --prefix /home/developer/pj-2_10-android-16-armeabi-v7a

if(ANDROID)
    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick LinguistTools REQUIRED)
if(ANDROID)
    find_package(QT NAMES Qt6 Qt5 COMPONENTS AndroidExtras REQUIRED)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS AndroidExtras REQUIRED)
endif()
find_package(PkgConfig REQUIRED)
pkg_check_modules(PJSIP IMPORTED_TARGET libpjproject REQUIRED)

set(TS_FILES Qsua_de_DE.ts)

if(ANDROID)
    add_library(Qsua SHARED
      main.cpp
      qml.qrc
      ${TS_FILES}
    )
else()
    add_executable(Qsua
      main.cpp
      qml.qrc
      ${TS_FILES}
    )
endif()

target_sources(Qsua
    PRIVATE
    sipaccount.h
    sipaccount.cpp
    sipcall.h
    sipcall.cpp
    calllistmodel.h
    calllistmodel.cpp
    pjsuacore.h
    pjsuacore.cpp
    pjsuacontext.h
    pjsuacontext.cpp
    siplogwriter.h
    siplogwriter.cpp
    calllogentry.h
    calllogentry.cpp
    sipconference.h
    sipconference.cpp
    )

target_compile_definitions(Qsua
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(Qsua
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick PkgConfig::PJSIP)

if(ANDROID)
    target_link_libraries(Qsua PRIVATE Qt${QT_VERSION_MAJOR}::AndroidExtras)
endif()

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
