#ifndef _APP_H_
#define _APP_H_

#include "s_task.h"
#include "object.h"
#include "task.h"
#include "print_task.h"
#include "at/at_fsm_resp.h"
#include "at/at_fsm_resp_line.h"
#include "fsm_extractly.h"
#include "fsm_int.h"
#include "navi_urc_reg_item.h"
#include "runar_urc_reg_item.h"
#include "at_client.h"

CLS_DEF(App, Task)
//	PrintTask task1, task2;
	AtFsmResp fsmResp;
	AtFsmRespLine fsmTestLine;
	FsmExtractly fsmTestLineKeyword;
	RespLineParamItem testLineItems[1];
	FsmInt fsmTestLineData;
	AtRespItem respItems[1];
	NaviUrcRegItem naviUrcRegItem;
	RunarUrcRegItem runarUrcRegItem;
	AtClient atClient;

	int stack[1024 / sizeof(int)];
END_CLS_DEF(App)

CTOR_ASYNC_EXPORT(App);

#define App_V_TABLE_BODY() \
	Task_V_TABLE_BODY();

CLS_EXPORTS(App, Object);

#endif
