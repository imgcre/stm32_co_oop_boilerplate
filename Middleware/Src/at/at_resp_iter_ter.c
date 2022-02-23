/*
 * at_resp_iter_ter.c
 *
 *  Created on: Feb 19, 2022
 *      Author: Administrator
 */

#include "at/at_resp_iter_ter.h"
#define USE_BASE_CLS Object
#define USE_CLS_NAME AtRespIterTer

CTOR_IMPL_X(Fsm*** terminators, size_t setSize) {
	self->terminators = terminators;
	self->setSize = setSize;
	self->i = 0;
	self->j = 0;
}

V_FUNC_IMPL_X(next, Fsm*) {
	if(self->i >= self->setSize) return NULL;
	Fsm* curFsm = NULL;
	if(self->terminators[self->i] != NULL) {
		curFsm = self->terminators[self->i][self->j];
		if(curFsm == NULL) {
			self->i++;
			self->j = 0;
		} else {
			self->j++;
		}
	} else {
		self->i++;
	}
	return curFsm;
}

V_TABLE_VAR_DEF_X = {
	V_FUNC_REF_X(next),
};

INIT_V_TABLE_X

END_INIT_V_TABLE_X
