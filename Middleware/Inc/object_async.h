#ifndef _OBJECT_ASYNC_
#define _OBJECT_ASYNC_
#include "s_task.h"

/*
#define INST_AS_TASK(clazz, object, stack) do { \
		BIND_V_TABLE(clazz, object); \
		s_task_create(stack, sizeof(stack), clazz##_async_make, object); \
	} while(0)
*/

#define INST_ASYNC_MAKE(clazz, object, ...) \
	do { \
		BIND_V_TABLE(clazz, object); \
		clazz##_async_make(__await__, object, ##__VA_ARGS__); \
	}while(0)
		
#define CTOR_ASYNC_IMPL(clazz, ...) \
	void clazz##_async_make(__async__, clazz* self, ##__VA_ARGS__)

#define _CTOR_ASYNC_IMPL_X(clazz, ...) CTOR_ASYNC_IMPL(clazz, ##__VA_ARGS__)
#define CTOR_ASYNC_IMPL_X(...) _CTOR_ASYNC_IMPL_X(USE_CLS_NAME, ##__VA_ARGS__)
		
#define CTOR_ASYNC_EXPORT(clazz, ...) void clazz##_async_make(__async__, clazz* self, ##__VA_ARGS__)
#define _CTOR_ASYNC_EXPORT_X(clazz, ...) CTOR_ASYNC_EXPORT(clazz, ##__VA_ARGS__)
#define CTOR_ASYNC_EXPORT_X(...) _CTOR_ASYNC_EXPORT_X(USE_CLS_NAME, ##__VA_ARGS__)

#define BASE_ASYNC_CTOR(baseClazz, ...) baseClazz##_async_make(__await__, (baseClazz*)self, ##__VA_ARGS__)
#define INVOKE_ASYNC(clazz, object, func, ...)  ((clazz##_VTable*)((Object*)object)->vTable)->func(__await__, (void*)object, ##__VA_ARGS__)

#define V_FUNC_ASYNC_IMPL(clazz, name, r, ...) static r clazz##_##name(__async__, clazz* self, ##__VA_ARGS__)
#define _V_FUNC_ASYNC_IMPL_X(clazz, name, r, ...) V_FUNC_ASYNC_IMPL(clazz, name, r, ##__VA_ARGS__)
#define V_FUNC_ASYNC_IMPL_X(name, r, ...) _V_FUNC_ASYNC_IMPL_X(USE_CLS_NAME, name, r, ##__VA_ARGS__)

#define V_FUNC_ASYNC_OVERRIDE(clazz, name, r, ...) static r clazz##_ovrd_##name(__async__, clazz* self, ##__VA_ARGS__)
#define _V_FUNC_ASYNC_OVERRIDE_X(clazz, name, r, ...) V_FUNC_ASYNC_OVERRIDE(clazz, name, r, ##__VA_ARGS__)
#define V_FUNC_ASYNC_OVERRIDE_X(name, r, ...) _V_FUNC_ASYNC_OVERRIDE_X(USE_CLS_NAME, name, r, ##__VA_ARGS__)

#define V_FUNC_ASYNC_DEF(clazz, name, r, ...) r (*name)(__async__, clazz* self, ##__VA_ARGS__)

#endif
