/*
 * at_fsm_ok.c
 *
 *  Created on: Feb 13, 2022
 *      Author: Administrator
 */

#include "at/at_fsm_ok.h"
#include <stdio.h>

#define USE_BASE_CLS FsmSeq
#define USE_CLS_NAME AtFsmOk

CTOR_IMPL_X() {
	self->inited = false;
	BASE_CTOR_X("OK\r\n", self->next);
	self->inited = true;
	INST_MAKE(FsmLine, &self->fsmLine);
}

V_FUNC_OVERRIDE_X(next, void, char value) {
	if(INVOKE_X(isTerminated))
		return;

	if((INVOKE(FsmLine, &self->fsmLine, getPos) == 0 && value == '+') || value == ':'){
		printf("AT OK INVALID\n");
		self->invalid = true;
	}

	INVOKE(Fsm, &self->fsmLine, next, value);
	BASE_V_X(next, value);
	if(INVOKE(Fsm, &self->fsmLine, isTerminated)) {
		if(self->invalid || !BASE_V_X(isTerminated)) {
			INVOKE_X(reset);
		} else {
			printf("AT OK TERMINATED\n");
		}
	}
}

V_FUNC_OVERRIDE_X(reset, void) {
	printf("AT OK RESET\n");
	BASE_V_X(reset);
	self->invalid = false;

	if(self->inited) {
		INVOKE(Fsm, &self->fsmLine, reset);
	}
}

V_FUNC_OVERRIDE_X(isTerminated, bool) {
	return BASE_V_X(isTerminated) && !self->invalid;
}

V_TABLE_VAR_DEF_X = {0};

INIT_V_TABLE_X
	V_OVERRIDE_X(next);
	V_OVERRIDE_X(reset);
	V_OVERRIDE_X(isTerminated);
END_INIT_V_TABLE_X
