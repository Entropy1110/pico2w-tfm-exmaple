#ifndef PSA_MY_SUM_SERVICE_API_H
#define PSA_MY_SUM_SERVICE_API_H

#include "psa/client.h" // psa_status_t 등 기본 타입 포함
#include <stdint.h>

/*
 * 서비스 SID (Secure ID)
 * 이 값은 sum_service_sp_psa_manifest.json 파일의 "sid"와 반드시 일치해야 합니다.
 * TF-M 내에서 고유한 값이어야 합니다. (예: 0x0000F000 ~ 0x0000FFFF 범위 내 사용자 정의 값)
 */
#define MY_SUM_SERVICE_SID                  (0x0000F0E1)

/*
 * 서비스에 대한 시그널 (Signal)
 * 매니페스트의 "services" 배열 내 해당 서비스의 "signal" 값과 일치해야 합니다.
 */
#define MY_SUM_SERVICE_ADD_SIGNAL           (1U << (PSA_SID_TO_SIGNAL_POS(MY_SUM_SERVICE_SID))) // SID 기반으로 시그널 자동 생성 가능


/*
 * NS 클라이언트에서 사용할 서비스 호출 래퍼 함수 (선택 사항이지만 편리함)
 * 이 함수는 두 개의 int32_t 값을 SP로 보내고, 그 합을 반환받습니다.
 */
static inline psa_status_t psa_sum_service_add(psa_handle_t handle,
                                               int32_t val1,
                                               int32_t val2,
                                               int32_t *result) {
    psa_status_t status;

    psa_invec in_vecs[2] = {
        { .base = &val1, .len = sizeof(val1) },
        { .base = &val2, .len = sizeof(val2) }
    };

    psa_outvec out_vecs[1] = {
        { .base = result, .len = sizeof(*result) }
    };

    /*
     * psa_call의 type 파라미터:
     * - RoT 서비스의 일반적인 호출은 PSA_IPC_CALL을 사용합니다.
     * - 서비스 내 특정 동작은 msg->client_data 또는 부 버전(minor version)으로 구분할 수 있으나,
     * 이 예제는 단일 '더하기' 동작만 가정합니다.
     */
    status = psa_call(handle,               // psa_connect로 얻은 핸들
                      PSA_IPC_CALL,         // 메시지 타입 (표준 호출)
                      in_vecs,              // 입력 데이터 벡터 배열
                      IOVEC_LEN(in_vecs),   // 입력 벡터 배열 길이
                      out_vecs,             // 출력 데이터 버퍼 벡터 배열
                      IOVEC_LEN(out_vecs)); // 출력 벡터 배열 길이

    return status;
}

#endif // PSA_MY_SUM_SERVICE_API_H