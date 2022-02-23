/*
 * navi_urc_reg_item.h
 *
 *  Created on: Feb 21, 2022
 *      Author: Administrator
 */

#ifndef INC_NAVI_URC_REG_ITEM_H_
#define INC_NAVI_URC_REG_ITEM_H_

#include "fsm_extractly.h"
#include "fsm_int.h"

#include "at/at_urc_reg_item.h"
#define USE_BASE_CLS AtUrcRegItem
#define USE_CLS_NAME NaviUrcRegItem

CLS_DEF_X
	AtFsmRespLine fsmRespLine;
	FsmExtractly fsmKeyword;
	FsmInt fsmParam0;
	RespLineParamItem params[1];
END_CLS_DEF_X

#define NaviUrcRegItem_V_TABLE_BODY() \
	AtUrcRegItem_V_TABLE_BODY()

CTOR_EXPORT_X();

#include "end_cls_decl.h"

#endif /* INC_NAVI_URC_REG_ITEM_H_ */
