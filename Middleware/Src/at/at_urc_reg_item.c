/*
 * at_urc_reg_item.c
 *
 *  Created on: Feb 19, 2022
 *      Author: Administrator
 */

#include "at/at_urc_reg_item.h"
#define USE_BASE_CLS Object
#define USE_CLS_NAME AtUrcRegItem

CTOR_IMPL_X(AtFsmRespLine* fsm) {
	self->next = NULL;
	self->fsm = fsm;
}

V_TABLE_VAR_DEF_X = {
	V_FUNC_ABS_X(onMatch),
};

INIT_V_TABLE_X

END_INIT_V_TABLE_X
