#include "em_common.h"
#include "em_chip.h"
#include "hal_st_lld.h"

int main(void)
{
  CHIP_Init();
  SystemCoreClockUpdate();

  st_lld_init();

  while (1)
  {
    st_lld_set_alarm(st_lld_get_counter()+4096);
    for (volatile int i = 0; i < 1000000; i++);
  }

  return 0;
}

void _start(void)
{
  main();
  NVIC_SystemReset();
}
