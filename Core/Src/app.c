#include <stdio.h>
#include "app.h"
#include "print_task.h"
#include "fsm_extractly.h"
#include "fsm_int.h"
#include "at_client.h"

#define USE_BASE_CLS Task
#define USE_CLS_NAME App

CTOR_ASYNC_IMPL(App) {
	BASE_ASYNC_CTOR(Task);
//	s_task_init_system();

}

void print_feed(char c) {
	switch(c) {
	case '\r':
		//printf("feed [CR]\n");
		break;
	case '\n':
		//printf("feed [LF]\n");
		break;
	default:
		//printf("feed %c\n", c);
		break;
	}
}

char test_str[] =
	"+NAV: 456\r\n"
	"+RUNAR: 53945\r\n"
	"+NAVI: 123\r\n"
	"OK\r\n";

extern UART_HandleTypeDef huart1;

V_FUNC_ASYNC_OVERRIDE(App, run, void) {
	INST_ASYNC_MAKE(AtClient, &self->atClient, &huart1);

//	INST_MAKE(NaviUrcRegItem, &self->naviUrcRegItem);
//	INVOKE(AtClient, &self->atClient, registerUrc, (AtUrcRegItem*)&self->naviUrcRegItem);
//
//	INST_MAKE(RunarUrcRegItem, &self->runarUrcRegItem);
//	INVOKE(AtClient, &self->atClient, registerUrc, (AtUrcRegItem*)&self->runarUrcRegItem);
//
//	INST_CREATE(FsmExtractly, keyword, "NAV");
//	INST_CREATE(FsmInt, p0);
//	RespLineParamItem pitems[] = {
//		{
//			.idx = 0,
//			.fsm = (FsmTerminable*)&p0,
//		}
//	};
//	INST_CREATE(AtFsmRespLine, respLine, (FsmValidatable*)&keyword, pitems, A_SIZE(pitems));

//	AtRespItem litems[] = {
//		{
//			.idx = -1,
//			.fsm = (FsmValidatable*)&respLine,
//		}
//	};
//
//	INST_CREATE(AtFsmResp, resp, litems, A_SIZE(litems), NULL);
	INST_CREATE(AtFsmResp, resp, NULL, 0, NULL);
	INVOKE_ASYNC(AtClient, &self->atClient, request, &resp, "AT+HELLO\r\n");
//	for(int i = 0; i < sizeof(test_str) - 1; i++) {
//		print_feed(test_str[i]);
//		INVOKE(AtClient, &self->atClient, _recv, test_str[i]);
//		printf("RL ter: %d, val: %d\n",
//			INVOKE(Fsm, &resp, isTerminated),
//			INVOKE(FsmInt, &p0, getValue)
//		);
//		printf("\n");
//	}

//	printf("RL ter: %d, val: %d\n",
//		INVOKE(Fsm, &resp, isTerminated),
//		INVOKE(FsmInt, &p0, getValue)
//	);

	//printf("usage: %d\n", INVOKE_X(getStackUsage));




//	INVOKE_ASYNC(AtClient, &client, request, NULL, "AT+NAVI=%d,%s\r\n", 123, "protogen");
//	INVOKE_ASYNC(AtClient, &client, request, NULL, "AT+BIRTH=%d,%d,%d\r\n", 2002, 3, 28);
//
//	INST_MAKE(FsmExtractly, &self->fsmTestLineKeyword, "TEST");
//	INST_MAKE(FsmInt, &self->fsmTestLineData);
//	self->testLineItems[0] = (RespLineParamItem) {
//		.idx = 0,
//		.fsm = (FsmTerminable*)&self->fsmTestLineData,
//	};
//	INST_MAKE(AtFsmRespLine, &self->fsmTestLine, (FsmValidatable*)&self->fsmTestLineKeyword, self->testLineItems, A_SIZE(self->testLineItems));
//
//	self->respItems[0] = (AtRespItem) {
//		.idx = -1,
//		.fsm = (FsmValidatable*)&self->fsmTestLine,
//	};
//
//	INST_MAKE(AtFsmResp, &self->fsmResp, self->respItems, A_SIZE(self->respItems), NULL);
//
//	printf("test str: %s\n\n", test_str);
//	for(int i = 0; i < sizeof(test_str) - 1; i++) {
//		print_feed(test_str[i]);
//		INVOKE(Fsm, &self->fsmResp, next, test_str[i]);
//		printf("RL ter: %d\n",
//			INVOKE(Fsm, &self->fsmResp, isTerminated)
//		);
//		printf("\n");
//	}
//
//	printf("test val: ter: %d, isInt: %d, val: %d\n",
//		INVOKE(Fsm, &self->fsmTestLineData, isTerminated),
//		INVOKE(FsmInt, &self->fsmTestLineData, isInt),
//		INVOKE(FsmInt, &self->fsmTestLineData, getValue)
//	);
//
//	printf("stack usage: %d\n", INVOKE(Task, self, getStackUsage));

	while(1) {
		s_task_sleep(__await__, 5);
	}
}

V_FUNC_OVERRIDE(App, getStackPtr, void*) {
	return self->stack;
}


V_FUNC_OVERRIDE(App, getStackSize, size_t) {
	return sizeof(self->stack);
}

V_TABLE_VAR_DEF(App) = {0};

INIT_V_TABLE(App, Task)
	V_OVERRIDE(App, Task, run);
	V_OVERRIDE(App, Task, getStackPtr);
	V_OVERRIDE(App, Task, getStackSize);
END_INIT_V_TABLE(App)
