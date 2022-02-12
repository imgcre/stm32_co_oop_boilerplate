#ifndef _PRINT_TASK_H_
#define _PRINT_TASK_H_

#include "task.h"

CLS_DEF(PrintTask, Task)
	int delay;
	const char* msg;
	int stack[1024 / sizeof(int)];
	int count;
END_CLS_DEF(PrintTask)

CTOR_ASYNC_EXPORT(PrintTask, int delay, const char* msg);

#define PrintTask_V_TABLE_BODY() \
	Task_V_TABLE_BODY()

CLS_EXPORTS(PrintTask, Task);

#endif
