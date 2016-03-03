#include "common.h"
#include "ctx.h"
#include "lib.h"




/*************************************************************************
    Pool Tags
*************************************************************************/
#define BUFFER_SWAP_TAG     'bdBS'
#define CONTEXT_TAG         'xcBS'
#define NAME_TAG            'mnBS'
#define PRE_2_POST_TAG      'ppBS'

/*************************************************************************
    Local structures
*************************************************************************/
#define MIN_SECTOR_SIZE 0x200

//
//  This is a context structure that is used to pass state from our
//  pre-operation callback to our post-operation callback.
//
typedef struct _PRE_2_POST_CONTEXT {

    PVOLUME_CONTEXT VolCtx;
	PSTREAM_CONTEXT pStreamCtx ;
    PVOID SwappedBuffer;

} PRE_2_POST_CONTEXT, *PPRE_2_POST_CONTEXT;


NPAGED_LOOKASIDE_LIST Pre2PostContextList;


BOOLEAN g_bInitCurKey = FALSE ;
UCHAR g_szCurFileKey[MAX_KEY_LENGTH] = {0} ; 



/*************************************************************************
    Prototypes
*************************************************************************/
NTSTATUS
SetupInstance(
    __in PCFLT_RELATED_OBJECTS FltObjects,
    __in FLT_INSTANCE_SETUP_FLAGS Flags,
    __in DEVICE_TYPE VolumeDeviceType,
    __in FLT_FILESYSTEM_TYPE VolumeFilesystemType
    );

VOID
CleanupContext(
    __in PFLT_CONTEXT Context,
    __in FLT_CONTEXT_TYPE ContextType
    );

NTSTATUS
DriverEntry (
    __in PDRIVER_OBJECT DriverObject,
    __in PUNICODE_STRING RegistryPath
    );

NTSTATUS
DriverExit (
    __in FLT_FILTER_UNLOAD_FLAGS Flags
    );

FLT_PREOP_CALLBACK_STATUS
PreRead(
    __inout PFLT_CALLBACK_DATA Data,
    __in PCFLT_RELATED_OBJECTS FltObjects,
    __deref_out_opt PVOID *CompletionContext
    );

FLT_POSTOP_CALLBACK_STATUS
PostRead(
    __inout PFLT_CALLBACK_DATA Data,
    __in PCFLT_RELATED_OBJECTS FltObjects,
    __in PVOID CompletionContext,
    __in FLT_POST_OPERATION_FLAGS Flags
    );

FLT_POSTOP_CALLBACK_STATUS
PostReadWhenSafe (
    __inout PFLT_CALLBACK_DATA Data,
    __in PCFLT_RELATED_OBJECTS FltObjects,
    __in PVOID CompletionContext,
    __in FLT_POST_OPERATION_FLAGS Flags
    );

FLT_PREOP_CALLBACK_STATUS
PreDirCtrl(
    __inout PFLT_CALLBACK_DATA Data,
    __in PCFLT_RELATED_OBJECTS FltObjects,
    __deref_out_opt PVOID *CompletionContext
    );

FLT_POSTOP_CALLBACK_STATUS
PostDirCtrl(
    __inout PFLT_CALLBACK_DATA Data,
    __in PCFLT_RELATED_OBJECTS FltObjects,
    __in PVOID CompletionContext,
    __in FLT_POST_OPERATION_FLAGS Flags
    );

FLT_POSTOP_CALLBACK_STATUS
PostDirCtrlWhenSafe (
    __inout PFLT_CALLBACK_DATA Data,
    __in PCFLT_RELATED_OBJECTS FltObjects,
    __in PVOID CompletionContext,
    __in FLT_POST_OPERATION_FLAGS Flags
    );

FLT_PREOP_CALLBACK_STATUS
PreWrite(
    __inout PFLT_CALLBACK_DATA Data,
    __in PCFLT_RELATED_OBJECTS FltObjects,
    __deref_out_opt PVOID *CompletionContext
    );

FLT_POSTOP_CALLBACK_STATUS
PostWrite(
    __inout PFLT_CALLBACK_DATA Data,
    __in PCFLT_RELATED_OBJECTS FltObjects,
    __in PVOID CompletionContext,
    __in FLT_POST_OPERATION_FLAGS Flags
    );

VOID
ReadDriverParameters (
    __in PUNICODE_STRING RegistryPath
    );

FLT_PREOP_CALLBACK_STATUS
PreCreate (
    __inout PFLT_CALLBACK_DATA Data,
    __in PCFLT_RELATED_OBJECTS FltObjects,
    __deref_out_opt PVOID *CompletionContext
    );

FLT_POSTOP_CALLBACK_STATUS
PostCreate (
    __inout PFLT_CALLBACK_DATA Data,
    __in PCFLT_RELATED_OBJECTS FltObjects,
    __inout_opt PVOID CompletionContext,
    __in FLT_POST_OPERATION_FLAGS Flags
    );

FLT_PREOP_CALLBACK_STATUS
PreCleanup (
    __inout PFLT_CALLBACK_DATA Data,
    __in PCFLT_RELATED_OBJECTS FltObjects,
    __deref_out_opt PVOID *CompletionContext
    );

FLT_PREOP_CALLBACK_STATUS
PreClose (
    __inout PFLT_CALLBACK_DATA Data,
    __in PCFLT_RELATED_OBJECTS FltObjects,
    __deref_out_opt PVOID *CompletionContext
    );

FLT_PREOP_CALLBACK_STATUS
PreQueryInfo (
    __inout PFLT_CALLBACK_DATA Data,
    __in PCFLT_RELATED_OBJECTS FltObjects,
    __deref_out_opt PVOID *CompletionContext
    );

FLT_POSTOP_CALLBACK_STATUS
PostQueryInfo (
    __inout PFLT_CALLBACK_DATA Data,
    __in PCFLT_RELATED_OBJECTS FltObjects,
    __inout_opt PVOID CompletionContext,
    __in FLT_POST_OPERATION_FLAGS Flags
    );

FLT_PREOP_CALLBACK_STATUS
PreSetInfo (
    __inout PFLT_CALLBACK_DATA Data,
    __in PCFLT_RELATED_OBJECTS FltObjects,
    __deref_out_opt PVOID *CompletionContext
    );

FLT_POSTOP_CALLBACK_STATUS
PostSetInfo (
    __inout PFLT_CALLBACK_DATA Data,
    __in PCFLT_RELATED_OBJECTS FltObjects,
    __inout_opt PVOID CompletionContext,
    __in FLT_POST_OPERATION_FLAGS Flags
    );

//
//  Assign text sections for each routine.
//

#ifdef ALLOC_PRAGMA
#pragma alloc_text(PAGE, SetupInstance)
#pragma alloc_text(PAGE, CleanupContext)
#pragma alloc_text(INIT, DriverEntry)
#pragma alloc_text(INIT, ReadDriverParameters)
#pragma alloc_text(PAGE, DriverExit)
#endif

CONST FLT_OPERATION_REGISTRATION Dispatch_Array[] = {
	
	{ IRP_MJ_CREATE,  
	  FLTFL_OPERATION_REGISTRATION_SKIP_PAGING_IO, 
	  PreCreate,    
	  PostCreate },

	{ IRP_MJ_CLEANUP, 
	  FLTFL_OPERATION_REGISTRATION_SKIP_PAGING_IO, 
	  PreCleanup,   
	  NULL },

	{ IRP_MJ_CLOSE,   
	  0, 
	  PreClose,   
	  NULL },
	{ IRP_MJ_QUERY_INFORMATION, 
	  0, 
	  PreQueryInfo, 
	  PostQueryInfo },

	{ IRP_MJ_SET_INFORMATION,   
	  0, 
	  PreSetInfo,   
	  PostSetInfo },

	{ IRP_MJ_DIRECTORY_CONTROL, 
	  0, 
	  PreDirCtrl,   
	  PostDirCtrl },

    { IRP_MJ_READ,              
	  0, 
	  PreRead,      
	  PostRead },

    { IRP_MJ_WRITE,             
	  0, 
	  PreWrite,     
	  PostWrite }, 

    { IRP_MJ_OPERATION_END }
};


CONST FLT_CONTEXT_REGISTRATION Context_Array[] = {

	{ FLT_VOLUME_CONTEXT, 
	  0, 
	  CleanupContext, 
	  sizeof(VOLUME_CONTEXT), 
	  CONTEXT_TAG },

    { FLT_STREAM_CONTEXT, 
	  0, 
	  NULL, 
	  STREAM_CONTEXT_SIZE,    
	  STREAM_CONTEXT_TAG },

	{ FLT_CONTEXT_END }

};

CONST FLT_REGISTRATION FilterRegistration = {

    sizeof( FLT_REGISTRATION ),         //  Size
    FLT_REGISTRATION_VERSION,           //  Version
    0,                                  //  Flags
    Context_Array,                  //  Context
    Dispatch_Array,                 //  Operation callbacks
    DriverExit,                         //  FilterUnload
    SetupInstance,                  //  InstanceSetup
    NULL,                               //  InstanceQueryTeardown
    NULL,                               //  InstanceTeardownStart
    NULL,                               //  InstanceTeardownComplete
    NULL,                               //  GenerateFileName
    NULL,                               //  GenerateDestinationFileName
    NULL                                //  NormalizeNameComponent
};

/*************************************************************************
    Debug tracing information
*************************************************************************/


ULONG LoggingFlags = 0;             // all disabled by default

#define LOG_PRINT( _logFlag, _string )                              \
    (FlagOn(LoggingFlags,(_logFlag)) ?                              \
        DbgPrint _string  :                                         \
        ((void)0))