/*
 * fsm_validatable.h
 *
 *  Created on: Feb 16, 2022
 *      Author: Administrator
 */

#ifndef INC_FSM_VALIDATABLE_H_
#define INC_FSM_VALIDATABLE_H_

#include "fsm.h"
#include <stdbool.h>
#define USE_BASE_CLS Fsm
#define USE_CLS_NAME FsmValidatable

CLS_DEF_X

END_CLS_DEF_X

CTOR_EXPORT_X();

#define FsmValidatable_V_TABLE_BODY() \
	Fsm_V_TABLE_BODY() \
	V_FUNC_DEF(FsmValidatable, isValid, bool);

#include "end_cls_decl.h"

#endif /* INC_FSM_VALIDATABLE_H_ */
