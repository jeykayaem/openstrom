/*******************************************************************************
  Sample Application

  File Name:
    app_commands.c

  Summary:
    commands for the tcp client demo app.

  Description:
    
 *******************************************************************************/


// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END

#include "tcpip/tcpip.h"
#include "app_command.h"
#include "app.h"

#if SMSC_9303_CMD_PROCESSOR
int32_t DRV_ETHPHY_SMSC9303_InitCmdProcessor();
#endif

#if defined(TCPIP_STACK_COMMAND_ENABLE)



static int _APP_Commands_OpenURL(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
static int _APP_Commands_ChangeIP(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);

static const SYS_CMD_DESCRIPTOR    appCmdTbl[]=
{
    {"openurl",     _APP_Commands_OpenURL,              ": Connect to a url and do a GET"},
    {"ChangeIP",    _APP_Commands_ChangeIP,             ": Change the IP Address"},
};

bool APP_Commands_Init()
{
    if (!SYS_CMD_ADDGRP(appCmdTbl, sizeof(appCmdTbl)/sizeof(*appCmdTbl), "app", ": app commands"))
    {
        SYS_ERROR(SYS_ERROR_ERROR, "Failed to create TCPIP Commands\r\n");
        return false;
    }
//    memset(APP_URL_Buffer, 0, MAX_URL_SIZE);
#if SMSC_9303_CMD_PROCESSOR
    DRV_ETHPHY_SMSC9303_InitCmdProcessor();
#endif
    return true;
}

char APP_URL_Buffer[MAX_URL_SIZE];

int _APP_Commands_OpenURL(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
/*    const void* cmdIoParam = pCmdIO->cmdIoParam;

    if (argc != 2)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Usage: openurl <url>\r\n");
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Ex: openurl http://www.google.com/\r\n");
        return false;
    }*/
    //strcpy(APP_URL_Buffer, "http://techieservice.org/mcuworld/test.php?data=89");
    strncpy(APP_URL_Buffer, argv[1], MAX_URL_SIZE);
    return false;
}

int _APP_Commands_ChangeIP(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    TCPIP_NET_HANDLE    netH;
    IPV4_ADDR ipAddress;
    ipAddress.Val = 0xB677A8C0;
    netH = TCPIP_STACK_IndexToNet(0);
    TCPIP_STACK_NetAddressSet(netH, &ipAddress, NULL, 0);
    return true;
}

#endif
