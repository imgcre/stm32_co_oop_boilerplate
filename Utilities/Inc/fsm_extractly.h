/*
 * fsm_extractly.h
 *
 *  Created on: Feb 16, 2022
 *      Author: Administrator
 */

#ifndef INC_FSM_EXTRACTLY_H_
#define INC_FSM_EXTRACTLY_H_

#include <stdbool.h>
#include "fsm_validatable.h"
#define USE_BASE_CLS FsmValidatable
#define USE_CLS_NAME FsmExtractly

CLS_DEF_X
	const char* str;
	int i;
	bool valid;
END_CLS_DEF_X

CTOR_EXPORT_X(const char* str);

#define FsmExtractly_V_TABLE_BODY() \
	FsmValidatable_V_TABLE_BODY()

#include "end_cls_decl.h"

#endif /* INC_FSM_EXTRACTLY_H_ */
