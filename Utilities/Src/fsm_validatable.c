/*
 * fsm_validatable.c
 *
 *  Created on: Feb 16, 2022
 *      Author: Administrator
 */

#include "fsm_validatable.h"
#define USE_BASE_CLS Fsm
#define USE_CLS_NAME FsmValidatable

CTOR_IMPL_X() {
	BASE_CTOR_X();
}

V_FUNC_IMPL_X(isValid, bool) {
	return true;
}

V_TABLE_VAR_DEF_X = {
	V_FUNC_REF_X(isValid),
};

INIT_V_TABLE_X

END_INIT_V_TABLE_X

