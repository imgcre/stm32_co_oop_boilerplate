/*
 * fsm.c
 *
 *  Created on: Feb 13, 2022
 *      Author: Administrator
 */

#include <stdio.h>

#include "fsm.h"
#define USE_BASE_CLS Object
#define USE_CLS_NAME Fsm

CTOR_IMPL_X() {
	//printf("ctor of Fsm\n");
	INVOKE_X(reset);
}

V_TABLE_VAR_DEF_X = {
	V_FUNC_ABS_X(next),
	V_FUNC_ABS_X(reset),
	V_FUNC_ABS_X(isTerminated),
};

INIT_V_TABLE_X

END_INIT_V_TABLE_X
