#ifndef __DRV_CABLE_TEST_H
#define __DRV_CABLE_TEST_H

#include "bsp_gpio.h"

typedef enum {
		CABLE_UTP,
    CABLE_SFTP
} CableType_t;
extern CableType_t cable;

void HW_Cable_Init(void);
void CableTest_Init(void);
void CableType_Detect(void);
uint8_t CableTest_RunOnce(void);
uint8_t CableTest_CheckOpen(void);

#endif

