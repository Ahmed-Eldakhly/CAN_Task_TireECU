/***********************************************************************************
 * Module     : ECU of Tires Status
 *
 * File name  : "Tire_ECU_cfg.h"
 *
 * Created on : Oct 15, 2019
 *
 * Author     : Abdo & Dakhly & Taha & Taher & Hesham
 ***********************************************************************************/

#ifndef TIRE_ECU_CFG_H_
#define TIRE_ECU_CFG_H_

/************************ MailBoxs configurations Macros ***************************/
/* Diagnostic MailBox Macros */
#define RX_DIAGNOSTIC_MAILBOX            ((uint32_t)0x03)
#define RX_DIAGNOSTIC_MAILBOX_MSG_ID     ((uint32_t)0x7E0)
#define RX_DIAGNOSTIC_MAILBOX_MSG_FILTER ((uint32_t)0x7FF)
#define RX_DIAGNOSTIC_MAILBOX_MSG_FLAG   ((uint32_t)0x00)
#define RX_DIAGNOSTIC_MAILBOX_MSG_LENGTH ((uint32_t)0x04)

/* Tires pressure values MailBox Macros */
#define TX_TIRES_MAILBOX                ((uint32_t)0x02)
#define TX_TIRES_MSG_ID                 ((uint32_t)0x04)
#define TX_TIRES_MSG_FILTER             ((uint32_t)0x00)
#define TX_TIRES_MSG_FLAG               ((uint32_t)0x00)
#define TX_TIRES_MSG_LENGTH             ((uint32_t)0x04)

/* Tire Fault MailBox Macros */
#define TX_FAULT_MAILBOX                ((uint32_t)0x01)
#define TX_FAULT_MAILBOX_MSG_ID         ((uint32_t)0x02)
#define TX_FAULT_MAILBOX_MSG_FILTER     ((uint32_t)0x00)
#define TX_FAULT_MAILBOX_MSG_FLAG       ((uint32_t)0x00)
#define TX_FAULT_MAILBOX_MSG_LENGH      ((uint32_t)0x01)
#define TX_DEFAULT_VALUE                ((uint32_t)0x50)

/**********************************************************************************/


#endif /* TIRE_ECU_CFG_H_ */
