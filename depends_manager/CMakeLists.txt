#project(depends_manager)
cmake_minimum_required(VERSION 3.14)

IF (WIN32 AND MSVC)

include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
set(FETCHCONTENT_QUIET OFF)

#https://www.libsdl.org/download-2.0.php
#FetchContent_Declare(
#  sdl2_win_x64_release_downloaded
#  URL https://www.libsdl.org/release/SDL2-devel-2.0.20-VC.zip
#)
#FetchContent_MakeAvailable(sdl2_win_x64_release_downloaded)
#message ("SDL2 debug downloaded at '${sdl2_win_x64_release_downloaded_SOURCE_DIR}'")

#add_library(sdl2main STATIC IMPORTED GLOBAL)
#set_property(TARGET sdl2main PROPERTY IMPORTED_LOCATION "${sdl2_win_x64_release_downloaded_SOURCE_DIR}/lib/x64/SDL2main.lib")
#set_property(TARGET sdl2main PROPERTY IMPORTED_LOCATION_RELEASE "${sdl2_win_x64_release_downloaded_SOURCE_DIR}/lib/x64/SDL2main.lib")
#set_property(TARGET sdl2main PROPERTY IMPORTED_LOCATION_DEBUG "${sdl2_win_x64_release_downloaded_SOURCE_DIR}/lib/x64/SDL2main.lib")

#https://opencv.org/releases/
#https://github.com/opencv/opencv/releases/tag/4.5.5
FetchContent_Declare(
  opencv_win_x64_downloaded
  URL https://github.com/opencv/opencv/releases/download/4.5.5/opencv-4.5.5-vc14_vc15.exe
)
FetchContent_MakeAvailable(opencv_win_x64_downloaded)
message ("OpenCV release downloaded at ${opencv_win_x64_downloaded_SOURCE_DIR}'")

add_library(OpenCV SHARED IMPORTED GLOBAL)
set_property(TARGET OpenCV PROPERTY IMPORTED_IMPLIB "${opencv_win_x64_downloaded_SOURCE_DIR}/build/x64/vc15/lib/opencv_world455.lib")
set_property(TARGET OpenCV PROPERTY IMPORTED_LOCATION "${opencv_win_x64_downloaded_SOURCE_DIR}/build/x64/vc15/bin/opencv_world455.dll")
set_property(TARGET OpenCV PROPERTY IMPORTED_IMPLIB_RELEASE "${opencv_win_x64_downloaded_SOURCE_DIR}/build/x64/vc15/lib/opencv_world455.lib")
set_property(TARGET OpenCV PROPERTY IMPORTED_LOCATION_RELEASE "${opencv_win_x64_downloaded_SOURCE_DIR}/build/x64/vc15/bin/opencv_world455.dll")
set_property(TARGET OpenCV PROPERTY IMPORTED_IMPLIB_DEBUG "${opencv_win_x64_downloaded_SOURCE_DIR}/build/x64/vc15/lib/opencv_world455d.lib")
set_property(TARGET OpenCV PROPERTY IMPORTED_LOCATION_DEBUG "${opencv_win_x64_downloaded_SOURCE_DIR}/build/x64/vc15/bin/opencv_world455d.dll")
target_include_directories(OpenCV INTERFACE "${opencv_win_x64_downloaded_SOURCE_DIR}/build/include")

#https://www.boost.org/users/history/version_1_77_0.html
FetchContent_Declare(
  boost_win_downloaded
  URL https://boostorg.jfrog.io/artifactory/main/release/1.77.0/source/boost_1_77_0.zip
)
FetchContent_MakeAvailable(boost_win_downloaded)
message ("Boost downloaded at ${boost_win_downloaded_SOURCE_DIR}'")

add_library(boost_headers INTERFACE)
target_include_directories(boost_headers INTERFACE
        "${boost_win_downloaded_SOURCE_DIR}")
        
ELSE ()

#find_package(SDL2 REQUIRED)
#message ("SDL2 libraries founded at '${SDL2_LIBRARIES}'")
#message ("SDL2 includes founded at '${SDL2_INCLUDE_DIRS}'")
#add_library(sdl2 STATIC main.cpp)
#target_link_libraries(sdl2 "${SDL2_LIBRARIES}")
#target_include_directories(sdl2 INTERFACE "${SDL2_INCLUDE_DIRS}")

find_package(OpenCV REQUIRED)
message ("OpenCV libraries founded at '${OpenCV_LIBRARIES}'")
message ("OpenCV includes founded at '${OpenCV_INCLUDE_DIRS}'")
add_library(OpenCV STATIC main.cpp)
target_link_libraries(OpenCV "${OpenCV_LIBRARIES}")
target_include_directories(OpenCV INTERFACE "${OpenCV_INCLUDE_DIRS}")

set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.71.0 REQUIRED)
message ("Boost libraries founded at '${Boost_LIBRARIES}'")
message ("Boost includes founded at '${Boost_INCLUDE_DIRS}'")
add_library(boost_headers INTERFACE)
target_include_directories(boost_headers INTERFACE "${Boost_INCLUDE_DIRS}")

ENDIF ()
