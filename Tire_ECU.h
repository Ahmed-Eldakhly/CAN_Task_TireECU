/***********************************************************************************
 * Module     : ECU of Tires Status
 *
 * File name  : "Tire_ECU.h"
 *
 * Created on : Oct 15, 2019
 *
 * Author     : Abdo & Dakhly & Taha & Taher & Hesham
 ***********************************************************************************/

#ifndef TIRE_ECU_H_
#define TIRE_ECU_H_

/***********************************************************************************
 *                               Included libraries
 ***********************************************************************************/
#include "common_header.h"
#include "driverlib/can.h"
#include "Tire_ECU_cfg.h"

/***********************************************************************************
 *                                Type Define
 ************************************************************************************/
typedef enum
{
    TIRE_OK,
    TIRE_NOT_OK,
}EnumTireStatus_t;

/***********************************************************************************
 *                              Functions Deceleration
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
 ***********************************************************************************/
void Tire_ECU_Init(void);

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
void Tire_ECU_WriteMailBox(void);

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
void Tire_ECU_WriteFaultMailBox(void);

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
uint8_t * Tire_ECU_ReadMailBox(void);

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
void Set_TireDefaultPressure(uint8_t DefaultPressure);

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
void Set_TireDefaultFaultPressure(uint8_t DefaultPressure);

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
EnumTireStatus_t CheckTireStatus(void);

#endif /* TIRE_ECU_H_ */
