/*
 * navi_urc_reg_item.c
 *
 *  Created on: Feb 21, 2022
 *      Author: Administrator
 */

#include <stdio.h>

#include "navi_urc_reg_item.h"
#define USE_BASE_CLS AtUrcRegItem
#define USE_CLS_NAME NaviUrcRegItem

CTOR_IMPL_X() {
	INST_MAKE(FsmExtractly, &self->fsmKeyword, "NAVI");
	INST_MAKE(FsmInt, &self->fsmParam0);
	self->params[0] = (RespLineParamItem){
		.idx = 0,
		.fsm = (FsmTerminable*)&self->fsmParam0,
	};
	INST_MAKE(AtFsmRespLine, &self->fsmRespLine, (FsmValidatable*)&self->fsmKeyword, self->params, A_SIZE(self->params));
	BASE_CTOR_X(&self->fsmRespLine);
}

V_FUNC_OVERRIDE_X(onMatch, void) {
	//printf("==NAVI MATCHED val: %d==\n", INVOKE(FsmInt, &self->fsmParam0, getValue));
}

V_TABLE_VAR_DEF_X = {0};

INIT_V_TABLE_X
	V_OVERRIDE_X(onMatch);
END_INIT_V_TABLE_X

