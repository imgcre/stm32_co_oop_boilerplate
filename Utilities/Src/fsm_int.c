/*
 * fsm_int.c
 *
 *  Created on: Feb 15, 2022
 *      Author: Administrator
 */
#include <stdio.h>
#include "fsm_int.h"
#define USE_BASE_CLS FsmTerminable
#define USE_CLS_NAME FsmInt

CTOR_IMPL_X() {
	BASE_CTOR_X();
}

V_FUNC_IMPL_X(getValue, int) {
	return self->val * self->factor;
}

V_FUNC_IMPL_X(isInt, bool) {
	return self->fed && self->valid;
}

V_FUNC_OVERRIDE_X(next, void, char value) {
	//printf("FsmInt got %c, ter: %d, valid: %d\n", value, self->terminated, self->valid);
	if(self->terminated || !self->valid) return;

	bool prevFed = self->fed;
	self->fed = true;

	if(value == '-') {
		if(prevFed) {
			self->valid = false;
			return;
		}
		self->factor *= -1;
		return;
	}

	if(!('0' <= value && value <= '9')) {
		self->valid = false;
		return;
	}
	self->val *= 10;
	self->val += value - '0';
}

V_FUNC_OVERRIDE_X(reset, void) {
	self->valid = true;
	self->factor = 1;
	self->fed = false;
	self->val = 0;
	self->terminated = false;
}

V_FUNC_OVERRIDE_X(terminate, void) {
	self->terminated = true;
}

V_FUNC_OVERRIDE_X(isTerminated, bool) {
	return self->terminated;
}

V_TABLE_VAR_DEF_X = {
	V_FUNC_REF_X(getValue),
	V_FUNC_REF_X(isInt),
};

INIT_V_TABLE_X
	V_OVERRIDE_X(next);
	V_OVERRIDE_X(reset);
	V_OVERRIDE_X(terminate);
	V_OVERRIDE_X(isTerminated);
END_INIT_V_TABLE_X
