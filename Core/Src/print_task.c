#include "print_task.h"

CTOR_ASYNC_IMPL(PrintTask, int delay, const char* msg) {
	BASE_ASYNC_CTOR(Task);
	self->delay = delay;
	self->msg = msg;
	self->count = 0;
}

V_FUNC_ASYNC_OVERRIDE(PrintTask, run, void) {
	while(1) {
		printf("[%d]%s\n", self->count, self->msg);
		self->count++;
		s_task_msleep(__await__, self->delay);
	}
}

V_FUNC_OVERRIDE(PrintTask, getStackPtr, void*) {
	return self->stack;
}


V_FUNC_OVERRIDE(PrintTask, getStackSize, size_t) {
	return sizeof(self->stack);
}

V_TABLE_VAR_DEF(PrintTask) = {0};

INIT_V_TABLE(PrintTask, Task)
	V_OVERRIDE(PrintTask, Task, run);
	V_OVERRIDE(PrintTask, Task, getStackPtr);
	V_OVERRIDE(PrintTask, Task, getStackSize);
END_INIT_V_TABLE(PrintTask)
