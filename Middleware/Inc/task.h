#ifndef _TASK_H_
#define _TASK_H_

#include "s_task.h"
#include "object.h"

CLS_DEF(Task, Object)

END_CLS_DEF(Task)

#define Task_V_TABLE_BODY() \
	Object_V_TABLE_BODY() \
	V_FUNC_ASYNC_DEF(Task, run, void); \
	V_FUNC_DEF(Task, getStackPtr, void*); \
	V_FUNC_DEF(Task, getStackSize, size_t); \
	V_FUNC_ASYNC_DEF(Task, join, void);

CTOR_ASYNC_EXPORT(Task);
CLS_EXPORTS(Task, Object);

#endif
