/*
 * at_client.c
 *
 *  Created on: Feb 12, 2022
 *      Author: Administrator
 */

#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#include "at_client.h"
#define USE_BASE_CLS Task
#define USE_CLS_NAME AtClient

//TODO: atClient本身要吃一个线程，先给他2KB的线程栈

CTOR_ASYNC_IMPL_X(UART_HandleTypeDef* huart) {
	self->huart = huart;
	self->urcList = NULL;
	self->focusedUrcItem = NULL;
	self->currFsmResp = NULL;
	s_chan_init(self->uartChan, char, AT_CLIENT_UART_CHAN_SIZE);
	s_mutex_init(&self->respMutex);
	s_event_init(&self->respEvent);
	self->cachedDataSize = 0;
	INST_MAKE(FsmLine, &self->fsmLine);
	BASE_ASYNC_CTOR(Task);
}

V_FUNC_ASYNC_IMPL_X(request, void, AtFsmResp* resp, const char* cmd, ...) {
	va_list va;
	va_start (va, cmd);

	//TODO: 等待自己的AtResp状态机终结，同时只能存在一个request的AtResp状态机
//	s_mutex_lock(__await__, &self->respMutex);

//	sprintf(self->reqBuffer, cmd, va);
//	HAL_UART_Transmit(self->huart, (uint8_t*)self->reqBuffer, strlen(self->reqBuffer), HAL_MAX_DELAY);

	HAL_UART_Transmit(self->huart, (uint8_t*)cmd, strlen(cmd), HAL_MAX_DELAY);

	self->currFsmResp = resp;
	s_event_wait_sec(__await__, &self->respEvent, 9999);
	//printf("AT RESP EVENT SET\n");
	self->currFsmResp = NULL;

//	s_mutex_unlock(&self->respMutex);
	va_end (va);
}

V_FUNC_IMPL_X(registerUrc, void, AtUrcRegItem* item) {
	if(self->urcList == NULL) {
		self->urcList = item;
	} else {
		//插入到最前面
		AtUrcRegItem* rear = self->urcList;
		self->urcList = item;
		item->next = rear;
	}
}

V_FUNC_ASYNC_OVERRIDE_X(run, void) {
	//printf("====AT THREAD RUNNING====\n");
	while(true) {
		char value;
		s_chan_get(__await__, self->uartChan, &value);
		//printf("AT recv: %d\n", value);
		INVOKE_X(_recv, value);
//		s_task_sleep(__await__, 5);
	}
}

V_FUNC_OVERRIDE_X(getStackPtr, void*) {
	return self->stack;
}

V_FUNC_OVERRIDE_X(getStackSize, size_t) {
	return sizeof(self->stack);
}

//请在线程模式下调用
V_FUNC_IMPL_X(_recv, void, char value) {
	INVOKE(Fsm, &self->fsmLine, next, value);
	if(self->focusedUrcItem == NULL) {
		bool allUrcInvalid = true;
		AtUrcRegItem* currUrc = self->urcList;
		while(currUrc != NULL) {
			//尝试更新所有的URC状态机
			INVOKE(Fsm, currUrc->fsm, next, value);
			//如果所有的都是无效状态，则调用
			if(INVOKE(FsmValidatable, currUrc->fsm, isValid)) {
				allUrcInvalid = false;
			}
			if(currUrc->fsm->state == STATE_AT_FSM_RESP_LINE_PARAM_BODY) {
				self->focusedUrcItem = currUrc;
				//printf("CACHE clean\n");
				self->cachedDataSize = 0;
				break;
			}
			currUrc = currUrc->next;
		}
		if(allUrcInvalid) {
			if(self->currFsmResp != NULL) {

				for(int i = 0; i < self->cachedDataSize; i++) {
					//printf("*route to resp: %d\n", self->cachedData[i]);
					INVOKE(Fsm, self->currFsmResp, next, self->cachedData[i]);
				}
				//printf("CACHE clean\n");
				self->cachedDataSize = 0;
				//printf("*route to resp: %d\n", value);
				INVOKE(Fsm, self->currFsmResp, next, value);

				if(INVOKE(Fsm, self->currFsmResp, isTerminated)) {
					//printf("AT RESP TERMINATED\n");
					s_event_set(&self->respEvent);
				}
			}
		} else {
			if(self->focusedUrcItem == NULL) {
				//printf("CACHE put %d\n", value);
				self->cachedData[self->cachedDataSize++] = value;
			}
		}
	} else {
		//等待这个状态机终结
		INVOKE(Fsm, self->focusedUrcItem->fsm, next, value);
		if(INVOKE(Fsm, self->focusedUrcItem->fsm, isTerminated)) {
			INVOKE(AtUrcRegItem, self->focusedUrcItem, onMatch);
			self->focusedUrcItem = NULL;
		}
	}

	if(INVOKE(Fsm, &self->fsmLine, isTerminated)) {
		INVOKE(Fsm, &self->fsmLine, reset);
		//复位所有URC状态机
		AtUrcRegItem* currUrc = self->urcList;
		while(currUrc != NULL) {
			INVOKE(Fsm, currUrc->fsm, reset);
			currUrc = currUrc->next;
		}
	}
}

//请在中断模式下调用
V_FUNC_IMPL_X(recv, void, char value) {
	s_chan_put__in_irq(self->uartChan, &value);
}

V_TABLE_VAR_DEF_X = {
	V_FUNC_REF_X(request),
	V_FUNC_REF_X(registerUrc),
	V_FUNC_REF_X(_recv),
	V_FUNC_REF_X(recv),
};


INIT_V_TABLE_X
	V_OVERRIDE_X(run);
	V_OVERRIDE_X(getStackPtr);
	V_OVERRIDE_X(getStackSize);
END_INIT_V_TABLE_X
