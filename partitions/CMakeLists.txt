# my_tfm_custom_project/partitions/CMakeLists.txt
# 이 CMakeLists.txt는 my_tfm_custom_project/CMakeLists.txt에 의해 호출됩니다.

# 이 디렉토리 내의 보안 파티션 하위 디렉토리들을 추가합니다.
add_subdirectory(sum_service_sp)
# 다른 보안 파티션이 있다면 여기에 계속 추가:
# add_subdirectory(another_custom_sp)