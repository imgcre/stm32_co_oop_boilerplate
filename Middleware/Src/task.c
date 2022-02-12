#include "task.h"
#include <stdio.h>

CTOR_ASYNC_IMPL(Task) {
	BASE_CTOR(Object, self);
	printf("try invoke task create, self: %p\n", self);
	
	printf("try get stack ptr, v: %p\n", V_FUNC_PTR(Task, self, getStackPtr));
	INVOKE(Task, self, getStackPtr);
	printf("stack ptr get done\n");
	
	s_task_create(
		INVOKE(Task, self, getStackPtr),
		INVOKE(Task, self, getStackSize),
		(s_task_fn_t)V_FUNC_PTR(Task, self, run),
		self
	);
}

V_FUNC_ASYNC_IMPL(Task, run, void) {
	
}

V_FUNC_IMPL(Task, getStackPtr, void *) {
	return 0; //NOT IMPLEMENTED
}

V_FUNC_IMPL(Task, getStackSize, size_t) {
	return 0; //NOT IMPLEMENTED
}

V_FUNC_ASYNC_IMPL(Task, join, void) {
	printf("joining %p\n", INVOKE(Task, self, getStackPtr));
	s_task_join(__await__, INVOKE(Task, self, getStackPtr));
}



V_TABLE_VAR_DEF(Task) = {
	V_FUNC_REF(Task, run),
	V_FUNC_REF(Task, getStackPtr),
	V_FUNC_REF(Task, getStackSize),
	V_FUNC_REF(Task, join),
};

INIT_V_TABLE(Task, Object)
	printf("vtable of TASK inited\n");
END_INIT_V_TABLE(Task)
