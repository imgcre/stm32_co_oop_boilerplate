/*
 * fsm_line.h
 *
 *  Created on: Feb 13, 2022
 *      Author: Administrator
 */

#ifndef INC_FSM_LINE_H_
#define INC_FSM_LINE_H_

#include "fsm.h"

typedef enum {
	STATE_FSM_LINE_NORMAL,
	STATE_FSM_LINE_CR,
	STATE_FSM_LINE_LF,
} STATE_FSM_LINE;

CLS_DEF(FsmLine, Fsm)
	int i;
	STATE_FSM_LINE state;
END_CLS_DEF(FsmLine)

CTOR_EXPORT(FsmLine);

#define FsmLine_V_TABLE_BODY() \
	Fsm_V_TABLE_BODY() \
	V_FUNC_DEF(FsmLine, getPos, size_t);

CLS_EXPORTS(FsmLine, Fsm);

#endif /* INC_FSM_LINE_H_ */
