#ifndef SUM_SERVICE_SP_H
#define SUM_SERVICE_SP_H

#include "psa/service.h" // psa_status_t, psa_signal_t 등

/* 매니페스트에 정의된 SP 진입점 함수 */
psa_status_t sum_service_sp_main(void);

#endif // SUM_SERVICE_SP_H