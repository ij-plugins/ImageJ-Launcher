cmake_minimum_required(VERSION 3.0)
project(ImageJ-Launcher)

set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/appicon.rc")

add_executable(ImageJ 
               WIN32 
               Launcher.cpp
               ${APP_ICON_RESOURCE_WINDOWS}
)