#ifndef _APP_H_
#define _APP_H_

#include "s_task.h"
#include "object.h"
#include "print_task.h"

CLS_DEF(App, Object)
	PrintTask task1, task2;
END_CLS_DEF(App)

CTOR_EXPORT(App);

#define App_V_TABLE_BODY() \
	Object_V_TABLE_BODY();

CLS_EXPORTS(App, Object);

#endif
