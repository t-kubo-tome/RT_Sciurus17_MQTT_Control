cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(list_samples
    s17_study
    s17_realtime
)

foreach(sample IN LISTS list_samples)
    message("${sample}")
    add_executable(${sample}.app ${sample}.cpp)
    target_link_libraries(${sample}.app PRIVATE rt_manipulators_cpp)
    install(TARGETS ${sample}.app RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
endforeach()
