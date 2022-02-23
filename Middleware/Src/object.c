#include "object.h"
#include <stdio.h>

static const V_INIT_FUNC f_begin __attribute__((used)) __attribute__((section("vinit.0"))) = init_Object_vtable;
static const V_INIT_FUNC f_end __attribute__((used)) __attribute__((section("vinit.1.end"))) = 0;

CTOR_IMPL(Object) {
	//printf("object ctor called\n");
}

V_FUNC_IMPL(Object, test, void) {
	//printf("test name: %s\n", INVOKE(Object, self, toString));
}

V_FUNC_IMPL(Object, toString, const char*) {
	return "object";
}

V_TABLE_VAR_DEF(Object) = {
	V_FUNC_REF(Object, test),
	V_FUNC_REF(Object, toString),
};

void* init_Object_vtable() {
	return &V_TABLE_VAR_NAME(Object);
}

void cls_init() {
	V_INIT_FUNC* f;
	for(f = (V_INIT_FUNC*)&f_begin; f != &f_end; f++) {
		//printf("addr: %p\n", f);
		(*f)();
	}
}

void object_abstract_stub() {
	printf("WARN abstract func called\n");
	while(1){}
}
