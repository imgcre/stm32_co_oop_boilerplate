#include <stdio.h>
#include "app.h"
#include "print_task.h"

CTOR_IMPL(App) {
	s_task_init_system();
	INST_ASYNC_MAKE(PrintTask, &self->task1, 1000, "hello");
	INST_ASYNC_MAKE(PrintTask, &self->task2, 1500, "navi");
	INVOKE_ASYNC(Task, &self->task1, join);
	INVOKE_ASYNC(Task, &self->task2, join);
}

V_TABLE_VAR_DEF(App) = {

};
