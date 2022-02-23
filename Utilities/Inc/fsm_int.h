/*
 * fsm_int.h
 *
 *  Created on: Feb 15, 2022
 *      Author: Administrator
 */

#ifndef INC_FSM_INT_H_
#define INC_FSM_INT_H_

#include <stdbool.h>
#include "fsm_terminable.h"
#define USE_BASE_CLS FsmTerminable
#define USE_CLS_NAME FsmInt

CLS_DEF_X
	int val;
	int factor;
	bool valid;
	bool fed;
	bool terminated;
END_CLS_DEF_X

CTOR_EXPORT_X();

#define FsmInt_V_TABLE_BODY() \
	FsmTerminable_V_TABLE_BODY() \
	V_FUNC_DEF(FsmInt, getValue, int); \
	V_FUNC_DEF(FsmInt, isInt, bool);

#include "end_cls_decl.h"

#endif /* INC_FSM_INT_H_ */
