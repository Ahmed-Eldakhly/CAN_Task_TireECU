/***********************************************************************************
 * Module     : ECU of Tires Status
 *
 * File name  : "main.c"
 *
 * Created on : Oct 15, 2019
 *
 * Author     : Abdo & Dakhly & Taha & Taher & Hesham
 ***********************************************************************************/

/***********************************************************************************
 *                               Included libraries
 ***********************************************************************************/
#include "Tire_ECU.h"

/***********************************************************************************
 *                               Main Function
 ***********************************************************************************/
int main(void)
{
    static uint8_t *RecivedMessage;
    static EnumTireStatus_t TiresStatus;
    Tire_ECU_Init();

    while(1)
    {
        /*Check if Diagnostic ECU send new configurations*/
        RecivedMessage = Tire_ECU_ReadMailBox();

        /*update configurations*/
        if( (RecivedMessage[0] == 0xF1) && (RecivedMessage[1] == 0xFE) )
        {
            if(RecivedMessage[2] == TX_TIRES_MAILBOX_MSG_ID)
            {
                Set_TireDefaultPressure(RecivedMessage[3]);
            }
            else if(RecivedMessage[2] == TX_FAULT_MAILBOX_MSG_ID)
            {
                Set_TireDefaultFaultPressure(RecivedMessage[3]);
            }
            else
            {
                /*Do Nothing*/
            }
        }
        else
        {
            /*Do Nothing*/
        }

        /*Check on Tires Pressure*/
        TiresStatus = CheckTireStatus();

        /*if any tire pressure is more than Limited pressure, Tire ECU will send alarm to Diagnostic ECU with this problem*/
        if(TiresStatus == TIRE_NOT_OK)
        {
            Tire_ECU_WriteFaultMailBox();
        }
        else
        {
            /*Do Nothing*/
        }

        /*Send Tires Pressure to Diagnostic ECU*/
        Tire_ECU_WriteMailBox();

        /*Delay to 200 ms*/
        SysCtlDelay(16000000 / 15);
    }
}
