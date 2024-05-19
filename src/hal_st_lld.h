#ifndef HAL_ST_LLD_H
#define HAL_ST_LLD_H

#include "em_letimer.h"

typedef long systime_t;

#define ST_INIT_VALUE                        0x00FFFFFFUL

#define EFR32_ST_TIM                         LETIMER0

#ifdef __cplusplus
extern "C" {
#endif
void st_lld_init(void);
void st_lld_serve_interrupt(void);
#ifdef __cplusplus
}
#endif

static inline systime_t st_lld_get_counter(void) {

  return (systime_t)(ST_INIT_VALUE - EFR32_ST_TIM->CNT);
}

static inline void st_lld_start_alarm(systime_t abstime) {

  EFR32_ST_TIM->IEN_CLR = LETIMER_IEN_COMP0;

  EFR32_ST_TIM->COMP0 = (uint32_t)ST_INIT_VALUE - (uint32_t)abstime;

  EFR32_ST_TIM->IEN_SET = LETIMER_IEN_COMP0;
}

static inline void st_lld_stop_alarm(void) {

  EFR32_ST_TIM->IEN_CLR = LETIMER_IEN_COMP0;
}

static inline void st_lld_set_alarm(systime_t abstime) {

  st_lld_start_alarm(abstime);
}

static inline systime_t st_lld_get_alarm(void) {

  return (systime_t)(ST_INIT_VALUE - EFR32_ST_TIM->COMP0);
}

static inline bool st_lld_is_alarm_active(void) {

  return (EFR32_ST_TIM->IEN & LETIMER_IEN_COMP0) != 0U;
}

#endif
