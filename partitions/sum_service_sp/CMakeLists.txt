# my_tfm_custom_project/partitions/sum_service_sp/CMakeLists.txt
cmake_minimum_required(VERSION 3.20)

project(sum_service_sp C)

set(PARTITION_NAME_UPPER SUM_SERVICE_SP) # 매니페스트의 'name'과 일치 (대문자)
set(PARTITION_NAME_LOWER sum_service_sp) # 라이브러리 이름 등에 사용할 소문자 이름

# 1. 파티션 소스 라이브러리 정의
set(PARTITION_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/sum_service_sp.c"
)
set(PARTITION_INCLUDES
    "${CMAKE_CURRENT_SOURCE_DIR}" # sum_service_sp.h
    # "${CMAKE_SOURCE_DIR}/my_tfm_custom_project/interface" # 루트 CMake에서 전역으로 추가했다면 생략 가능
)

add_library(${PARTITION_NAME_LOWER}_lib STATIC ${PARTITION_SOURCES})
target_include_directories(${PARTITION_NAME_LOWER}_lib PUBLIC ${PARTITION_INCLUDES})

# 2. 매니페스트 파일 및 생성될 헤더 파일 경로 설정
set(MANIFEST_FILE "${CMAKE_CURRENT_SOURCE_DIR}/sum_service_sp.yaml")
set(GENERATED_MANIFEST_HEADER_DIR "${CMAKE_BINARY_DIR}/generated/interface/src") # 생성된 매니페스트 헤더 경로
set(GENERATED_MANIFEST_HEADER "${GENERATED_MANIFEST_HEADER_DIR}/psa_manifest_${PARTITION_NAME_LOWER}.h")

# 3. TF-M 빌드 시스템에 파티션 등록 (tfm_add_partition 함수 사용)
# 이 함수는 TF-M 코어 빌드 시스템의 CMake 매크로/함수입니다.
tfm_add_partition(
    TARGET              ${PARTITION_NAME_LOWER}_target # TF-M 내부에서 사용할 타겟 이름
    BASE_NAME           ${PARTITION_NAME_UPPER}        # 매니페스트의 "name" 필드와 일치
    MANIFEST_FILE       ${MANIFEST_FILE}
    GENERATED_HEADER    ${GENERATED_MANIFEST_HEADER}
    SOURCES_LIB         ${PARTITION_NAME_LOWER}_lib    # 위에서 정의한 소스 라이브러리
    # STACK_SIZE          # 매니페스트에서 읽어옴 (또는 여기서 오버라이드 가능)
    # PRIORITY            # 매니페스트에서 읽어옴
    # DEPENDENCIES        # 매니페스트에서 읽어옴
)

# 생성된 매니페스트 헤더를 포함 경로에 추가
# (tfm_add_partition이 자동으로 처리해줄 수도 있지만, 명시적으로 추가하는 것이 안전할 수 있음)
# target_include_directories(${PARTITION_NAME_LOWER}_lib INTERFACE
#    ${GENERATED_MANIFEST_HEADER_DIR}
# )
# 실제로는 tfm_add_partition 매크로가 INTERFACE_PSA_ROT_PARTITION_GENERATED_HEADER_DIR 와 같은 변수를 설정하여
# 전역적으로 include 경로가 관리될 가능성이 높습니다.