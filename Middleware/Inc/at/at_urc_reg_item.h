/*
 * at_urc_reg_item.h
 *
 *  Created on: Feb 19, 2022
 *      Author: Administrator
 */

#ifndef INC_AT_AT_URC_REG_ITEM_H_
#define INC_AT_AT_URC_REG_ITEM_H_

#include "at/at_fsm_resp_line.h"
#include "object.h"
#define USE_BASE_CLS Object
#define USE_CLS_NAME AtUrcRegItem


CLS_DEF_X
	CLS_X next;
	AtFsmRespLine* fsm;
END_CLS_DEF_X

#define AtUrcRegItem_V_TABLE_BODY() \
	Object_V_TABLE_BODY() \
	V_FUNC_DEF(AtUrcRegItem, onMatch, void);

CTOR_EXPORT_X(AtFsmRespLine* fsm);

#include "end_cls_decl.h"

#endif /* INC_AT_AT_URC_REG_ITEM_H_ */
