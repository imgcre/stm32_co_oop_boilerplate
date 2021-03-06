#ifndef INC_S_PORT_H_
#define INC_S_PORT_H_

#include <Windows.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif


/* Copyright xhawk, MIT license */

/* Timer functions need to be implemented on a new porting. */

/* === Timer functions on windows === */

/* 1. define a type for clock */
typedef DWORD my_clock_t;
typedef LONG  my_clock_diff_t;

/* 2. define the clock ticks count for one second */
#define MY_CLOCKS_PER_SEC 1000

/* 3. Implement the initilization function for clock. Leave it blank if not required. */
void my_clock_init(void);

/* 4. Implement the function of getting current clock ticks. */
my_clock_t my_clock(void);

/* 5. Implement the idle delay function. */
void my_on_idle(uint64_t max_idle_ms);


#ifdef __cplusplus
}
#endif
#endif

