/******************************************************************************
 * File Name.c
 *
 *  Created on: April 08, 2023
 *  Author: Anis Shakkour
 *  Email:  anis.shakkour399@gmail.com
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "BLE_Centeral.h"

/*******************************************************************************
 * Data types
 ******************************************************************************/

/*******************************************************************************
 * Extern
 ******************************************************************************/


/*******************************************************************************
 * Interface Functions
 ******************************************************************************/

/*******************************************************************************
 * Private Functions
 ******************************************************************************/

/******************************************************************************
 * Function name: Process_Scan_Response_BLE_DeviceName
 *
 * Description  : When scanning we enter here and check data types found.
 *                checking for shortened local name or complete local name data packet
 *                reference https://btprodspecificationrefs.blob.core.windows.net/assigned-numbers/Assigned%20Number%20Types/Assigned%20Numbers.pdf
 *                page 13
 *
 *                /-------- Packet overview -----------------------------------------------\
 *                | 0   |  1   |  2      -  n   |  n + 1 | n + 2 | n + 4  .....            |
 *                |------------------------------------------------------------------------|
 *                | Len | type | name[n] -      | Len    | type  | name[n] -               |
 *                \------------------------------------------------------------------------/
 *
 * Parameters   : [data] pointer to the advertised packet found.
 *                [stored_BytesNum] number data advertised in that current packet.
 *                [deviceName] predefined device name Central is looking for
 *                [deviceName_len] predefined device name length Central is looking for
 * Returns      : true if device name is found in that current advertised packet, false otherwise.
 *
 * Known issues :
 * Note         :
 * TODO         :
 *
 * ****************************************************************************/
bool Process_Scan_Response_BLE_DeviceName(uint8_t *data, uint8_t stored_BytesNum, uint8_t deviceName[], uint8_t deviceName_len)
{
  //decoding scan response (advertised packets from other devices)
  for(uint8_t i = 0; i< stored_BytesNum; )
    {
      /* Parse packet */
      int advetised_PKT_len = data[i];
      int advetised_PKT_type = data[i + 1];

      /* Check packet type */
      if((advetised_PKT_type == COMPLETE_LOCALE_NAME) ||
         (advetised_PKT_type == SHORTENED_LOCAL_NAME))
          {
            if(memcmp(&(data[i+2]), deviceName, deviceName_len) == 0)
              {
                return true;
              }
          }
      i += advetised_PKT_len + 1;
    }
  return false;
}


/*******************************************************************************
 * Function name: BLE_sl_status_display
 *
 * Description  : Print BLE SiLabs statuses
 * Parameters   :
 * Returns      :
 *
 * Known issues :
 * Note         :
 ******************************************************************************/
void BLE_sl_status_display(sl_status_t sc)
{

  switch(sc){

    case SL_STATUS_OK:
      printf("sl status: success\n");
      break;

    case SL_STATUS_FAIL:
      printf("sl status: fail\n");
      break;

    case SL_STATUS_WOULD_OVERFLOW:
      printf("sl status: would overflow\n");
      break;
  }
}
