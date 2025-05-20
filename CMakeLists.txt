# my_tfm_custom_project/CMakeLists.txt
cmake_minimum_required(VERSION 3.20)

project(my_tfm_custom_project)

message(STATUS "Processing My Custom TF-M Project (Extras Style) from: ${CMAKE_CURRENT_SOURCE_DIR}")

# 전역적으로 이 프로젝트의 interface 디렉토리를 include 경로에 추가할 수 있습니다.
# 이렇게 하면 하위 프로젝트들에서 상대 경로를 더 간단하게 사용할 수 있습니다.
include_directories(SYSTEM "${CMAKE_CURRENT_SOURCE_DIR}/interface")

# 하위 디렉토리(partitions, app)의 CMakeLists.txt를 순차적으로 처리
add_subdirectory(partitions)
add_subdirectory(app)