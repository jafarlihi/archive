#include <arch/i386/isr.h>

void timer_handler(registers_t *r);
void init_timer();
void timer_wait(int ticks);
void timer_phase(int hz);

