/* 
	File : core_portme.c
*/
/*
	Author : Shay Gal-On, EEMBC
	Legal : TODO!
*/ 

/* orpsoc driver includes */
#include "cpu-utils.h"
#include "board.h"
#include "uart.h"

#include "coremark.h"

#if VALIDATION_RUN
	volatile ee_s32 seed1_volatile=0x3415;
	volatile ee_s32 seed2_volatile=0x3415;
	volatile ee_s32 seed3_volatile=0x66;
#endif
#if PERFORMANCE_RUN
	volatile ee_s32 seed1_volatile=0x0;
	volatile ee_s32 seed2_volatile=0x0;
	volatile ee_s32 seed3_volatile=0x66;
#endif
#if PROFILE_RUN
	volatile ee_s32 seed1_volatile=0x8;
	volatile ee_s32 seed2_volatile=0x8;
	volatile ee_s32 seed3_volatile=0x8;
#endif
	volatile ee_s32 seed4_volatile=ITERATIONS;
	volatile ee_s32 seed5_volatile=0;
/* Porting : Timing functions
	How to capture time and convert to seconds must be ported to whatever is supported by the platform.
	e.g. Read value from on board RTC, read value from cpu clock cycles performance counter etc. 
	Sample implementation for standard time.h and windows.h definitions included.
*/
#define MYTIMEDIFF(fin,ini) ((fin)-(ini))
#define EE_TICKS_PER_SEC TICKS_PER_SEC

/** Define Host specific (POSIX), or target specific global time variables. */
static CORE_TICKS start_time_val, stop_time_val;

/* Function : start_time
	This function will be called right before starting the timed portion of the benchmark.

	Implementation may be capturing a system timer (as implemented in the example code) 
	or zeroing some system parameters - e.g. setting the cpu clocks cycles to 0.
*/
void start_time(void) {
  cpu_reset_timer_ticks();
  cpu_enable_timer();
  start_time_val = cpu_get_timer_ticks();
}
/* Function : stop_time
	This function will be called right after ending the timed portion of the benchmark.

	Implementation may be capturing a system timer (as implemented in the example code) 
	or other system parameters - e.g. reading the current value of cpu cycles counter.
*/
void stop_time(void) {
  stop_time_val = cpu_get_timer_ticks();
}
/* Function : get_time
	Return an abstract "ticks" number that signifies time on the system.
	
	Actual value returned may be cpu cycles, milliseconds or any other value,
	as long as it can be converted to seconds by <time_in_secs>.
	This methodology is taken to accomodate any hardware or simulated platform.
*/
CORE_TICKS get_time(void) {
	CORE_TICKS elapsed=(CORE_TICKS)(MYTIMEDIFF(stop_time_val, start_time_val));
	return elapsed;
}
/* Function : time_in_secs
	Convert the value returned by get_time to seconds.

	The <secs_ret> type is used to accomodate systems with no support for floating point.
	Default implementation implemented by the EE_TICKS_PER_SEC macro above.
*/
secs_ret time_in_secs(CORE_TICKS ticks) {
	secs_ret retval=((secs_ret)ticks) / (secs_ret)EE_TICKS_PER_SEC;
	return retval;
}

ee_u32 default_num_contexts=1;

/* Function : portable_malloc
        Portable malloc() function.
 */
void * portable_malloc(ee_size_t size)
{
  return NULL;
}

/* Function : portable_free
        Portable free() function.
 */
void portable_free(void *p)
{
  return;
}

/* Function : portable_init
	Target specific initialization code 
	Test for some common mistakes.
*/
void portable_init(core_portable *p, int *argc, char *argv[])
{
  uart_init(DEFAULT_UART);
	if (sizeof(ee_ptr_int) != sizeof(ee_u8 *)) {
		ee_printf("ERROR! Please define ee_ptr_int to a type that holds a pointer!\n");
	}
	if (sizeof(ee_u32) != 4) {
		ee_printf("ERROR! Please define ee_u32 to a 32b unsigned type!\n");
	}
	p->portable_id=1;
        ee_printf("Initialized Coremark for Digilent Atlys\n");
}
/* Function : portable_fini
	Target specific final code 
*/
void portable_fini(core_portable *p)
{
	p->portable_id=0;
        ee_printf("Finished Coremark for Digilent Atlys\n");
}
