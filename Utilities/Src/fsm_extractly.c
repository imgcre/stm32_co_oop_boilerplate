/*
 * fsm_extractly.c
 *
 *  Created on: Feb 16, 2022
 *      Author: Administrator
 */

#include "fsm_extractly.h"
#define USE_BASE_CLS FsmValidatable
#define USE_CLS_NAME FsmExtractly

CTOR_IMPL_X(const char* str) {
	BASE_CTOR_X();
	self->str = str;
}

V_FUNC_OVERRIDE_X(isValid, bool) {
	return self->valid;
}

V_FUNC_OVERRIDE_X(next, void, char value) {
	if(!self->valid || INVOKE_X(isTerminated)) return;

	if(self->str[self->i] != value) {
		self->valid = false;
		return;
	}
	self->i++;
}

V_FUNC_OVERRIDE_X(reset, void) {
	self->i = 0;
	self->valid = true;
}

V_FUNC_OVERRIDE_X(isTerminated, bool) {
	return self->str[self->i] == '\0';
}

V_TABLE_VAR_DEF_X = {0};

INIT_V_TABLE_X
	V_OVERRIDE_X(isValid);
	V_OVERRIDE_X(next);
	V_OVERRIDE_X(reset);
	V_OVERRIDE_X(isTerminated);
END_INIT_V_TABLE_X
