/******************************************************************************
 * File Name.c
 *
 *  Created on: April 24, 2023
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
const int32_t BLE_Password = 123456;
const uint8_t BLE_deviceName[] = {'A', 'n', 'i', 's', '1', '2', '3', '4'};
const uint8_t BLE_deviceName_len = 8;
uint8_t BLE_Advertising_Set_Handle = 0xFF;
uint8_t BLE_Connection_Handle;
volatile bool BLE_Device_Connected = false;

/*******************************************************************************
 * Extern
 ******************************************************************************/

/*******************************************************************************
 * Interface Functions
 ******************************************************************************/

/*******************************************************************************
 * Private Functions
 ******************************************************************************/
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
/*******************************************************************************
* Bluetooth stack event handler.
* This overrides the dummy weak implementation.
* @param[in] evt Event coming from the Bluetooth stack.
*******************************************************************************/
void sl_bt_on_event(sl_bt_msg_t *evt)
{

  sl_status_t sc;
  bd_addr address;
  uint8_t address_type;
  uint8_t system_id[8];
  uint8_t buf[100] = {0};
  size_t bufSize = 0;

  switch (SL_BT_MSG_ID(evt->header))
  {
    //************************************* sl_bt_evt_system_boot_id ***************************************
    case sl_bt_evt_system_boot_id:
      printf("BLE evt: system boot\n");

      sc = sl_bt_sm_configure(0x03,
                              sl_bt_sm_io_capability_keyboardonly);//00000011- all can connect

      sc = sl_bt_scanner_start(sl_bt_gap_1m_phy,
                               sl_bt_scanner_discover_observation);

      break;

      //******************************* sl_bt_evt_scanner_scan_report_id ***********************************
    case sl_bt_evt_scanner_scan_report_id:;
      printf("BLE evt: scanner scan report id\n");
      if(evt->data.evt_scanner_scan_report.packet_type == 0)
        {
          uint8_t ret = Process_Scan_Response_BLE_DeviceName(&(evt->data.evt_scanner_scan_report.data.data[0]),
                                                             evt->data.evt_scanner_scan_report.data.len,
                                                             &BLE_deviceName,
                                                             BLE_deviceName_len);
          if(ret == 1)
            {
              printf("BLE evt: scanner scan report id, found device\n");
              // Found BLE device now we stop scanning
              sc = sl_bt_scanner_stop();
              BLE_sl_status_display(sc);

              // Open connection with device
              sc = sl_bt_connection_open(evt->data.evt_scanner_scan_report.address,
                                         evt->data.evt_scanner_scan_report.address_type,
                                         sl_bt_gap_1m_phy,
                                         &BLE_Connection_Handle);
              BLE_sl_status_display(sc);
            }
        }
      break;

      //********************************** sl_bt_evt_connection_opened_id **********************************
    case sl_bt_evt_connection_opened_id:
      printf("BLE evt: connection opened\n");
      if (evt->data.evt_connection_opened.master == 1) /**< Device role in connection. Values: - <b>0:</b> Peripheral - <b>1:</b> Central */
        {
          printf("BLE evt: Connection open, Connection as Centertal\n");
          if (evt->data.evt_connection_opened.bonding != SL_BT_INVALID_BONDING_HANDLE)
            {
              //Already bonded
              printf("BLE evt: Connection open, Already bonded\n");
              sc = sl_bt_gatt_discover_primary_services(BLE_Connection_Handle);
            }
        }
      break;

      //********************************** sl_bt_evt_connection_closed_id **********************************
    case sl_bt_evt_connection_closed_id:
      printf("BLE evt: connection closed\n");
      break;

      //********************************** sl_bt_evt_sm_passkey_display_id *********************************
    case sl_bt_evt_sm_passkey_display_id:
      printf("BLE evt: passkey display\n");
      break;

      //********************************** sl_bt_evt_sm_passkey_request_id *********************************
    case sl_bt_evt_sm_passkey_request_id:
      printf("BLE evt: Enter passkey\n");
      sl_bt_sm_enter_passkey(BLE_Connection_Handle, BLE_Password);
      break;

      //************************************* sl_bt_evt_sm_bonded_id ***************************************
    case sl_bt_evt_sm_bonded_id:
      printf("BLE evt: bonded\n");
      sc = sl_bt_gatt_discover_primary_services(BLE_Connection_Handle);
      break;

      //********************************** sl_bt_evt_sm_bonding_failed_id **********************************
    case sl_bt_evt_sm_bonding_failed_id:
      printf("BLE evt: bonding failed\n");
      break;

      //*********************************** sl_bt_evt_gatt_service_id **************************************
    case sl_bt_evt_gatt_service_id:
      printf("BLE evt: Service ID\n");
      break;

      //**************************** sl_bt_evt_gatt_procedure_completed_id ********************************
    case sl_bt_evt_gatt_procedure_completed_id:
      printf("BLE evt: Procedure completed\n");
      break;

      //************************* sl_bt_evt_gatt_server_characteristic_status_id ***************************
    case sl_bt_evt_gatt_server_characteristic_status_id:;
      printf("BLE evt: server characteristic status\n");
      break;

      //**************************** sl_bt_evt_connection_parameters_id ************************************
    case sl_bt_evt_connection_parameters_id:;
      printf("BLE evt: Connection parameters\n");
      break;

      //**************************** sl_bt_evt_connection_phy_status_id ************************************
    case sl_bt_evt_connection_phy_status_id:;
      printf("BLE evt: Connection phy status\n");
      break;

      //************************* sl_bt_evt_connection_remote_used_features_id *****************************
    case sl_bt_evt_connection_remote_used_features_id:;
      printf("BLE evt: Connection remote used features\n");
      break;

    //**************************** sl_bt_evt_gatt_server_attribute_value_id ********************************
    case sl_bt_evt_gatt_server_attribute_value_id:;
      printf("BLE evt: server attribute value\n");
      break;

      //**************************** sl_bt_evt_gatt_mtu_exchanged_id ***************************************
      case sl_bt_evt_gatt_mtu_exchanged_id:;
        printf("BLE evt: mtu exchange id\n");
        break;

      //********************************************* Default **********************************************
    default:;
      uint32_t Step = SL_BT_MSG_ID(evt->header);
      (void)Step;
      printf("BLE evt: unknown %ld\n",Step);
    break;
  }
}
