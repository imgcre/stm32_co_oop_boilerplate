#ifndef _OBJECT_H_
#define _OBJECT_H_
#include <string.h>
#include "object_async.h"

void object_abstract_stub();

#define A_SIZE(x) (sizeof(x) / sizeof(x[0]))

//usage: invoke(Client, client, getVal, 5)
#define V_FUNC_PTR(clazz, object, func) ((clazz##_VTable*)((Object*)object)->vTable)->func
#define INVOKE(clazz, object, func, ...)  V_FUNC_PTR(clazz, object, func)((void*)object, ##__VA_ARGS__)

#define INVOKE_X(func, ...) INVOKE(USE_CLS_NAME, self, func, ##__VA_ARGS__)

#define BASE_V(baseClazz, object, func, ...) ((V_TABLE_NAME(baseClazz)*)init_##baseClazz##_vtable())->func((void*)object, ##__VA_ARGS__)

#define _BASE_V_X(baseClazz, object, func, ...) BASE_V(baseClazz, object, func, ##__VA_ARGS__)
#define BASE_V_X(func, ...) _BASE_V_X(USE_BASE_CLS, self, func, ##__VA_ARGS__)

#define INST_MAKE(clazz, object, ...) \
	do { \
		BIND_V_TABLE(clazz, object); \
		clazz##_make(object, ##__VA_ARGS__); \
	}while(0)

#define INST_CREATE(clazz, name, ...) \
	clazz name; \
	INST_MAKE(clazz, &name, ##__VA_ARGS__);

#define BASE_CTOR(baseClazz, ...) baseClazz##_make((baseClazz*)self, ##__VA_ARGS__)

#define _BASE_CTOR_X(baseClazz, ...) BASE_CTOR(baseClazz, ##__VA_ARGS__)
#define BASE_CTOR_X(...) _BASE_CTOR_X(USE_BASE_CLS, ##__VA_ARGS__)

#define CTOR_IMPL(clazz, ...) \
	void clazz##_##make(clazz* self, ##__VA_ARGS__)

#define _CTOR_IMPL_X(clazz, ...) CTOR_IMPL(clazz, ##__VA_ARGS__)
#define CTOR_IMPL_X(...) _CTOR_IMPL_X(USE_CLS_NAME, ##__VA_ARGS__)
	
#define CTOR_EXPORT(clazz, ...) void clazz##_##make(clazz* self, ##__VA_ARGS__)

#define _CTOR_EXPORT_X(clazz, ...) CTOR_EXPORT(clazz, ##__VA_ARGS__)
#define CTOR_EXPORT_X(...) _CTOR_EXPORT_X(USE_CLS_NAME, ##__VA_ARGS__)

#define CLS_DEF(clazz, baseClazz) \
	typedef struct _##clazz { \
	baseClazz base;

#define CLS(clazz) struct _##clazz*
#define _CLS_X(clazz) CLS(clazz)
#define CLS_X _CLS_X(USE_CLS_NAME)

#define _CLS_DEF_X(clazz, baseClazz) CLS_DEF(clazz, baseClazz)
#define CLS_DEF_X _CLS_DEF_X(USE_CLS_NAME, USE_BASE_CLS)

#define END_CLS_DEF(clazz) \
	} clazz;

#define END_CLS_DEF_X END_CLS_DEF(USE_CLS_NAME)

#define CLS_EXPORTS(clazz, baseClazz) \
	V_TABLE_DEF(clazz, baseClazz); \
	EXPORT_INIT_V_TABLE(clazz); \
	EXPORT_V_TABLE_VAR(clazz);

#define CLS_EXPORTS_X CLS_EXPORTS(USE_CLS_NAME, USE_BASE_CLS)
	
#define V_TABLE_NAME(clazz) clazz##_VTable
	
#define V_TABLE_DEF(clazz, baseClazz) \
	typedef struct { \
		clazz##_V_TABLE_BODY() \
	} V_TABLE_NAME(clazz); 
	
#define V_TABLE_BODY_INHERIT(baseClazz) baseClazz##_V_TABLE_BODY()
	
#define V_TABLE_VAR_NAME(clazz) __##vtable_of_##clazz##__
#define V_TABLE_VAR_DEF(clazz) V_TABLE_NAME(clazz) V_TABLE_VAR_NAME(clazz)

#define V_TABLE_VAR_DEF_X V_TABLE_VAR_DEF(USE_CLS_NAME)

#define V_TABLE_MIXIN(baseClazz) baseClazz##_V_TABLE_BODY()

#define V_FUNC_DEF(clazz, name, r, ...) r (*name)(clazz* self, ##__VA_ARGS__)

#define V_FUNC_REF(clazz, name) .name = clazz##_##name

#define _V_FUNC_REF_X(clazz, name) V_FUNC_REF(clazz, name)
#define V_FUNC_REF_X(name) _V_FUNC_REF_X(USE_CLS_NAME, name)

#define V_FUNC_ABS_X(name) .name = (void*)object_abstract_stub

#define V_FUNC_IMPL(clazz, name, r, ...) static r clazz##_##name(clazz* self, ##__VA_ARGS__)

#define _V_FUNC_IMPL_X(clazz, name, r, ...) V_FUNC_IMPL(clazz, name, r, ##__VA_ARGS__)
#define V_FUNC_IMPL_X(name, r, ...) _V_FUNC_IMPL_X(USE_CLS_NAME, name, r, ##__VA_ARGS__)

#define V_FUNC_OVERRIDE(clazz, name, r, ...) static r clazz##_ovrd_##name(clazz* self, ##__VA_ARGS__)

#define _V_FUNC_OVERRIDE_X(clazz, name, r, ...) V_FUNC_OVERRIDE(clazz, name, r, ##__VA_ARGS__)
#define V_FUNC_OVERRIDE_X(name, r, ...) _V_FUNC_OVERRIDE_X(USE_CLS_NAME, name, r, ##__VA_ARGS__)

#define BIND_V_TABLE(clazz, object) \
	extern V_TABLE_NAME(clazz) V_TABLE_VAR_NAME(clazz); \
	((Object*)object)->vTable = &V_TABLE_VAR_NAME(clazz)

#define INIT_V_TABLE(clazz, baseClazz) \
void* init_##clazz##_vtable() { \
	static void* baseVTablePtr = 0; \
	if(!baseVTablePtr) { \
		baseVTablePtr = init_##baseClazz##_vtable(); \
		memcpy(&V_TABLE_VAR_NAME(clazz), baseVTablePtr, sizeof(V_TABLE_NAME(baseClazz)));

#define _INIT_V_TABLE_X(clazz, baseClazz) INIT_V_TABLE(clazz, baseClazz)
#define INIT_V_TABLE_X _INIT_V_TABLE_X(USE_CLS_NAME, USE_BASE_CLS)

#define V_OVERRIDE(clazz, baseClazz, func) ((baseClazz##_VTable *)&V_TABLE_VAR_NAME(clazz))->func = (void*)clazz##_ovrd_##func

#define _V_OVERRIDE_X(clazz, baseClazz, func) V_OVERRIDE(clazz, baseClazz, func)
#define V_OVERRIDE_X(func) _V_OVERRIDE_X(USE_CLS_NAME, USE_BASE_CLS, func)

#define END_INIT_V_TABLE(clazz) \
	} \
	return &V_TABLE_VAR_NAME(clazz); \
} \
static const V_INIT_FUNC f_##clazz __attribute__((used, section("vinit.1"))) = init_##clazz##_vtable;

#define _END_INIT_V_TABLE_X(clazz) END_INIT_V_TABLE(clazz)
#define END_INIT_V_TABLE_X _END_INIT_V_TABLE_X(USE_CLS_NAME)

#define EXPORT_INIT_V_TABLE(clazz) void* init_##clazz##_vtable(void)
#define EXPORT_V_TABLE_VAR(clazz) extern V_TABLE_NAME(clazz) V_TABLE_VAR_NAME(clazz)

#define __BASE_V_TABLE_BODY_X(baseClazz) baseClazz##_V_TABLE_BODY()
#define _BASE_V_TABLE_BODY_X(baseClazz) __BASE_V_TABLE_BODY_X(baseClazz)
#define BASE_V_TABLE_BODY_X() _BASE_V_TABLE_BODY_X(USE_BASE_CLS)

typedef struct {
	void *vTable;
} Object;

#define Object_V_TABLE_BODY() \
	void(*test)(); \
	const char*(*toString)();

typedef struct {
	Object_V_TABLE_BODY()
} Object_VTable;

CTOR_EXPORT(Object);
EXPORT_V_TABLE_VAR(Object);

typedef void*(*V_INIT_FUNC)(void);

void* init_Object_vtable(void);
void cls_init(void);

#endif

