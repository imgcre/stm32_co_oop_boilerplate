/*
 * at_fsm_error.h
 *
 *  Created on: Feb 17, 2022
 *      Author: Administrator
 */

#ifndef INC_AT_AT_FSM_ERROR_H_
#define INC_AT_AT_FSM_ERROR_H_

#include <stdbool.h>
#include "fsm_extractly.h"
#include "fsm_line.h"
#include "at/at_fsm_resp_line.h"

#include "fsm.h"
#define USE_BASE_CLS Fsm
#define USE_CLS_NAME AtFsmError

CLS_DEF_X
	FsmExtractly fsmExtractlyError, fsmKeywordCmsError, fsmKeywordCmeError;
	AtFsmRespLine fsmCmsError, fsmCmeError;
 	FsmLine fsmLine;
	bool inited;
	bool terminated;
END_CLS_DEF_X

CTOR_EXPORT_X();

#define AtFsmError_V_TABLE_BODY() \
		Fsm_V_TABLE_BODY()

#include "end_cls_decl.h"

#endif /* INC_AT_AT_FSM_ERROR_H_ */
