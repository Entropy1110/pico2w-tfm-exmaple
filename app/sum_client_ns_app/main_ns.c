// my_tfm_custom_project/sum_client_ns_app/main_ns.c
#include "psa/client.h"                // PSA 클라이언트 API
#include "psa_sum_service_api.h"  // 공유 인터페이스 헤더
#include <stdio.h>                   // printf 등 (NSPE에서 stdio 리타겟팅 필요)
#include <stdint.h>

// NSPE 애플리케이션 진입점
int main(void) {
    psa_handle_t service_handle = PSA_NULL_HANDLE; // 핸들 초기화
    psa_status_t status;

    int32_t val1 = 100;
    int32_t val2 = 23;
    int32_t result = 0;

    // printf 출력을 보려면 NSPE 환경에서 UART 등으로 stdio 리타겟팅 필요
    printf("NS APP: SUM Client Application Started.\r\n");
    printf("NS APP: Attempting to connect to MY_SUM_SERVICE (SID: 0x%08X)\r\n", MY_SUM_SERVICE_SID);

    // 1. 보안 서비스에 연결
    service_handle = psa_connect(MY_SUM_SERVICE_SID, 1); // 서비스 SID, 버전 1
    if (service_handle <= 0) { // 0 (PSA_SUCCESS) 또는 음수 오류 코드
        printf("NS APP: Failed to connect to MY_SUM_SERVICE. Error code: %ld\r\n", (long)service_handle);
        return (int)service_handle; // 오류 발생 시 종료
    }
    printf("NS APP: Successfully connected to MY_SUM_SERVICE. Handle: %ld\r\n", (long)service_handle);

    // 2. 서비스 호출 (정의된 래퍼 함수 사용)
    printf("NS APP: Calling sum service with %d and %d\r\n", (int)val1, (int)val2);
    status = psa_sum_service_add(service_handle, val1, val2, &result);

    if (status == PSA_SUCCESS) {
        printf("NS APP: SUM Service returned: %d + %d = %d\r\n", (int)val1, (int)val2, (int)result);
    } else {
        printf("NS APP: SUM Service call failed. Error code: %d\r\n", status);
    }

    // 3. 서비스 연결 종료
    psa_close(service_handle);
    printf("NS APP: Disconnected from MY_SUM_SERVICE.\r\n");

    printf("NS APP: Execution finished. Entering infinite loop.\r\n");
    while (1) {
        // 보통 임베디드 NS 앱은 여기서 무한 루프를 돌거나 슬립 모드로 진입
    }
    // return 0; // 도달하지 않음
}