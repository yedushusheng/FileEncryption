/*++

Copyright (c) 1999-2002  Microsoft Corporation

Module Name:

    scanUser.c

Abstract:

    This file contains the implementation for the main function of the
    user application piece of scanner.  This function is responsible for
    actually scanning file contents.

Environment:

    User mode

--*/

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <winioctl.h>
#include <string.h>
#include <crtdbg.h>
#include <assert.h>
#include <fltuser.h>
#include <dontuse.h>
#include <process.h>
#include "interface.h"

int _cdecl
main (
    __in int argc,
    __in_ecount(argc) char *argv[]
    )
{
    
    HANDLE hPort;
   
    HRESULT hr;
   
    ULONG hRes,dwReturned; 

    MSG_SEND_ADD_PROCESS_INFO sSendAddProcInfo;
    MSG_GET_ADD_PROCESS_INFO  sGetAddProcInfo;
	int i;



    //
    //  Open a commuication channel to the filter
    //

	
    printf( "Scanner: Connecting to the filter ...\n" );

    hr = FilterConnectCommunicationPort( SERVER_PORTNAME,
                                         0,
                                         NULL,
                                         0,
                                         NULL,
                                         &hPort );

    if (IS_ERROR( hr )) {

        printf( "ERROR: Connecting to filter port: 0x%08x\n", hr );
        return 2;
    }
	
	

	printf("%d\n",argc);
	for(i=1;i<argc;i++)
	{
		memset(&sSendAddProcInfo, 0, sizeof(sSendAddProcInfo));
		sSendAddProcInfo.sSendType.uSendType = IOCTL_ADD_PROCESS_INFO;
		sSendAddProcInfo.sProcInfo.bMonitor = TRUE;
		RtlCopyMemory(sSendAddProcInfo.sProcInfo.szProcessName, argv[i], strlen( argv[i]));
		printf("%d\n",sizeof(MSG_SEND_ADD_PROCESS_INFO));

		printf("%d\n",sSendAddProcInfo.sSendType.uSendType);
		
		printf("%s\n",sSendAddProcInfo.sProcInfo.szProcessName);
		memset(&sGetAddProcInfo, 0, sizeof(MSG_GET_ADD_PROCESS_INFO));
		hRes = FilterSendMessage(hPort, &sSendAddProcInfo, sizeof(MSG_SEND_ADD_PROCESS_INFO), &sGetAddProcInfo, sizeof(MSG_GET_ADD_PROCESS_INFO), &dwReturned);
	}
	getchar();










   
   /**
    memset(&sSendAddProcInfo, 0, sizeof(sSendAddProcInfo));
    sSendAddProcInfo.sSendType.uSendType = IOCTL_ADD_PROCESS_INFO;
    sSendAddProcInfo.sProcInfo.bMonitor = TRUE;
    RtlCopyMemory(sSendAddProcInfo.sProcInfo.szProcessName, "system", strlen("system"));
    memset(&sGetAddProcInfo, 0, sizeof(MSG_GET_ADD_PROCESS_INFO));
    hRes = FilterSendMessage(hPort, &sSendAddProcInfo, sizeof(MSG_SEND_ADD_PROCESS_INFO), &sGetAddProcInfo, sizeof(MSG_GET_ADD_PROCESS_INFO), &dwReturned);
   
    memset(&sSendAddProcInfo, 0, sizeof(sSendAddProcInfo));
    sSendAddProcInfo.sSendType.uSendType = IOCTL_ADD_PROCESS_INFO;
    sSendAddProcInfo.sProcInfo.bMonitor = TRUE;
    RtlCopyMemory(sSendAddProcInfo.sProcInfo.szProcessName, "explorer.exe", strlen("explorer.exe"));
    memset(&sGetAddProcInfo, 0, sizeof(MSG_GET_ADD_PROCESS_INFO));
    hRes = FilterSendMessage(hPort, &sSendAddProcInfo, sizeof(MSG_SEND_ADD_PROCESS_INFO), &sGetAddProcInfo, sizeof(MSG_GET_ADD_PROCESS_INFO), &dwReturned);
	*/
   
    return 0;
}

