/*
 * fsm_seq.c
 *
 *  Created on: Feb 14, 2022
 *      Author: Administrator
 */

#include <stdio.h>
#include <stdbool.h>

#include "fsm_seq.h"
#define USE_BASE_CLS Fsm
#define USE_CLS_NAME FsmSeq

//next数组长度必须比pattern大
CTOR_IMPL_X(const char* pattern, int16_t* next) {
	//printf("ctor of FsmSeq, pattern: %p, next: %p\n", pattern, next);
	self->pattern = pattern;
	self->next = next;
	INVOKE_X(genNext);
	//printf("next genged\n");
	BASE_CTOR_X();
}

V_FUNC_IMPL_X(genNext, void) {
	int j = 0, k = -1;
	//printf("gening next\n");
	self->next[j] = k;
	//printf("j: %d, k: %d\n", j, k);
	//printf("pattern: %p, next: %p\n", self->pattern, self->next);
	while(self->pattern[j] != '\0') {
		//printf("j: %d, k: %d\n", j, k);
		if(k == -1 || self->pattern[j] == self->pattern[k]) {
			j++;
			k++;
			self->next[j] = k;
		} else {
			k = self->next[k];
		}
	}
	//printf("exited\n");
}

V_FUNC_OVERRIDE_X(next, void, char value) {
	if(self->pattern[self->j] != '\0') {
		while(true) {
			if(self->j == -1 || value == self->pattern[self->j]) {
				self->j++;
				break;
			} else {
				self->j = self->next[self->j];
			}
		}
	}
}

V_FUNC_OVERRIDE_X(reset, void) {
	self->j = 0;
}

V_FUNC_OVERRIDE_X(isTerminated, bool) {
	return self->pattern[self->j] == '\0';
}

V_TABLE_VAR_DEF_X = {
	V_FUNC_REF_X(genNext),
};

INIT_V_TABLE_X
	V_OVERRIDE_X(next);
	V_OVERRIDE_X(reset);
	V_OVERRIDE_X(isTerminated);
END_INIT_V_TABLE_X
