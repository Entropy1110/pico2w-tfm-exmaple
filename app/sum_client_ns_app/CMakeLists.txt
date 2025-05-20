# my_tfm_custom_project/app/sum_client_ns_app/CMakeLists.txt
cmake_minimum_required(VERSION 3.20)

project(sum_client_ns_app C)

# 이 애플리케이션이 TF-M Extras의 NS 앱으로 선택되었을 때 실행될 로직
# (TF-M Extras 루트 CMakeLists.txt에서 TFM_EXTRAS_NS_APP_NAME 변수를 통해 앱을 선택하는 방식)
if(TFM_EXTRAS_NS_APP_NAME STREQUAL ${PROJECT_NAME})
    message(STATUS "Configuring Non-Secure application: ${PROJECT_NAME}")

    # NS 애플리케이션의 소스 파일 목록 정의
    set(NS_APP_SOURCES_LIST
        "${CMAKE_CURRENT_SOURCE_DIR}/main_ns.c"
    )

    # NS 애플리케이션의 include 디렉토리 목록 정의
    set(NS_APP_INCLUDE_DIRS_LIST
        "${CMAKE_CURRENT_SOURCE_DIR}"
        # "${CMAKE_SOURCE_DIR}/my_tfm_custom_project/interface" # 루트 CMake에서 전역으로 추가했다면 생략 가능
    )

    # 이 변수들을 PARENT_SCOPE로 설정하여 TF-M 빌드 시스템에서 사용하도록 합니다.
    # (tf-m-extras/app/CMakeLists.txt 에서 EXTRA_NS_APP_ソース 등을 설정하는 것과 유사)
    set(EXTRA_NS_APP_SOURCES "${NS_APP_SOURCES_LIST}" PARENT_SCOPE)
    set(EXTRA_NS_APP_INCLUDE_DIRS "${NS_APP_INCLUDE_DIRS_LIST}" PARENT_SCOPE)

    # NS 애플리케이션에 필요한 추가적인 컴파일 정의나 링크 라이브러리가 있다면 여기에 추가
    # target_compile_definitions( ... PARENT_SCOPE)
    # target_link_libraries( ... PARENT_SCOPE)
else()
    message(STATUS "Skipping Non-Secure application: ${PROJECT_NAME} (not selected as TFM_EXTRAS_NS_APP_NAME)")
endif()