/*
 * fsm_terminable.c
 *
 *  Created on: Feb 15, 2022
 *      Author: Administrator
 */

#include "fsm_terminable.h"
#define USE_BASE_CLS Fsm
#define USE_CLS_NAME FsmTerminable

CTOR_IMPL_X() {
	BASE_CTOR_X();
}

V_FUNC_IMPL_X(terminate, void) {

}

V_TABLE_VAR_DEF_X = {
	V_FUNC_REF_X(terminate),
};

INIT_V_TABLE_X

END_INIT_V_TABLE_X
