#include "mstp_command_obj.h"

//Indexes into the default value array
#define DEF_STATES_TEXT          0
#define DEF_COMMAND_COUNT        5

//mstpCommand default values
UNSIGNED8 mstp_command_default [] =
{ 0x2e,0x92,0x06,0x22,0x2f,         // Byte Offset 0, DEF_STATES_TEXT = 1570 (ACTIONS_ENUM_SET)
  0x2e,0x21,0x00,0x2f,              // Byte Offset 5, Default Number Of States = 0
};


ENUM_INFO mstpCommandValueInfo = {
  ATTR_REF,             // size
  ATTR_REF,             // enum_type
  STATES_TEXT_ATTR,     // enum_set
  COMMAND_COUNT_ATTR    // not used when size is not redirected
  };

ENUM_INFO mstpCommandStateTextInfo = {
  NO_CHECK,                         // size
  VALUE_GIVEN,                      // enum_type
  MULTISTATE_ENUM_SET,              // enum_set
  0,                                // not used when size is not redirected
  MULTISTATE_STATES_TEXT_CATEGORY   // category
  };

ENUM_INFO mstpCommandValueDataTypeEnumInfo = {
  3,                                // emun_size
  VALUE_GIVEN,                      // enum_type
  TYPE_OF_SCHEDULE_ENUM_SET,
  0,                                // not used if size is not redirected
  DEFAULT_CATEGORY
};

ENUM_INFO mstpCommandErrorStatusEnumInfo = {
  NO_CHECK,                   // emun_size
  VALUE_GIVEN,                // enum_type
  STATUS_ENUM_SET,            // enum_set
  0,                          // not used if size is not redirected
  DEFAULT_CATEGORY,
  NOT_RECOMMENDED
};

STRING_INFO mstpCommandValueTextInfo = {
  STR_STORE(MAX_VALUE_TEXT_LENGTH),// max string size
  MULTISTATE_STATES_TEXT_CATEGORY      // category
  };

INTEGER_INFO mstpCommandPostDelayInfo = {
  BETWEEN_LIMITS,            // range_ck
  NOT_DEFINED,               // cov_type
  VALUE_GIVEN,               // unit_type
  LIMIT_VALUE,               // limit type
  0,                         // unused
  0,                         // lowLmt
  86400,                     // hiLmt = 24*60*60 seconds = 24 hours;
  NONE,                      // cov_sensitivity
  SECOND                     // unit
  };

STRUCTURE_INFO(8) mstpCommandJCIActionCommandInfo = {
  8,
  COMMAND_REFERENCE_STRUCT_CATEGORY,

  ELENAM_AI_ATTRREF_TYPE,
  ATTRIBUTE_REFERENCE_DATA_TYPE,
  offsetof(MSTP_COMMAND_JCI_ACTION_COMMANDS,attrRef),
  NULL,

  ELENAM_VALUE,
  STRING_DATA_TYPE,
  offsetof(MSTP_COMMAND_JCI_ACTION_COMMANDS,valueText),
  &mstpCommandValueTextInfo,

  ELENAM_DATA_TYPE,
  ENUM_DATA_TYPE,
  offsetof(MSTP_COMMAND_JCI_ACTION_COMMANDS,valueDataType),
  &mstpCommandValueDataTypeEnumInfo,

  ELENAM_PRIORITY,
  ENUM_DATA_TYPE,
  offsetof(MSTP_COMMAND_JCI_ACTION_COMMANDS,priority),
  &cmnPriInfo,

  ELENAM_POST_DELAY,
  ULONG_DATA_TYPE,
  offsetof(MSTP_COMMAND_JCI_ACTION_COMMANDS,post_delay),
  &mstpCommandPostDelayInfo,

  ELENAM_QUIT_ON_FAILURE,
  BOOL_DATA_TYPE,
  offsetof(MSTP_COMMAND_JCI_ACTION_COMMANDS,quit_on_failure),
  NULL,

  ELENAM_WRITE_SUCESSFUL,
  BOOL_DATA_TYPE,
  offsetof(MSTP_COMMAND_JCI_ACTION_COMMANDS,write_successful),
  NULL,

  ELENAM_STATUS,
  ENUM_DATA_TYPE,
  offsetof(MSTP_COMMAND_JCI_ACTION_COMMANDS,errorStatus),
  &mstpCommandErrorStatusEnumInfo,

};

LISTOF_INFO mstpCommandJCIActionSequenceListInfo = {
  STRUCT_DATA_TYPE,                        // element_type
  sizeof(MSTP_COMMAND_JCI_ACTION_COMMANDS),
  3,
  &mstpCommandJCIActionCommandInfo,                // element_info
  NOT_DEFINED,                             // element_max
  TABLE_CATEGORY
};

LISTOF_INFO mstpCommandJCIActionListInfo = {
  LISTOF_DATA_TYPE,                        // element_type
  sizeof(OID_TYPE),                        // element size
  5,                                       // elements per block
                                           // - typical number of elements you would find
                                           // in the action list
  &mstpCommandJCIActionSequenceListInfo,           // element_info
  MAX_NUMBER_OF_STATES,                    // element_max
  TABLE_CATEGORY
};

//-----------------------------------------------------------------------------

STRUCTURE_INFO(13) mstpCommandActionCommandInfo = {
  13,
  COMMAND_REFERENCE_STRUCT_CATEGORY,

  ELENAM_DEVID_DEFINED,
  BOOL_DATA_TYPE,
  offsetof(MSTP_COMMAND_ACTION_COMMANDS,devOidPresent),
  NULL,

  ELENAM_DEVICE_ID,                        // optional
  BAC_OID_DATA_TYPE,
  offsetof(MSTP_COMMAND_ACTION_COMMANDS,devBACoid),
  NULL,

  ELENAM_OBJ_ID,
  BAC_OID_DATA_TYPE,
  offsetof(MSTP_COMMAND_ACTION_COMMANDS,objBACoid),
  NULL,

  ELENAM_ATTRIBUTE_ID,
  ENUM_DATA_TYPE,
  offsetof(MSTP_COMMAND_ACTION_COMMANDS,attrID),
  &cmnAttrInfo,

  ELENAM_ARRAY_INDX_DEFINED,
  BOOL_DATA_TYPE,
  offsetof(MSTP_COMMAND_ACTION_COMMANDS,useArrayIndex),
  NULL,

  ELENAM_ARRAY_INDEX,                      // conditional
  USHORT_DATA_TYPE,
  offsetof(MSTP_COMMAND_ACTION_COMMANDS,arrayIndex),
  NULL,

  ELENAM_VALUE,
  NUMERIC_DATA_TYPE,
  offsetof(MSTP_COMMAND_ACTION_COMMANDS,value),
  NULL,

  ELENAM_PRIORITY_DEFINED,
  BOOL_DATA_TYPE,
  offsetof(MSTP_COMMAND_ACTION_COMMANDS,usePriority),
  NULL,

  ELENAM_PRIORITY,
  BYTE_DATA_TYPE,
  offsetof(MSTP_COMMAND_ACTION_COMMANDS,priority),
  NULL,

  ELENAM_POST_DELAY_DEFINED,
  BOOL_DATA_TYPE,
  offsetof(MSTP_COMMAND_ACTION_COMMANDS,usePostDelay),
  &mstpCommandPostDelayInfo,

  ELENAM_POST_DELAY,
  ULONG_DATA_TYPE,
  offsetof(MSTP_COMMAND_ACTION_COMMANDS,post_delay),
  NULL,

  ELENAM_QUIT_ON_FAILURE,
  BOOL_DATA_TYPE,
  offsetof(MSTP_COMMAND_ACTION_COMMANDS,quit_on_failure),
  NULL,

  ELENAM_WRITE_SUCESSFUL,
  BOOL_DATA_TYPE,
  offsetof(MSTP_COMMAND_ACTION_COMMANDS,write_successful),
  NULL,

};

LISTOF_INFO mstpCommandActionSequenceListInfo = {
  STRUCT_DATA_TYPE,                        // element_type
  sizeof(MSTP_COMMAND_ACTION_COMMANDS),
  3,
  &mstpCommandActionCommandInfo,                   // element_info
  NOT_DEFINED,                             // element_max
  TABLE_CATEGORY
};

LISTOF_INFO mstpCommandActionListInfo = {
  LISTOF_DATA_TYPE,                        // element_type
  sizeof(OID_TYPE),                        // element size
  5,                                       // elements per block
                                           // - typical number of elements you would find
                                           // in the action list
  &mstpCommandActionSequenceListInfo,              // element_info
  MAX_NUMBER_OF_STATES,                    // element_max
  TABLE_CATEGORY
};

//-----------------------------------------------------------------------------

ENUM_INFO mstpCommandActionValueInfo = {
  NO_CHECK,          // size
  VALUE_GIVEN,                   // enum_type
  MULTISTATE_ENUM_SET,           // enum_set
  0                              // enum_size_attr
  };

LISTOF_INFO mstpCommandStateTextStrLstInfo = {
   STRING_DATA_TYPE,               // element_type
   INACTIVE_ACTIVE_TEXT_LENGTH,    // element size in bytes (Largest String?)
   4,                              // elements per block
   &cmnActiveInactiveTextSize,     // element info
   NOT_DEFINED,                    // max number of elements
   DEFAULT_CATEGORY                // special category
   };

ENUM_INFO mstpActionValueInfo = {
  ATTR_REF,                                // size
  ATTR_REF,                                // enum_type
  STATES_TEXT_ATTR,                        // attr # when redirected
  COMMAND_COUNT_ATTR                       // not used if size not redirected
  };



// MSTP COMMAND attribute table
// FLAGS ARE:
//   W   attribute is writeable
//   Z   prioritized write
//   E   execute when written
//   D   default attribute
//   I   internal attribute
//   N   Value Not Required
//   C   Configurable
//   A   Save attribute when archived
//   K   Key attribute
//   P   Input attribute
//   V   redirect default value to attribute
//   R   the reliable_attr describes this attribute
//   F   allow signup if COV_PMI
//   Q   BACnet Required
//   O   BACnet Optional
//   B   BACnet Array
//   U   Unused

#define O(v) offsetof(MSTP_COMMAND_OBJ,v)

ATTR_TBL mstp_command_attr_tbl [] = {
/* Attribute #        Data Type           Memory offset
                                          Ptr extra
                                          default
                                          W Z E D I N C A K P V R F Q O B U U U*/

A2(PRESENT_VALUE_ATTR,        ENUM_DATA_TYPE,
                              O(Value),
                              &mstpActionValueInfo,
                              NO_DEFAULT,
//                            W Z E D I N C A K P V R F Q O B U U U
                              1,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0)},

A2(JCI_ACTION_ATTR,           LISTOF_DATA_TYPE,
                              O(JCIActionList),
                              &mstpCommandJCIActionListInfo,
                              NO_DEFAULT,
//                            W Z E D I N C A K P V R F Q O B U U U
                              1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0)},

A2(JCI_COMMAND_ACTION_ATTR,           LISTOF_DATA_TYPE,
                              NONE_FFFF,
                              &mstpCommandJCIActionListInfo,
                              NO_DEFAULT,
//                            W Z E D I N C A K P V R F Q O B U U U
                              1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0)},

A2(ACTION_ATTR,               LISTOF_DATA_TYPE,
                              NONE_FFFF,
                              &mstpCommandActionListInfo,
                              NO_DEFAULT,
//                            W Z E D I N C A K P V R F Q O B U U U
                              0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0)},

A2(IN_PROCESS_ATTR,           BOOL_DATA_TYPE,
                              O(inProcess),
                              NULL,
                              NO_DEFAULT,
//                            W Z E D I N C A K P V R F Q O B U U U
                              0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0)},

A2(WRITES_SUCCESSFUL_ATTR,    BOOL_DATA_TYPE,
                              O(allWritesSuccessful),
                              NULL,
                              NO_DEFAULT,
//                            W Z E D I N C A K P V R F Q O B U U U
                              0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0)},

A2(ACTION_TEXT_ATTR,          LISTOF_DATA_TYPE,
                              NONE_FFFF,
                              &mstpCommandStateTextStrLstInfo,
                              NO_DEFAULT,
//                            W Z E D I N C A K P V R F Q O B U U U
                              0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0)},

A2(COMMAND_COUNT_ATTR,        USHORT_DATA_TYPE,
                              O(actionCount),
                              NULL,
                              DEF_COMMAND_COUNT,
//                            W Z E D I N C A K P V R F Q O B U U U
                              0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},

A2(STATES_TEXT_ATTR,          ENUM_DATA_TYPE,
                              O(StatesText),
                              &mstpCommandStateTextInfo,
                              DEF_STATES_TEXT,
//                            W Z E D I N C A K P V R F Q O B U U U
                              1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0)},

A2(LAST_EXECUTED_DATE_ATTR,   DATE_DATA_TYPE,
                              O(ExeDate),
                              NULL,
                              NO_DEFAULT,
//                            W Z E D I N C A K P V R F Q O B U U U
                              0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0)},

A2(LAST_EXECUTED_TIME_ATTR,   TIME_DATA_TYPE,
                              O(ExeTime),
                              NULL,
                              NO_DEFAULT,
//                            W Z E D I N C A K P V R F Q O B U U U
                              0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0)},


END_OF_ATTR_TABLE};

// Parameter for Override Command
CMD_PARM_TBL mstpCommandCmdValueParm = {
  VALUE_CMDPARM,                 // parmId
  ENUM_DATA_TYPE,                // dataType
  PARM_REDIRECTED,               // defaultType
  0,                             // unused
  PRESENT_VALUE_ATTR,            // defaultIndex
  &mstpCommandValueInfo          // uniqueParmPtr
  };


CMD_PARM_TBL mstpMultiActionValueParm = {
  VALUE_CMDPARM,                 // parmId
  ENUM_DATA_TYPE,                // dataType
  PARM_REDIRECTED,               // defaultType
  0,                             // unused
  PRESENT_VALUE_ATTR,            // defaultIndex (attribute number)
  &mstpActionValueInfo               // uniqueParmPtr
};

// Command Property table FLAGS ARE:
//   I   internal command
//   An  associated attribute as Name (redirection)
//   Aw  associated attribute as Write
//   D   default command (first selected)
//   P   Accept Priority?
//   U   Unused

CMD_PROP_TBL mstp_command_cmd_tbl [] = {
//Command id
// Command method
//   numberOfParms
//      accessLevel
//         AssocAttr
//            AssocVal
//               Parm info
//                  I AnAwD P U U U U
C(SET_STATE_COMMAND,
  0,
     1,
        OPERATE_ACCESS,
           PRESENT_VALUE_ATTR,
              0,
                 &mstpMultiActionValueParm,
                    0,0,1,1,1,1,0,0,0)},

C(RESTORE_CONTROLLER_STATES_TEXT_COMMAND,
  0,
     0,
        OPERATE_ACCESS,
           USER_SELECTED_STATES_TEXT_ATTR,
              FALSE,
                 NULL,
                    0,0,1,0,0,0,0,0,0)},

END_OF_CMD_TABLE};

