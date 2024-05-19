#include "hal_st_lld.h"

#define ST_HANDLER                    LETIMER0_IRQHandler
#define ST_NUMBER                     LETIMER0_IRQn
#define ST_CLOCK_SRC                  32768U /* LFRCO clock is 32.768 Hz */
#define ST_ENABLE_CLOCK()             do {                                   \
                                        CMU->CLKEN0_SET |= CMU_CLKEN0_LFRCO; \
                                        CMU->EM23GRPACLKCTRL = (CMU->EM23GRPACLKCTRL & ~_CMU_EM23GRPACLKCTRL_CLKSEL_MASK) | CMU_EM23GRPACLKCTRL_CLKSEL_LFRCO; \
                                        CMU->CLKEN0 |= CMU_CLKEN0_LETIMER0;  \
                                      }                                      \
                                      while(0)

#define EFR32_ST_PRESC                LETIMER_CTRL_CNTPRESC_DIV4

void ST_HANDLER(void) {

  st_lld_serve_interrupt();
}

void st_lld_init(void) {
  
  /* Enabling timer clock. */
  ST_ENABLE_CLOCK();

  /* Enable timer. */
  EFR32_ST_TIM->EN_SET = LETIMER_EN_EN;

  /* Initializing the counter in free running mode. */
  EFR32_ST_TIM->IEN    = 0;
  EFR32_ST_TIM->IF_CLR = _LETIMER_IF_MASK;
  EFR32_ST_TIM->CTRL   = LETIMER_CTRL_REPMODE_FREE |
                         EFR32_ST_PRESC;
  EFR32_ST_TIM->COMP0  = 0;

  /* Wait for command to complete. */
  while (EFR32_ST_TIM->SYNCBUSY & (LETIMER_SYNCBUSY_START | LETIMER_SYNCBUSY_CNT)) {
  }

  /* Start timer on continuous mode. */
  EFR32_ST_TIM->CNT    = 0;
  EFR32_ST_TIM->CMD    = LETIMER_CMD_START;

  NVIC_SetPriority(ST_NUMBER, 4);
  NVIC_EnableIRQ(ST_NUMBER);
}

/**
 * @brief   IRQ handling code.
 */
void st_lld_serve_interrupt(void) {

  if ((EFR32_ST_TIM->IF & LETIMER_IF_COMP0) != 0U) {
    EFR32_ST_TIM->IF_CLR = LETIMER_IF_COMP0;
  }
}
