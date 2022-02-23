/*
 * fsm_terminable.h
 *
 *  Created on: Feb 15, 2022
 *      Author: Administrator
 */

#ifndef INC_FSM_TERMINABLE_H_
#define INC_FSM_TERMINABLE_H_

#include "fsm.h"
#define USE_BASE_CLS Fsm
#define USE_CLS_NAME FsmTerminable

CLS_DEF_X

END_CLS_DEF_X

CTOR_EXPORT_X();

#define FsmTerminable_V_TABLE_BODY() \
	Fsm_V_TABLE_BODY() \
	V_FUNC_DEF(FsmTerminable, terminate, void);

#include "end_cls_decl.h"

#endif /* INC_FSM_TERMINABLE_H_ */
