/*
 * at_fsm_resp.h
 *
 *  Created on: Feb 17, 2022
 *      Author: Administrator
 */

#ifndef INC_AT_AT_FSM_RESP_H_
#define INC_AT_AT_FSM_RESP_H_

#include <stdbool.h>
#include "at/at_fsm_ok.h"
#include "at/at_fsm_error.h"
#include "fsm_line.h"
#include "fsm.h"
#define USE_BASE_CLS Fsm
#define USE_CLS_NAME AtFsmResp

typedef struct {
	int idx; //如果idx是-1, 则作用在所有行, 行号从0开始
	FsmValidatable* fsm;
} AtRespItem;

CLS_DEF_X
	Fsm** terminators[2];
	AtFsmOk fsmOk;
	AtFsmError fsmError;
	Fsm* defaultTerminators[3];
	bool inited;
	FsmLine fsmLine;
	int curLine;
	AtRespItem* respItems;
	size_t respItemSize;
END_CLS_DEF_X

CTOR_EXPORT_X(AtRespItem* items, size_t itemSize, Fsm** extraTerminators);

#define AtFsmResp_V_TABLE_BODY() \
	Fsm_V_TABLE_BODY() \

#include "end_cls_decl.h"

#endif /* INC_AT_AT_FSM_RESP_H_ */
