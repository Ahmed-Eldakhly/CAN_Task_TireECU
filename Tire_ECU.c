/***********************************************************************************
 * Module     : ECU of Tires Status
 *
 * File name  : "Tire_ECU.c"
 *
 * Created on : Oct 15, 2019
 *
 * Author     : Abdo & Dakhly & Taha & Taher & Hesham
 ***********************************************************************************/

/***********************************************************************************
 *                            Included libraries
 ***********************************************************************************/
#include "Tire_ECU.h"

/***********************************************************************************
 *                                Type Define
 ************************************************************************************/

typedef union
{
    uint8_t allFaults;
    struct
    {
        uint8_t TierLeft    : 1 ;
        uint8_t TierRight   : 1 ;
        uint8_t ButtomRight : 1 ;
        uint8_t ButtomLeft  : 1 ;
        uint8_t             : 4 ;
    }FAULT_BITS;
}Fault_t;


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Received Diagnostic Data*/
uint8_t RX_DIAGNOSTIC_MailBox_Msg_Data[RX_DIAGNOSTIC_MAILBOX_MSG_LENGTH] = {TX_DEFAULT_VALUE};

/* array of tires pressure values*/
uint8_t TiresPresureValPar[TX_TIRES_MAILBOX_MSG_LENGTH] = {TX_DEFAULT_VALUE , TX_DEFAULT_VALUE , TX_DEFAULT_VALUE , TX_DEFAULT_VALUE};

/* Hold Fault of Tires*/
Fault_t Fault_Info = {0x00};

/*Fault Pressure of Tire*/
static uint8_t FaultPressure = DEFAULT_FAULT_PRESSURE;

/* Diagnostic message object */
static tCANMsgObject RX_DIAGNOSTIC_ObjType = {RX_DIAGNOSTIC_MAILBOX_MSG_ID,
                                              RX_DIAGNOSTIC_MAILBOX_MSG_FILTER,
                                              RX_DIAGNOSTIC_MAILBOX_MSG_FLAG,
                                              RX_DIAGNOSTIC_MAILBOX_MSG_LENGTH,
                                              RX_DIAGNOSTIC_MailBox_Msg_Data};


/* 4 Tires pressure message object */
static tCANMsgObject TX_TiresPresure_OjectTypes = {TX_TIRES_MAILBOX_MSG_ID,
                                                   TX_TIRES_MAILBOX_MSG_FILTER,
                                                   TX_TIRES_MAILBOX_MSG_FLAG,
                                                   TX_TIRES_MAILBOX_MSG_LENGTH,
                                                   TiresPresureValPar};

/* 4 Tires fault message object */
static tCANMsgObject TX_Fault_OjbectType = {TX_FAULT_MAILBOX_MSG_ID,
                                            TX_FAULT_MAILBOX_MSG_FILTER,
                                            TX_FAULT_MAILBOX_MSG_FLAG,
                                            TX_FAULT_MAILBOX_MSG_LENGH,
                                            &Fault_Info.allFaults};
/***********************************************************************************/

/***********************************************************************************
 *                              Functions Definition
 ***********************************************************************************/

/***********************************************************************************
 * Function Name:   Tire_ECU_Init
 *
 * Description:     Initialize CAN0 module in ECU of Tire information
 *
 * Inputs:          NULL
 *
 * Outputs:         NULL
 *
 * Return:          NULL
 *******************************************************************************/
void Tire_ECU_Init(void)
{

     /* Initializing CAN0 GPIO */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB));
    GPIOPinConfigure(GPIO_PB4_CAN0RX);
    GPIOPinConfigure(GPIO_PB5_CAN0TX);
    GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);

     /*Initializing CAN0 */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_CAN0));

    CANInit(CAN0_BASE);

    /*CANBitTimingSet(CAN0_BASE, &CANBitClk);*/
    CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);

    /*Enable CAN0 */
    CANEnable(CAN0_BASE);

    /* Initializing Diagnostic MailBox in Can(0) module */
    CANMessageClear(CAN0_BASE,RX_DIAGNOSTIC_MAILBOX);

    /* Initializing Tire Pressure MailBox in Can(0) module */
    CANMessageClear(CAN0_BASE,TX_TIRES_MAILBOX);

    /* Initializing Tire Fault MailBox in Can(0) module */
    CANMessageClear(CAN0_BASE, TX_FAULT_MAILBOX);

    /* Receive Diagnostic MailBox Configuration */
    CANMessageSet(CAN0_BASE,RX_DIAGNOSTIC_MAILBOX,  &RX_DIAGNOSTIC_ObjType,MSG_OBJ_TYPE_RX);

    /*send 4 Tires pressure object message*/
    CANMessageSet(CAN0_BASE, TX_TIRES_MAILBOX , &TX_TiresPresure_OjectTypes, MSG_OBJ_TYPE_TX);

    /*send 4 Tires Fault object message*/
    CANMessageSet(CAN0_BASE, TX_FAULT_MAILBOX, &TX_Fault_OjbectType, MSG_OBJ_TYPE_TX);
}

/*******************************************************************************
 * Function Name:   Tire_ECU_WriteMailBox
 *
 * Description:     Transmit tires pressure to diagnostic ECU
 *
 * Inputs:          NULL
 *
 * Outputs:         NULL
 *
 * Return:          NULL
 *******************************************************************************/
void Tire_ECU_WriteMailBox(void)
{
    /* Send the message out of the Tire pressure object.*/
    CANMessageSet(CAN0_BASE, TX_TIRES_MAILBOX , &TX_TiresPresure_OjectTypes, MSG_OBJ_TYPE_TX);
}

/*******************************************************************************
 * Function Name:   Tire_ECU_WriteFaultMailBox
 *
 * Description:     Transmit problems of tires pressure to diagnostic ECU
 *
 * Inputs:          NULL
 *
 * Outputs:         NULL
 *
 * Return:          NULL
 *******************************************************************************/
void Tire_ECU_WriteFaultMailBox(void)
{
    /* Send the message out of the Fault object.*/
    CANMessageSet(CAN0_BASE, TX_FAULT_MAILBOX , &TX_Fault_OjbectType, MSG_OBJ_TYPE_TX);
}

/*******************************************************************************
 * Function Name:   Tire_ECU_ReadMailBox
 *
 * Description:     Read message of diagnostic ECU
 *
 * Inputs:          NULL
 *
 * Outputs:         NULL
 *
 * Return:          NULL
 *******************************************************************************/
uint8_t * Tire_ECU_ReadMailBox(void)
{
    /* Pull till messages is ready*/
    if((CANStatusGet(CAN0_BASE, CAN_STS_NEWDAT) & 1) == 1)
    {
        /* Read the message out of the message object.*/
        CANMessageGet(CAN0_BASE, RX_DIAGNOSTIC_MAILBOX , &RX_DIAGNOSTIC_ObjType, true);
    }
    /*return coming Data*/
    return RX_DIAGNOSTIC_ObjType.pui8MsgData;
}

/*******************************************************************************
 * Function Name:   Set_TireDefaultPressure
 *
 * Description:     Set Default pressure to each tire
 *
 * Inputs:          NULL
 *
 * Outputs:         NULL
 *
 * Return:          NULL
 *******************************************************************************/
void Set_TireDefaultPressure(uint8_t DefaultPressure)
{
    uint8_t Counter;
    for(Counter = 0; Counter<4; Counter++)
    {
        TiresPresureValPar[Counter] = DefaultPressure;
    }
}

/*******************************************************************************
 * Function Name:   Set_TireDefaultFaultPressure
 *
 * Description:     Set Default Fault pressure to each tire
 *
 * Inputs:          NULL
 *
 * Outputs:         NULL
 *
 * Return:          NULL
 *******************************************************************************/
void Set_TireDefaultFaultPressure(uint8_t DefaultPressure)
{
    FaultPressure = DefaultPressure;
}

/*******************************************************************************
 * Function Name:   CheckTireStatus
 *
 * Description:     Check if any tire break Limited pressure value
 *
 * Inputs:          NULL
 *
 * Outputs:         NULL
 *
 * Return:          NULL
 *******************************************************************************/
EnumTireStatus_t CheckTireStatus(void)
{
    EnumTireStatus_t TireState = TIRE_OK;
    uint8_t Counter;
    for(Counter = 0; Counter<4; Counter++)
    {
        TiresPresureValPar[Counter] = FaultPressure;
        Fault_Info.allFaults |= (1<<Counter);
        TireState = TIRE_NOT_OK;
    }
    return TireState;
}

