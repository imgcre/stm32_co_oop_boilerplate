/*
 * fsm.h
 *
 *  Created on: Feb 13, 2022
 *      Author: Administrator
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "object.h"
#include <stdbool.h>

#define USE_BASE_CLS Object
#define USE_CLS_NAME Fsm

CLS_DEF_X

END_CLS_DEF_X

#define Fsm_V_TABLE_BODY() \
	Object_V_TABLE_BODY() \
	V_FUNC_DEF(Fsm, next, void, char value); \
	V_FUNC_DEF(Fsm, reset, void); \
	V_FUNC_DEF(Fsm, isTerminated, bool);

CTOR_EXPORT_X();

#include "end_cls_decl.h"

#endif /* INC_FSM_H_ */
