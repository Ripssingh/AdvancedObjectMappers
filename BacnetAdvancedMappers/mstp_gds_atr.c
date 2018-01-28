
#include"mstp_gds_obj.h"

#define DEF_REFRESH_TIMER         0
#define DEF_PRIORITY_FOR_WRITING  4

UNSIGNED8  mstp_gds_default [] = {
  0x2e,0x91,0x02,0x2f,      // refresh timer = 2
  0x2e,0x21,0x0f,0x2f,      // priority = 15
  };

ATTRIBUTE_REF_INFO mstpGdsSlaveAttrRefInfo = {
  WRITEABLE_NUMERIC_PROPERTY_LIST, // property filter: all non-internal
                                   //  numeric (including enum)
  NULL                             // object type filter: no restriction
};

LISTOF_INFO mstpGdsSlaveListInfo = {
  ATTRIBUTE_REFERENCE_DATA_TYPE,  // data type of each listof element
  sizeof(ATTRREF),                // size of each listof element
  16,
  &mstpGdsSlaveAttrRefInfo,           // element_info
  NOT_DEFINED,                    // maximum size for the list (none in this case)
  DEFAULT_CATEGORY                // list is not a special category
};

INTEGER_INFO mstpGdsRefreshTimerInfo = {
  NO_CHECK,         //range_ck
  NOT_DEFINED,      //cov_type
  VALUE_GIVEN,      //unit_type
  LIMIT_VALUE,      //limit type, use as a value
  0,                //unused
  0,                //lolmt
  0,                //hiLmt
  NONE,             //cov sensitivity
  MINUTE            //unit
};

LISTOF_INFO mstpJCISlaveListRef = {
  ATTRIBUTE_REFERENCE_DATA_TYPE, // element_type
  sizeof(MSTP_OBJECT_REF),       // element size
  5,                             // elements per block
  NULL,                          // element_info
  NOT_DEFINED,                   // element max
  DEFAULT_CATEGORY               // element category
};

ENUM_INFO mstpGdsSetupEnumInfo = {
  NO_OF_GDS_SETUP_ENUMS,      // emun_size
  VALUE_GIVEN,                // enum_type
  GDS_SETUP_ENUM_SET,         // enum_set
  0                           // not used if size is not redirected
  };

ENUM_INFO mstpGdsPresentValueInfo = {
  NO_OF_GDS_PV_ENUMS,
  VALUE_GIVEN,
  GDS_PV_ENUM_SET,
  0
};

INTEGER_INFO mstpGdsWritePriorityInfo = {
  BETWEEN_LIMITS,            // range_ck
  NOT_DEFINED,               // cov_type
  VALUE_GIVEN,               // unit_type
  LIMIT_VALUE,               // limit type
  0,                         // unused
  7,                         // lowLmt
  16,                        // hiLmt
  NONE,                      // cov_sensitivity
  NO_UNITS,                  // unit
  DEFAULT_CATEGORY           // element category
  };

// Global Data Share object attribute table
// FLAGS ARE:
//   W   attribute is writable
//   Z   priority on write
//   E   execute on write
//   D   default attribute
//   I   internal attribute
//   N   Value NOT required when set
//   C   Configurable
//   A   Save attribute when archived
//   K   LME Output
//   P   LME Input
//   V   Attribute Default is redirected
//   R   the reliable_attr describes this attribute
//   F   allow signup if COV_PMI
//   U   unused

#define O(v) offsetof(MSTP_GDS_OBJ,v)

ATTR_TBL mstp_gds_attr_tbl [] = {
/* Attribute #        Data Type               Memory offset
                                              Ptr extra
                                              default
                                              W Z E D I N C A K P V R F Q O U U U U*/

A2(PRESENT_VALUE_ATTR, ENUM_DATA_TYPE,        O(PresentValue),
                                              &mstpGdsPresentValueInfo,
                                              NO_DEFAULT,
//                                            W Z E D I N C A K P V R F Q O U U U U
                                              0,0,0,1,0,0,1,1,0,0,0,0,1,0,0,0,0,0,0)},

A2(RELIABILITY_ATTR,     ENUM_DATA_TYPE,      O(Reliability),
                                              &cmnRelInfo,
                                              NO_DEFAULT,
//                                            W Z E D I N C A K P V R F Q O U U U U
                                              0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},

A2(SETUP_ATTR, ENUM_DATA_TYPE,                O(Setup),
                                              &mstpGdsSetupEnumInfo,
                                              NO_DEFAULT,
//                                            W Z E D I N C A K P V R F Q O U U U U
                                              0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0)},

A2(MASTER_ATTR,ATTRIBUTE_REFERENCE_DATA_TYPE, O(Master),
                                              &cmnAttrRefInfo,
                                              NO_DEFAULT,
//                                            W Z E D I N C A K P V R F Q O U U U U
                                              1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0)},

A2(JCI_MASTER_ATTR,ATTRIBUTE_REFERENCE_DATA_TYPE, NONE_FFFF,
                                              &cmnAttrRefInfo,
                                              NO_DEFAULT,
//                                            W Z E D I N C A K P V R F Q O U U U U
                                              1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0)},

A2(ALT_MASTER_ATTR,ATTRIBUTE_REFERENCE_DATA_TYPE,O(Alt_Master),
                                              &cmnAttrRefInfo,
                                              NO_DEFAULT,
//                                            W Z E D I N C A K P V R F Q O U U U U
                                              1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0)},

A2(JCI_ALT_MASTER_ATTR,ATTRIBUTE_REFERENCE_DATA_TYPE,NONE_FFFF,
                                              &cmnAttrRefInfo,
                                              NO_DEFAULT,
//                                            W Z E D I N C A K P V R F Q O U U U U
                                              1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0)},

A2(SLAVES_LIST_ATTR,     LISTOF_DATA_TYPE,    O(SlavesList),
                                              &mstpGdsSlaveListInfo,
                                              NO_DEFAULT,
//                                            W Z E D I N C A K P V R F Q O U U U U
                                              1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0)},
A2(JCI_SLAVES_LIST_ATTR,     LISTOF_DATA_TYPE,    NONE_FFFF,
                                              &mstpJCISlaveListRef,
                                              NO_DEFAULT,
//                                            W Z E D I N C A K P V R F Q O U U U U
                                              1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0)},

A2(REFRESH_TIMER_ATTR, USHORT_DATA_TYPE,      O(Refresh_Timer),
                                              &mstpGdsRefreshTimerInfo,
                                              DEF_REFRESH_TIMER,
//                                            W Z E D I N C A K P V R F Q O U U U U
                                              1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0)},

A2(FAILSOFT_ATTR, FLOAT_DATA_TYPE,            O(FailSoft),
                                              NULL,
                                              NO_DEFAULT,
//                                            W Z E D I N C A K P V R F Q O U U U U
                                              1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0)},

A2(PRIORITY_FOR_WRITING_ATTR, BYTE_DATA_TYPE, O(Priority),
                                              &mstpGdsWritePriorityInfo,
                                              DEF_PRIORITY_FOR_WRITING,
//                                            W Z E D I N C A K P V R F Q O B U U U
                                              1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0)},

END_OF_ATTR_TABLE};
