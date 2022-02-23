/*
 * at_fsm_resp_line.c
 *
 *  Created on: Feb 16, 2022
 *      Author: Administrator
 */
#include <stdio.h>
#include "at/at_fsm_resp_line.h"
#define USE_BASE_CLS FsmValidatable
#define USE_CLS_NAME AtFsmRespLine

CTOR_IMPL_X(FsmValidatable* fsmKeyword, RespLineParamItem* items, int itemSize) {
	self->initing = true;
	BASE_CTOR_X();
	self->initing = false;
	INST_MAKE(FsmLine, &self->fsmLine);
	self->fsmKeyword = fsmKeyword;
	self->items = items;
	self->itemSize = itemSize;
}

V_FUNC_IMPL_X(updateCurrParamFsm, void) {
	self->currParamFsm = NULL;
	if(self->items == NULL) return;
	for(int i = 0; i < self->itemSize; i++) {
		if(self->items[i].idx == self->paramPos) {
			//printf("RL param fsm found\n");
			self->currParamFsm = self->items[i].fsm;
		}
	}
}

V_FUNC_OVERRIDE_X(isValid, bool) {
	return self->state != STATE_AT_FSM_RESP_LINE_INVALID;
}

V_FUNC_OVERRIDE_X(next, void, char value) {
	if(INVOKE(Fsm, &self->fsmLine, isTerminated)) {
		return;
	}

	switch(self->state) {
	case STATE_AT_FSM_RESP_LINE_HEADER:
		if(value != '+') {
			//printf("RL state -> invalid\n");
			self->state = STATE_AT_FSM_RESP_LINE_INVALID;
		} else {
			//printf("RL state -> keyword\n");
			self->state = STATE_AT_FSM_RESP_LINE_KEYWORD;
		}
		break;
	case STATE_AT_FSM_RESP_LINE_KEYWORD:
		INVOKE(Fsm, self->fsmKeyword, next, value);
		if(!INVOKE(FsmValidatable, self->fsmKeyword, isValid)) {
			//printf("RL state -> invalid\n");
			self->state = STATE_AT_FSM_RESP_LINE_INVALID;
		} else {
			if(INVOKE(Fsm, self->fsmKeyword, isTerminated)) {
				//printf("RL state -> param leading\n");
				self->state = STATE_AT_FSM_RESP_LINE_PARAM_LEADING;
				//TODO: 可能没参数，后面就是空格、\r
			}
		}
		break;
	case STATE_AT_FSM_RESP_LINE_PARAM_LEADING: {
		char leading_char = self->paramPos == 0 ? ':' : ',';
		if(value == leading_char) {
			//printf("RL state -> param body [0]\n");
			self->state = STATE_AT_FSM_RESP_LINE_PARAM_BODY;
			self->leadingSpace = true;
			INVOKE_X(updateCurrParamFsm);
		} else if(value != ' ') {
			//printf("RL state -> invalid\n");
			self->state = STATE_AT_FSM_RESP_LINE_INVALID;
		}
		break;
	}
	case STATE_AT_FSM_RESP_LINE_PARAM_BODY:
		if(self->delimiter == '\0') {
			if(value == ' ' && self->leadingSpace) {
				//printf("RL param meet leading space\n");
				break;
			}
			self->leadingSpace = false;
			if(value == '"') {
				self->delimiter = '"';
				break;
			}
			if(value == ',') {
				self->state = STATE_AT_FSM_RESP_LINE_PARAM_BODY;
				self->leadingSpace = true;
				self->paramPos++;
				//printf("RL state -> param body [%d]\n", self->paramPos);
				if(self->currParamFsm != NULL)
					INVOKE(FsmTerminable, self->currParamFsm, terminate);
				INVOKE_X(updateCurrParamFsm);
				break;
			}
			if(value == '\r' || value == '\n') {
				break;
			}
			if(self->currParamFsm != NULL) {
				//printf("RL param fsm update\n");
				INVOKE(Fsm, self->currParamFsm, next, value);
			}


		} else if(self->delimiter == value) {
			self->delimiter = '\0';
		} else {
			if(self->currParamFsm != NULL) {
				//printf("RL param fsm update\n");
				INVOKE(Fsm, self->currParamFsm, next, value);
			}
		}

		break;
	default:
		break;
	}
	INVOKE(Fsm, &self->fsmLine, next, value);
	if(INVOKE(Fsm, &self->fsmLine, isTerminated) && self->currParamFsm != NULL)
		INVOKE(FsmTerminable, self->currParamFsm, terminate);
}

V_FUNC_OVERRIDE_X(reset, void) {
	//printf("RL state -> header\n");
	self->state = STATE_AT_FSM_RESP_LINE_HEADER;
	self->paramPos = 0;
	self->delimiter = '\0';
	self->currParamFsm = NULL;
	if(!self->initing) {
		INVOKE(Fsm, &self->fsmLine, reset);
		INVOKE(Fsm, self->fsmKeyword, reset);
	}
}

V_FUNC_OVERRIDE_X(isTerminated, bool) {
	return INVOKE(Fsm, &self->fsmLine, isTerminated);
}

V_TABLE_VAR_DEF_X = {
	V_FUNC_REF_X(updateCurrParamFsm),
};

INIT_V_TABLE_X
	V_OVERRIDE_X(isValid);
	V_OVERRIDE_X(next);
	V_OVERRIDE_X(reset);
	V_OVERRIDE_X(isTerminated);
END_INIT_V_TABLE_X
