//this file defines some interface between driver and application.

#ifndef _INTERFACE_H_
#define _INTERFACE_H_


#define SERVER_PORTNAME L"\\EnginePort"

#define IOCTL_GET_ALL_PROCESS_INFO 0x00000001
#define IOCTL_GET_PROCESS_COUNT    0x00000002
#define IOCTL_SET_PROCESS_MONITOR  0x00000003
#define IOCTL_ADD_PROCESS_INFO     0x00000004
#define IOCTL_DEL_PROCESS_INFO     0x00000005
#define IOCTL_SET_FILEKEY_INFO     0x00000006
#define IOCTL_SET_MONITOR          0x00000007
#define IOCTL_SET_KEYLIST          0x00000008
#define IOCTL_GET_MONITOR          0x00000009

#define TAG_LENGTH     4 
#define VERSION_LENGTH 4
#define IV_LENGTH      16
#define SECTION_SIZE       512




typedef struct _MSG_SEND_TYPE{
	ULONG uSendType ; 
}MSG_SEND_TYPE,*PMSG_SEND_TYPE ;

/**
 * get current process count
 */
typedef struct _MSG_GET_PROCESS_COUNT{
	ULONG uCount ;
}MSG_GET_PROCESS_COUNT,*PMSG_GET_PROCESS_COUNT ;

/**
 * get all process info
 */
typedef struct _MSG_GET_ALL_PROCESS_INFO{
	ULONG uCount ;
	PROCESS_INFO sProcInfo[1] ;
}MSG_GET_ALL_PROCESS_INFO,*PMSG_GET_ALL_PROCESS_INFO ;

/**
 * set process monitor on/off
 */
typedef struct _MSG_SEND_SET_PROCESS_INFO{
	MSG_SEND_TYPE sSendType ;
	PROCESS_INFO sProcInfo ;
}MSG_SEND_SET_PROCESS_INFO,*PMSG_SEND_SET_PROCESS_INFO ;

/**
 * add process info to process list
 */
typedef MSG_SEND_SET_PROCESS_INFO MSG_SEND_ADD_PROCESS_INFO  ;
typedef MSG_SEND_SET_PROCESS_INFO* PMSG_SEND_ADD_PROCESS_INFO ;

/**
 * result of add process info 
 */
#define MGAPI_RESULT_SUCCESS        0x00000000
#define MGAPI_RESULT_ALREADY_EXIST  0x00000001
#define MGAPI_RESULT_INTERNEL_ERROR 0x00000002

typedef struct _MSG_GET_ADD_PROCESS_INFO{
	ULONG uResult ;
}MSG_GET_ADD_PROCESS_INFO,*PMSG_GET_ADD_PROCESS_INFO ;

/**
 * delete specified process info in process list
 */
typedef MSG_SEND_SET_PROCESS_INFO MSG_SEND_DEL_PROCESS_INFO  ;
typedef MSG_SEND_SET_PROCESS_INFO* PMSG_SEND_DEL_PROCESS_INFO ;

/**
 * result of delete process info
 */
#define MGDPI_RESULT_SUCCESS MGAPI_RESULT_SUCCESS        
#define MGDPI_RESULT_NOT_EXIST MGAPI_RESULT_ALREADY_EXIST   
#define MGDPI_RESULT_INTERNEL_ERROR MGAPI_RESULT_INTERNEL_ERROR 

typedef MSG_GET_ADD_PROCESS_INFO  MSG_GET_DEL_PROCESS_INFO ;
typedef MSG_GET_ADD_PROCESS_INFO* PMSG_GET_DEL_PROCESS_INFO ;








#endif