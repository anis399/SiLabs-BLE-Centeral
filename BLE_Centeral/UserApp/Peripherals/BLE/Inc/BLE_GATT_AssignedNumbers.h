
/*******************************************************************************
*                     _           _           _    _                           *
*         /\         (_)         | |         | |  | |                          *
*        /  \   _ __  _ ___   ___| |__   __ _| | _| | _____  _   _ _ __        *
*       / /\ \ | '_ \| / __| / __| '_ \ / _` | |/ / |/ / _ \| | | | '__|       *
*      / ____ \| | | | \__ \ \__ \ | | | (_| |   <|   < (_) | |_| | |          *
*     /_/    \_\_| |_|_|___/ |___/_| |_|\__,_|_|\_\_|\_\___/ \__,_|_|          *
*                                                                              *
*******************************************************************************/
/*******************************************************************************
 * File BIT.h
 *
 *  Created on: March 20, 2023
 *  Author: Anis Shakkour
 *  Email:  anis.shakkour399@gmail.com
 *
 *  @brief :
 *  @note  :Referance
 *  https://btprodspecificationrefs.blob.core.windows.net/assigned-numbers/Assigned%20Number%20Types/Assigned%20Numbers.pdf
 *  @todo  :
*******************************************************************************/

/*******************************************************************************
 * Multiple include protection
*******************************************************************************/
#ifndef BLE_GATT_ASSIGNEDNUMBERS_H_
#define BLE_GATT_ASSIGNEDNUMBERS_H_

/*******************************************************************************
 * Includes
*******************************************************************************/

/*******************************************************************************
 * Macros
*******************************************************************************/

/*******************************************************************************
 * Defines
*******************************************************************************/
/* Common data types*/
#define COMPLETE_LIST_16b_SERVICE_UUID ((uint8_t)0x03)
#define SHORTENED_LOCAL_NAME           ((uint8_t)0x08) /** Contains contiguous characters from the beginning of the full BLE device name */
#define COMPLETE_LOCALE_NAME           ((uint8_t)0x09) /** COmplete name of the BLE device  and can be read */

/*******************************************************************************
 * Typedef & Enums
*******************************************************************************/

/*******************************************************************************
 * Interface Functions
*******************************************************************************/

/*******************************************************************************
 * END
*******************************************************************************/
#endif /* BLE_GATT_ASSIGNEDNUMBERS_H_ */
