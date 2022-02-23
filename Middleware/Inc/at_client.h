/*
 * at_client.h
 *
 *  Created on: Feb 12, 2022
 *      Author: Administrator
 */

#ifndef AT_CLIENT_H_
#define AT_CLIENT_H_


#include "stm32g0xx_hal.h"
#include "task.h"
#include "s_task.h"
#include "at/at_urc_reg_item.h"
#include "at/at_fsm_resp.h"
#include "fsm_line.h"

#include "object.h"
#define USE_BASE_CLS Task
#define USE_CLS_NAME AtClient

#define AT_CLIENT_UART_CHAN_SIZE 64
#define AT_CLIENT_REQ_BUF_SIZE 64
#define AT_CLIENT_CACHED_DATA_SIZE 32

CLS_DEF_X
	int stack[1024 / sizeof(int)];
	s_chan_declare(uartChan, char, AT_CLIENT_UART_CHAN_SIZE);
	UART_HandleTypeDef* huart;
	AtUrcRegItem *urcList, *focusedUrcItem;
	char reqBuffer[AT_CLIENT_REQ_BUF_SIZE];
	s_mutex_t respMutex;
	s_event_t respEvent;
	AtFsmResp* currFsmResp;
	char cachedData[AT_CLIENT_CACHED_DATA_SIZE];
	size_t cachedDataSize;
	FsmLine fsmLine;
END_CLS_DEF_X

CTOR_ASYNC_EXPORT_X(UART_HandleTypeDef* huart);

#define AtClient_V_TABLE_BODY() \
	Task_V_TABLE_BODY() \
	V_FUNC_ASYNC_DEF(AtClient, request, void, AtFsmResp* resp, const char* cmd, ...); \
	V_FUNC_DEF(AtClient, registerUrc, void, AtUrcRegItem* item); \
	V_FUNC_DEF(AtClient, _recv, void, char value); \
	V_FUNC_DEF(AtClient, recv, void, char value);

#include "end_cls_decl.h"

#endif /* INC_AT_CLIENT_H_ */
