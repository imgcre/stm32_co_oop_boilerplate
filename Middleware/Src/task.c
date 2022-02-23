#include "task.h"
#include <stdio.h>
#include "s_task_internal.h"

#define STACK_MAGIC_CODE 0xc1c2c3c4

CTOR_ASYNC_IMPL(Task) {
	BASE_CTOR(Object);
	//printf("try invoke task create, self: %p\n", self);
	
//	printf("try get stack ptr, v: %p\n", V_FUNC_PTR(Task, self, getStackPtr));
	
	uint32_t* bottom = (uint32_t*)INVOKE(Task, self, getStackPtr);
	size_t size = INVOKE(Task, self, getStackSize);
//
//	for(int i = sizeof(s_task_t) / 4; i < size / 4; i++) {
//		bottom[i] = STACK_MAGIC_CODE;
//	}

	s_task_create(
		(void*)bottom,
		size,
		(s_task_fn_t)V_FUNC_PTR(Task, self, run),
		self
	);
}

V_FUNC_ASYNC_IMPL(Task, run, void) {
	
}

V_FUNC_IMPL(Task, getStackUsage, size_t) {
//	uint32_t* bottom = (uint32_t*)INVOKE(Task, self, getStackPtr) + sizeof(s_task_t) / 4;
//	size_t size = INVOKE(Task, self, getStackSize) - sizeof(s_task_t);
//	size /= 4;
//
//	int i;
//	for(i = 0; i < size; i++) {
//		if(bottom[i] != STACK_MAGIC_CODE) {
//			break;
//		}
//	}
//
//	return 100 - 100 * i / size;
	return 0;
}

V_FUNC_ASYNC_IMPL(Task, join, void) {
	//printf("joining %p\n", INVOKE(Task, self, getStackPtr));
	s_task_join(__await__, INVOKE(Task, self, getStackPtr));
}



V_TABLE_VAR_DEF(Task) = {
	V_FUNC_REF(Task, run),
	V_FUNC_ABS_X(getStackPtr),
	V_FUNC_ABS_X(getStackSize),
	V_FUNC_REF(Task, getStackUsage),
	V_FUNC_REF(Task, join),
};

INIT_V_TABLE(Task, Object)
	//printf("vtable of TASK inited\n");
END_INIT_V_TABLE(Task)
