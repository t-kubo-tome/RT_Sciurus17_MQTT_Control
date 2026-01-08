cmake_minimum_required(VERSION 3.15)
project(RT_Sciurus17_MQTT_Control)

add_subdirectory(src/sciurus)

# testsディレクトリが存在する場合のみビルド
if(EXISTS ${CMAKE_SOURCE_DIR}/src/tests/CMakeLists.txt)
    add_subdirectory(src/tests)
endif()
