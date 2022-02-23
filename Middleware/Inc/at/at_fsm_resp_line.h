/*
 * at_fsm_resp_line.h
 *
 *  Created on: Feb 16, 2022
 *      Author: Administrator
 */

#ifndef INC_AT_AT_FSM_RESP_LINE_H_
#define INC_AT_AT_FSM_RESP_LINE_H_

#include "fsm_line.h"
#include "fsm_validatable.h"
#include "fsm_terminable.h"
#include <stdbool.h>
#include "fsm.h"
#define USE_BASE_CLS FsmValidatable
#define USE_CLS_NAME AtFsmRespLine

typedef struct {
	int idx;
	FsmTerminable* fsm;
} RespLineParamItem;

typedef enum {
	STATE_AT_FSM_RESP_LINE_HEADER,
	STATE_AT_FSM_RESP_LINE_KEYWORD,
	STATE_AT_FSM_RESP_LINE_PARAM_LEADING,
	STATE_AT_FSM_RESP_LINE_PARAM_BODY,
	STATE_AT_FSM_RESP_LINE_INVALID
} STATE_AT_FSM_RESP_LINE;

CLS_DEF_X
	FsmValidatable* fsmKeyword;
	STATE_AT_FSM_RESP_LINE state;
	FsmLine fsmLine;
	bool initing;
	int paramPos;
	char delimiter;
	bool leadingSpace;
	RespLineParamItem* items;
	int itemSize;
	FsmTerminable* currParamFsm;
END_CLS_DEF_X

CTOR_EXPORT_X(FsmValidatable* fsmKeyword, RespLineParamItem* items, int itemSize);

#define AtFsmRespLine_V_TABLE_BODY() \
	FsmValidatable_V_TABLE_BODY() \
	V_FUNC_DEF(AtFsmRespLine, updateCurrParamFsm, void);

#include "end_cls_decl.h"

#endif /* INC_AT_AT_FSM_RESP_LINE_H_ */
