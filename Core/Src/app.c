#include <stdio.h>
#include "app.h"
#include "print_task.h"

CTOR_ASYNC_IMPL(App) {
	BASE_ASYNC_CTOR(Task);
//	s_task_init_system();

}

V_FUNC_ASYNC_OVERRIDE(App, run, void) {
	INST_ASYNC_MAKE(PrintTask, &self->task1, 1000, "hello");
	INST_ASYNC_MAKE(PrintTask, &self->task2, 1500, "navi");
	while(1) {
		s_task_sleep(__await__, 5);
		printf("====STACK USAGE====\n");
		printf("app:\t%d%%\n", INVOKE(App, self, getStackUsage));
		printf("task1:\t%d%%\n", INVOKE(PrintTask, &self->task1, getStackUsage));
		printf("task2:\t%d%%\n", INVOKE(PrintTask, &self->task2, getStackUsage));
		printf("===================\n");
	}
}

V_FUNC_OVERRIDE(App, getStackPtr, void*) {
	return self->stack;
}


V_FUNC_OVERRIDE(App, getStackSize, size_t) {
	return sizeof(self->stack);
}

V_TABLE_VAR_DEF(App) = {0};

INIT_V_TABLE(App, Task)
	V_OVERRIDE(App, Task, run);
	V_OVERRIDE(App, Task, getStackPtr);
	V_OVERRIDE(App, Task, getStackSize);
END_INIT_V_TABLE(App)
