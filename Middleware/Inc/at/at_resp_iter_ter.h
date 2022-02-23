/*
 * at_resp_iter_ter.h
 *
 *  Created on: Feb 19, 2022
 *      Author: Administrator
 */

#ifndef INC_AT_AT_RESP_ITER_TER_H_
#define INC_AT_AT_RESP_ITER_TER_H_

#include "fsm.h"
#include "object.h"
#define USE_BASE_CLS Object
#define USE_CLS_NAME AtRespIterTer

CLS_DEF_X
	Fsm*** terminators;
	size_t setSize;
	int i, j;
END_CLS_DEF_X

#define AtRespIterTer_V_TABLE_BODY() \
	Object_V_TABLE_BODY() \
	V_FUNC_DEF(AtRespIterTer, next, Fsm*);

CTOR_EXPORT_X(Fsm*** terminators, size_t setSize);

#include "end_cls_decl.h"

#endif /* INC_AT_AT_RESP_ITER_TER_H_ */
