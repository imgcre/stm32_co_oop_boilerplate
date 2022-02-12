#ifndef _OBJECT_H_
#define _OBJECT_H_
#include <string.h>
#include "object_async.h"

//usage: invoke(Client, client, getVal, 5)
#define V_FUNC_PTR(clazz, object, func) ((clazz##_VTable*)((Object*)object)->vTable)->func
#define INVOKE(clazz, object, func, ...)  V_FUNC_PTR(clazz, object, func)((clazz*)object, ##__VA_ARGS__)

#define BASE_V(baseClazz, object, func, ...) ((V_TABLE_NAME(baseClazz)*)init_##baseClazz##_vtable())->func(object, ##__VA_ARGS__)

#define INST_MAKE(clazz, object, ...) \
	do { \
		BIND_V_TABLE(clazz, object); \
		clazz##_make(object, ##__VA_ARGS__); \
	}while(0)

#define BASE_CTOR(baseClazz, object, ...) baseClazz##_make((baseClazz*)object, ##__VA_ARGS__)

#define CTOR_IMPL(clazz, ...) \
	void clazz##_##make(clazz* self, ##__VA_ARGS__)
	
#define CTOR_EXPORT(clazz, ...) void clazz##_##make(clazz* self, ##__VA_ARGS__)

#define CLS_DEF(clazz, baseClazz) \
	typedef struct { \
	baseClazz *	base;

#define END_CLS_DEF(clazz) \
	} clazz;

#define CLS_EXPORTS(clazz, baseClazz) \
	V_TABLE_DEF(clazz, baseClazz); \
	EXPORT_INIT_V_TABLE(clazz); \
	EXPORT_V_TABLE_VAR(clazz);
	
#define V_TABLE_NAME(clazz) clazz##_VTable
	
#define V_TABLE_DEF(clazz, baseClazz) \
	typedef struct { \
		clazz##_V_TABLE_BODY() \
	} V_TABLE_NAME(clazz); 
	
#define V_TABLE_BODY_INHERIT(baseClazz) baseClazz##_V_TABLE_BODY()
	
#define V_TABLE_VAR_NAME(clazz) __##vtable_of_##clazz##__
#define V_TABLE_VAR_DEF(clazz) V_TABLE_NAME(clazz) V_TABLE_VAR_NAME(clazz)
#define V_TABLE_MIXIN(baseClazz) baseClazz##_V_TABLE_BODY()

#define V_FUNC_DEF(clazz, name, r, ...) r (*name)(clazz* self, ##__VA_ARGS__)
#define V_FUNC_REF(clazz, name) .name = clazz##_##name
#define V_FUNC_IMPL(clazz, name, r, ...) static r clazz##_##name(clazz* self, ##__VA_ARGS__)
#define V_FUNC_OVERRIDE(clazz, name, r, ...) static r clazz##_ovrd_##name(clazz* self, ##__VA_ARGS__)

#define BIND_V_TABLE(clazz, object) \
	extern V_TABLE_NAME(clazz) V_TABLE_VAR_NAME(clazz); \
	((Object*)object)->vTable = &V_TABLE_VAR_NAME(clazz)

#define INIT_V_TABLE(clazz, baseClazz) \
void* init_##clazz##_vtable() { \
	static void* baseVTablePtr = 0; \
	if(!baseVTablePtr) { \
		baseVTablePtr = init_##baseClazz##_vtable(); \
		memcpy(&V_TABLE_VAR_NAME(clazz), baseVTablePtr, sizeof(V_TABLE_NAME(baseClazz)));

#define V_OVERRIDE(clazz, baseClazz, func) ((baseClazz##_VTable *)&V_TABLE_VAR_NAME(clazz))->func = (void*)clazz##_ovrd_##func
	
#define END_INIT_V_TABLE(clazz) \
	} \
	return &V_TABLE_VAR_NAME(clazz); \
} \
static const V_INIT_FUNC f_##clazz __attribute__((used, section("vinit.1"))) = init_##clazz##_vtable;


#define EXPORT_INIT_V_TABLE(clazz) void* init_##clazz##_vtable(void)
#define EXPORT_V_TABLE_VAR(clazz) extern V_TABLE_NAME(clazz) V_TABLE_VAR_NAME(clazz)

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

