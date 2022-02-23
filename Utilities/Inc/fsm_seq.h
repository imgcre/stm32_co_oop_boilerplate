/*
 * fsm_seq.h
 *
 *  Created on: Feb 14, 2022
 *      Author: Administrator
 */

#ifndef INC_FSM_SEQ_H_
#define INC_FSM_SEQ_H_

#include "fsm.h"
#define USE_BASE_CLS Fsm
#define USE_CLS_NAME FsmSeq

CLS_DEF_X
	const char* pattern;
	int16_t* next;
	int j;
END_CLS_DEF_X

CTOR_EXPORT_X(const char* pattern, int16_t* next);

#define FsmSeq_V_TABLE_BODY() \
	Fsm_V_TABLE_BODY() \
	V_FUNC_DEF(FsmSeq, genNext, void);

#include "end_cls_decl.h"

#endif /* INC_FSM_SEQ_H_ */
