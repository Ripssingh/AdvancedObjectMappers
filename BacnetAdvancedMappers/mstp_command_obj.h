
#ifndef MSTP_COMMAND_OBJ_H
#define MSTP_COMMAND_OBJ_H

#include "mstp_shared_obj.h"


extern VIEW_TABLE mstp_command_view_tbl[];
extern ATTR_TBL mstp_command_attr_tbl [];
extern CMD_PROP_TBL mstp_command_cmd_tbl[];
extern UNSIGNED8 mstp_command_default[];

#ifndef SKIPEXTERN
extern LISTOF_INFO mstpCommandTableInfo;
extern LISTOF_INFO mstpCommandSlaveInfo;
extern LISTOF_INFO mstpCommandJCIActionListInfo;
extern LISTOF_INFO mstpCommandJCIActionSequenceListInfo;
extern LISTOF_INFO mstpCommandJCIActionSequenceListInfo;
#endif

// tzz copied this code from strfuncs.h from base project
#ifndef DICT_STRLEN
#define DICT_STRLEN		128 // Defines the maximum length of a string in the dictionary.
#endif

#define REFERENCE_OFF_BOX  0
#define REFERENCE_ON_BOX   1

#define SEND_NEXT_ACTION_COMMAND    CMDNEXTSLAVE

#define MAX_VALUE_TEXT_LENGTH    10

// Define a MSTP_COMMAND_OBJ object
typedef struct
{
  DATE_PARM       ExeDate;                // DATE_DATA_TYPE
  TIME_PARM       ExeTime;                // TIME_DATA_TYPE
  VAR_ARRAY       attrRegList;            // Element Index handle for the registered attributes
  UNSIGNED16      actionCount;            // Number of actions in the list.
  UNSIGNED16      StatesText;             // ENUM_DATA_TYPE
  OID_TYPE        commandedActionSequenceOid; // the current JCIActionList list that is executing
  OID_TYPE        JCIActionList;
  UNSIGNED16      ActionTableIndex;
  TIMER_INDEX     SendNextActionCommandTimerIndex;  //index to timer for SEND_NEXT_ACTION_COMMAND (CMDNEXTSLAVE)
  INVOKEID        lastWriteAttributeInvokeId;
  UNSIGNED16      Value;                  //USHORT_DATA_TYPE
  UNSIGNED8       inProcess;              //BOOL_DATA_TYPE
  UNSIGNED8       allWritesSuccessful;    //BOOL_DATA_TYPE
  UNSIGNED8       anyWriteFailureFlag;
  UNSIGNED8       useGuaranteedWriteFlag;
  UNSIGNED8       ValueDefined;
  } MSTP_COMMAND_OBJ;

typedef struct {
  ATTRREF              attrRef;
  UNSIGNED32           post_delay;
  UNSIGNED16           valueDataType;
  UNSIGNED16           valueUnits;
  UNSIGNED16           priority;
  UNSIGNED16           errorStatus;
  UNSIGNED8            quit_on_failure;
  UNSIGNED8            write_successful;
  TCHAR                valueText[MAX_VALUE_TEXT_LENGTH + 1]; //STRING_DATA_TYPE
} MSTP_COMMAND_JCI_ACTION_COMMANDS;

typedef struct {
  PARM_DATA            value;
  UNSIGNED32           post_delay;
  BAC_OID_CONVERT      devBACoid;
  BAC_OID_CONVERT      objBACoid;
  UNSIGNED16           attrID;
  UNSIGNED16           arrayIndex;
  UNSIGNED16           priority;
  UNSIGNED8            quit_on_failure;
  UNSIGNED8            write_successful;
  UNSIGNED8            devOidPresent;
  UNSIGNED8            useArrayIndex;
  UNSIGNED8            usePriority;
  UNSIGNED8            usePostDelay;
} MSTP_COMMAND_ACTION_COMMANDS;


// MSTP COMMAND object class header macro
#define MSTP_COMMAND_HEADER(mstp_command_func)  \
{                             \
  COMMAND_MAPPER_CLASS,       /* Class ID                                   */ \
  MAPPER_CLASS,          /* Super Class ID                             */ \
  sizeof(MSTP_COMMAND_OBJ), /* Size of object's data structure            */ \
  mstp_command_func,          /* Pointer to Function Table                  */ \
  mstp_command_attr_tbl,      /* Pointer to Attribute Table                 */ \
  mstp_command_view_tbl,      /* Pointer to View Info                       */ \
  mstp_command_cmd_tbl,       /* Pointer to command property and params     */ \
  mstp_command_default,       /* Default value pointer                      */ \
  1,                     /* Major Version Number                       */ \
  0,                     /* Minor Version Number                       */ \
  BAC_COMMAND_CLASS,     /* bacnet Class ID                            */ \
  CC_FIELD_POINT,        /* class category                             */ \
  FALSE,                 /* Default value: not an internal object      */ \
  TRUE,                  /* set user creatable                         */ \
  FALSE,                 /* File Associated Flag                       */ \
  0,                     /* Not Extension                              */ \
  BACNET_EXPOSED_PROG    /* Programmatically exposed on BACnet devce   */ \
}
// funtion prototypes
void mstpCommandWriteFunc(WRITE_DATA * pWriData);
void mstpCommandReadFunc(OBJ_INFO * objInfo);
void mstpCommandBuildActionSequence(OID_TYPE * pSourceActionSequence, PARM_DATA * pDestActionSequence);
void mstpCommandExecuteFunc(CLASSEXECUTE_DATA * classExecuteData);
void mstpCommandDeleteFunc(ERROR_STATUS * status);
void mstpCommandUnregisterAnyGuaranteedWrites(void);
void mstpCommandResolveActionTable(OID_TYPE * pSourceActionSequence, PARM_DATA * pDestActionSequence);
//Delete this function and bac_command_osatof_CE.c after OSatof is added for MSEA CE in core assets
#ifdef _WIN32_WCE
FLOAT32 OSatof(TCHAR *string);
#endif


#endif
