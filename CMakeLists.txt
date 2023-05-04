if(DEFINED BUILD_SHARED_LIBS AND NOT BUILD_SHARED_LIBS)
    # 'target_link_libraries' does not work correctly when called from
    # different directory where 'add_library' is called: CMake generates
    # incorrect OpenVINOConfig.cmake in this case
    cmake_minimum_required(VERSION 3.17)
else()
    if(CPACK_GENERATOR STREQUAL "DEB")
        # we have to use CPACK_DEBIAN_PACKAGE_SHLIBDEPS_PRIVATE_DIRS variable
        cmake_minimum_required(VERSION 3.20)
    else()
        # default choice
        cmake_minimum_required(VERSION 3.13)
    endif()
endif()

project(openvino_test)

set(CMAKE_CXX_STANDARD 17)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(openvino_test main.cpp OpenvinoInfer.cpp OpenvinoInfer.h)

target_link_libraries(openvino_test ${OpenCV_LIBS})

target_link_libraries(openvino_test
        /usr/local/openvino/runtime/lib/intel64/libopenvino.so)

target_include_directories(openvino_test PUBLIC
        /usr/local/openvino/runtime/include/
        /usr/local/openvino/runtime/include/ie/)