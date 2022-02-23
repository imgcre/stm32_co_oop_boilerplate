/*
 * at_fsm_ok.h
 *
 *  Created on: Feb 13, 2022
 *      Author: Administrator
 */

#ifndef _AT_FSM_OK_H_
#define _AT_FSM_OK_H_

#include "fsm_line.h"
#include <stdbool.h>
#include "fsm_seq.h"

#define USE_BASE_CLS FsmSeq
#define USE_CLS_NAME AtFsmOk

CLS_DEF_X
	bool invalid;
	bool inited;
	int16_t next[5];
	FsmLine fsmLine;
END_CLS_DEF_X

CTOR_EXPORT_X();

#define AtFsmOk_V_TABLE_BODY() \
	FsmSeq_V_TABLE_BODY()

#include "end_cls_decl.h"

#endif /* INC_AT_AT_FSM_OK_H_ */
