# my_tfm_custom_project/app/CMakeLists.txt
# 이 CMakeLists.txt는 my_tfm_custom_project/CMakeLists.txt에 의해 호출됩니다.

# 이 디렉토리 내의 비보안 애플리케이션 하위 디렉토리들을 추가합니다.
add_subdirectory(sum_client_ns_app)
# 다른 비보안 앱이 있다면 여기에 계속 추가:
# add_subdirectory(another_custom_ns_app)