#project(QuiltingHelp)
cmake_minimum_required(VERSION 3.11)

IF (WIN32 AND MSVC)

add_executable(QuiltingHelp WIN32 main.cpp)

add_custom_command(TARGET QuiltingHelp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:OpenCV>
        $<TARGET_FILE_DIR:QuiltingHelp>)

ELSE ()

add_executable(QuiltingHelp main.cpp)

ENDIF ()
target_compile_features(QuiltingHelp PRIVATE cxx_std_17)
target_link_libraries(QuiltingHelp OpenCV boost_headers)
