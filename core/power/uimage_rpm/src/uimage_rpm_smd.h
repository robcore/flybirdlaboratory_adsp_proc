#ifndef UIMAGE_RPM_SMD_H
#define UIMAGE_RPM_SMD_H

#include "DALStdDef.h"
#include "uimage_rpm_resource_data.h"

/*******************************************************************************
 *
 * uImage_rpm_smd_init
 *
 * This function is used to initialize SMD shared info.
 *
 */
void uImage_rpm_smd_init(void);

/*******************************************************************************
 *
 * uImage_rpm_sendMessage
 *
 * This function is used to send a message to RPM FW by writing into the
 * message RAM, and signalling when done
 *
 *   msg_id:          Message ID
 *   resource_info:   Resource request info
 *
 */
void uImage_rpm_sendMessage(uint32 msg_id, const uImage_rpm_resource_info_t *resource_info);

/*******************************************************************************
 *
 * uImage_rpm_readAck
 *
 * This function is used to clear all DDR ACKs the first time we enter
 * uImage and then on to read Acks from RPM and ensure the contents of
 * the ack are as expected
 *
 *   msg_id:     Message ID
 *   clear_nas:  Clear out NAS message Acks from DDR
 *
 */
DALBOOL uImage_rpm_readAck(uint32 msg_id, DALBOOL clear_nas);

#endif /* UIMAGE_RPM_SMD_H */

