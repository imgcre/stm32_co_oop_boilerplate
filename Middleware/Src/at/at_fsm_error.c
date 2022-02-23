/*
 * at_fsm_error.c
 *
 *  Created on: Feb 17, 2022
 *      Author: Administrator
 */

#include <stdio.h>
#include "at/at_fsm_error.h"
#define USE_BASE_CLS Fsm
#define USE_CLS_NAME AtFsmError

CTOR_IMPL_X() {
	self->inited = false;
	BASE_CTOR_X();
	self->inited = true;
	INST_MAKE(FsmExtractly, &self->fsmExtractlyError, "ERROR\r\n");
	INST_MAKE(FsmExtractly, &self->fsmKeywordCmsError, "CMS ERROR");
	INST_MAKE(FsmExtractly, &self->fsmKeywordCmeError, "CME ERROR");
	INST_MAKE(AtFsmRespLine, &self->fsmCmsError, (FsmValidatable*)&self->fsmKeywordCmsError, NULL, 0);
	INST_MAKE(AtFsmRespLine, &self->fsmCmeError, (FsmValidatable*)&self->fsmKeywordCmeError, NULL, 0);
	INST_MAKE(FsmLine, &self->fsmLine);
}

V_FUNC_OVERRIDE_X(next, void, char value) {
	if(self->terminated) return;
	//printf("AT ERROR RECV: %d\n", value);
	INVOKE(Fsm, &self->fsmExtractlyError, next, value);
	INVOKE(Fsm, &self->fsmCmsError, next, value);
	INVOKE(Fsm, &self->fsmCmeError, next, value);
	INVOKE(Fsm, &self->fsmLine, next, value);
	if(INVOKE(Fsm, &self->fsmLine, isTerminated)) {
		if(INVOKE(Fsm, &self->fsmExtractlyError, isTerminated)
		  || INVOKE(FsmValidatable, &self->fsmCmsError, isValid)
		  || INVOKE(FsmValidatable, &self->fsmCmeError, isValid)) {
			self->terminated = true;
			printf("AT ERROR TERMINATED\n");
			return;
		}
		INVOKE_X(reset);
	}
}

V_FUNC_OVERRIDE_X(reset, void) {
	self->terminated = false;
	if(self->inited) {
		INVOKE(Fsm, &self->fsmExtractlyError, reset);
		INVOKE(Fsm, &self->fsmLine, reset);
		INVOKE(Fsm, &self->fsmCmsError, reset);
		INVOKE(Fsm, &self->fsmCmeError, reset);
	}
}

V_FUNC_OVERRIDE_X(isTerminated, bool) {
	return self->terminated;
}

V_TABLE_VAR_DEF_X = {0};

INIT_V_TABLE_X
	V_OVERRIDE_X(next);
	V_OVERRIDE_X(reset);
	V_OVERRIDE_X(isTerminated);
END_INIT_V_TABLE_X
