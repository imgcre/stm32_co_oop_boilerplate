/*
 * runar_urc_reg_item.c
 *
 *  Created on: 2022年2月21日
 *      Author: Administrator
 */

#include "runar_urc_reg_item.h"
#define USE_BASE_CLS AtUrcRegItem
#define USE_CLS_NAME RunarUrcRegItem

CTOR_IMPL_X() {
	INST_MAKE(FsmExtractly, &self->fsmKeyword, "RUNAR");
	INST_MAKE(FsmInt, &self->fsmParam0);
	self->params[0] = (RespLineParamItem){
		.idx = 0,
		.fsm = (FsmTerminable*)&self->fsmParam0,
	};
	INST_MAKE(AtFsmRespLine, &self->fsmRespLine, (FsmValidatable*)&self->fsmKeyword, self->params, A_SIZE(self->params));
	BASE_CTOR_X(&self->fsmRespLine);
}

V_FUNC_OVERRIDE_X(onMatch, void) {
	//printf("==RUNAR MATCHED val: %d==\n", INVOKE(FsmInt, &self->fsmParam0, getValue));
}

V_TABLE_VAR_DEF_X = {0};

INIT_V_TABLE_X
	V_OVERRIDE_X(onMatch);
END_INIT_V_TABLE_X


