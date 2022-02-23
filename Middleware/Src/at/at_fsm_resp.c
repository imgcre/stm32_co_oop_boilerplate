/*
 * at_fsm_resp.c
 *
 *  Created on: Feb 17, 2022
 *      Author: Administrator
 */

#include "at/at_resp_iter_ter.h"
#include "at/at_fsm_resp.h"
#define USE_BASE_CLS Fsm
#define USE_CLS_NAME AtFsmResp

CTOR_IMPL_X(AtRespItem* items, size_t itemSize, Fsm** extraTerminators) {
	self->inited = false;
	BASE_CTOR_X();
	self->inited = true;
	self->respItems = items;
	self->respItemSize = itemSize;
	INST_MAKE(AtFsmOk, &self->fsmOk);
	INST_MAKE(AtFsmError, &self->fsmError);
	INST_MAKE(FsmLine, &self->fsmLine);
	self->defaultTerminators[0] = (Fsm*)&self->fsmOk;
	self->defaultTerminators[1] = (Fsm*)&self->fsmError;
	self->defaultTerminators[2] = NULL;
	self->terminators[0] = self->defaultTerminators;
	self->terminators[1] = extraTerminators;

}

V_FUNC_OVERRIDE_X(next, void, char value) {

	if(INVOKE_X(isTerminated)) return;

	INST_CREATE(AtRespIterTer, it, self->terminators, A_SIZE(self->terminators));
	Fsm* curTer = INVOKE(AtRespIterTer, &it, next);
	while(curTer != NULL) {
		//printf("INVOKE TER NEXT %d-%d\n", it.i, it.j);
		INVOKE(Fsm, curTer, next, value);
		curTer = INVOKE(AtRespIterTer, &it, next);
	}

	if(INVOKE_X(isTerminated)) return;
	if(self->respItems != NULL) {
		for(int i = 0; i < self->respItemSize; i++) {
			int curIdx = self->respItems[i].idx;
			if(!(curIdx == -1 || curIdx == self->curLine)) continue;
			INVOKE(Fsm, self->respItems[i].fsm, next, value);
		}
	}

	INVOKE(Fsm, &self->fsmLine, next, value);
	if(INVOKE(Fsm, &self->fsmLine, isTerminated)) {
		self->curLine++;
		INVOKE(Fsm, &self->fsmLine, reset);
		if(self->respItems != NULL) {
			for(int i = 0; i < self->respItemSize; i++) {
				if(!INVOKE(FsmValidatable, self->respItems[i].fsm, isValid)) {
					INVOKE(Fsm, self->respItems[i].fsm, reset);
				}
			}
		}
	}
}

V_FUNC_OVERRIDE_X(reset, void) {
	self->curLine = 0;
	if(!self->inited) return;
	INVOKE(Fsm, &self->fsmLine, reset);

	INST_CREATE(AtRespIterTer, it, self->terminators, A_SIZE(self->terminators));
	Fsm* curTer = INVOKE(AtRespIterTer, &it, next);
	while(curTer != NULL) {
		INVOKE(Fsm, curTer, reset);
		curTer = INVOKE(AtRespIterTer, &it, next);
	}
}

V_FUNC_OVERRIDE_X(isTerminated, bool) {
	INST_CREATE(AtRespIterTer, it, self->terminators, A_SIZE(self->terminators));
	Fsm* curTer = INVOKE(AtRespIterTer, &it, next);
	while(curTer != NULL) {
		if(INVOKE(Fsm, curTer, isTerminated)) {
			return true;
		}
		curTer = INVOKE(AtRespIterTer, &it, next);
	}
	return false;
}

V_TABLE_VAR_DEF_X = {0};

INIT_V_TABLE_X
	V_OVERRIDE_X(next);
	V_OVERRIDE_X(reset);
	V_OVERRIDE_X(isTerminated);
END_INIT_V_TABLE_X
