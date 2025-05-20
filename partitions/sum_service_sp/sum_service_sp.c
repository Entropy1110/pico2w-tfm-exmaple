#include "sum_service_sp.h"
#include "psa_my_sum_service_api.h" // 서비스 SID 및 시그널 정의 포함
#include "tfm_sp_log.h"             // TF-M 로깅 유틸리티 (선택 사항)
#include "psa/error.h"              // PSA 오류 코드
#include "psa/service.h"            // PSA IPC 함수

/* '더하기' 요청을 처리하는 내부 함수 */
static psa_status_t handle_sum_request(const psa_msg_t *msg) {
    int32_t val1, val2, sum_result;

    // 입력 벡터 개수 및 크기 확인
    if (msg->in_size[0] != sizeof(int32_t) || msg->in_size[1] != sizeof(int32_t)) {
        LOG_ERRFMT("[SUM_SP] Programmer error: Invalid input vector size.\r\n");
        return PSA_ERROR_PROGRAMMER_ERROR;
    }

    // 출력 벡터 크기 확인
    if (msg->out_size[0] < sizeof(int32_t)) {
        LOG_ERRFMT("[SUM_SP] Programmer error: Output buffer too small.\r\n");
        return PSA_ERROR_PROGRAMMER_ERROR;
    }

    // 입력 데이터 읽기
    psa_read(msg->handle, 0, &val1, sizeof(val1));
    psa_read(msg->handle, 1, &val2, sizeof(val2));

    // 계산 수행
    sum_result = val1 + val2;

    LOG_DBGFMT("[SUM_SP] Calculation: %d + %d = %d\r\n", val1, val2, sum_result);

    // 결과 데이터 쓰기
    psa_write(msg->handle, 0, &sum_result, sizeof(sum_result));

    return PSA_SUCCESS;
}

/* 보안 파티션 메인 함수 (SFN - Secure Function) */
psa_status_t sum_service_sp_main(void) {
    psa_signal_t signals;

    LOG_INFFMT("[SUM_SP] SUM Service Secure Partition initialized.\r\n");

    while (1) {
        // 시그널 대기 (블로킹 호출)
        signals = psa_wait(PSA_WAIT_ANY, PSA_BLOCK);

        LOG_DBGFMT("[SUM_SP] Received signal: 0x%x\r\n", (unsigned int)signals);

        // MY_SUM_SERVICE_ADD_SIGNAL 시그널 처리
        if (signals & MY_SUM_SERVICE_ADD_SIGNAL) {
            psa_msg_t msg;

            // 메시지 가져오기
            if (psa_get(MY_SUM_SERVICE_ADD_SIGNAL, &msg) != PSA_SUCCESS) {
                LOG_ERRFMT("[SUM_SP] Error getting message for MY_SUM_SERVICE_ADD_SIGNAL.\r\n");
                continue; // 다음 시그널 대기
            }

            switch (msg.type) {
                case PSA_IPC_CONNECT:
                    LOG_DBGFMT("[SUM_SP] Client connected to MY_SUM_SERVICE.\r\n");
                    psa_reply(msg.handle, PSA_SUCCESS); // 연결 요청에 응답
                    break;
                case PSA_IPC_CALL:
                    LOG_DBGFMT("[SUM_SP] Client called MY_SUM_SERVICE.\r\n");
                    // 실제 작업 처리 (이 예제에서는 더하기)
                    psa_status_t call_status = handle_sum_request(&msg);
                    psa_reply(msg.handle, call_status); // 호출에 응답
                    break;
                case PSA_IPC_DISCONNECT:
                    LOG_DBGFMT("[SUM_SP] Client disconnected from MY_SUM_SERVICE.\r\n");
                    psa_reply(msg.handle, PSA_SUCCESS); // 연결 종료 요청에 응답
                    break;
                default:
                    LOG_ERRFMT("[SUM_SP] Unsupported message type: %d\r\n", (int)msg.type);
                    psa_reply(msg.handle, PSA_ERROR_NOT_SUPPORTED);
                    break;
            }
        } else {
            // 처리되지 않은 다른 시그널 (오류 또는 예상치 못한 상황)
            LOG_ERRFMT("[SUM_SP] Received unhandled signal: 0x%x\r\n", (unsigned int)signals);
            // 필요시 오류 처리 로직 추가
        }
    }
    /* SFN 루프는 보통 무한 반복하므로 이 부분은 도달하지 않음 */
    // return PSA_SUCCESS;
}