/*
 * fsm_line.c
 *
 *  Created on: Feb 13, 2022
 *      Author: Administrator
 */

#include "fsm_line.h"
#include <stdio.h>

CTOR_IMPL(FsmLine) {
	BASE_CTOR(Fsm);
	//printf("ctor of FsmLine\n");
}

V_FUNC_IMPL(FsmLine, getPos, size_t) {
	return self->i;
}

//请在稍后调用基类的next回调
V_FUNC_OVERRIDE(FsmLine, next, void, char value) {
	switch(self->state) {
	case STATE_FSM_LINE_NORMAL:
		++self->i;
		if(value == '\r') {
			self->state = STATE_FSM_LINE_CR;
		}
		break;
	case STATE_FSM_LINE_CR:
		++self->i;
		if(value == '\n') {
			self->state = STATE_FSM_LINE_LF;
		} else {
			if(value == '\r') {
				self->state = STATE_FSM_LINE_CR;
			} else {
				self->state = STATE_FSM_LINE_NORMAL;
			}

		}
		break;
	case STATE_FSM_LINE_LF:
		break;
	}
}

V_FUNC_OVERRIDE(FsmLine, reset, void) {
	//printf("FsmLine reset\n");
	self->state = STATE_FSM_LINE_NORMAL;
	self->i = 0;
}

V_FUNC_OVERRIDE(FsmLine, isTerminated, bool) {
	return self->state == STATE_FSM_LINE_LF;
}

V_TABLE_VAR_DEF(FsmLine) = {
	V_FUNC_REF(FsmLine, getPos),
};

INIT_V_TABLE(FsmLine, Fsm)
	V_OVERRIDE(FsmLine, Fsm, next);
	V_OVERRIDE(FsmLine, Fsm, reset);
	V_OVERRIDE(FsmLine, Fsm, isTerminated);
END_INIT_V_TABLE(FsmLine)
