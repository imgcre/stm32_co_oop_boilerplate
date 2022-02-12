#ifndef _APP_H_
#define _APP_H_

#include "s_task.h"
#include "object.h"
#include "task.h"
#include "print_task.h"

CLS_DEF(App, Task)
	PrintTask task1, task2;
	int stack[1024 / sizeof(int)];
END_CLS_DEF(App)

CTOR_ASYNC_EXPORT(App);

#define App_V_TABLE_BODY() \
	Task_V_TABLE_BODY();

CLS_EXPORTS(App, Object);

#endif
