
#include"mstp_sgsl_obj.h"


LISTOF_INFO mstpSgslAttrbRefListInfo = {
   ATTRIBUTE_REFERENCE_DATA_TYPE,            // element_type
   sizeof(ATTRREF),                          // element_size
   5,                                        // elements_per_block
   NULL,                                         // ptr to property info of listof elements
   MAX_INPUTS,                               // Maximum number of Input
   DEFAULT_CATEGORY                          // Category Information
 };

LISTOF_INFO mstpJCISgslInputListRef = {
  ATTRIBUTE_REFERENCE_DATA_TYPE, // element_type
  sizeof(MSTP_OBJECT_REF),       // element size
  5,                             // elements per block
  NULL,                          // element_info
  MAX_INPUTS,                   // element max
  DEFAULT_CATEGORY               // element category
};

ENUM_INFO mstpSgslPointType = {
   NO_OF_SGSL_POINT_TYPE_ENUMS,  // enum_size
   VALUE_GIVEN,                  // enum_type
   SGSL_POINT_TYPE_ENUM_SET,     // enum_set
   0                             // not used
 };

//Since the enum set used in GDS is same as SGSL, it is reused here.
ENUM_INFO mstpSgslSetupEnumInfo = {
  NO_OF_SGSL_SETUP_ENUMS,      // emun_size
  VALUE_GIVEN,                // enum_type
  SGSL_SETUP_ENUM_SET,         // enum_set
  0                           // not used if size is not redirected
  };

//Need to be changed, once it  compiles properly
ENUM_INFO mstpSgslPresentValueInfo = {
   NO_OF_SGSL_PV_ENUMS,
   VALUE_GIVEN,
   SGSL_PV_ENUM_SET,
   0
};



// SIGNAL SELECT object attribute table
// FLAGS ARE:
//   W   attribute is writable
//   Z   priority on write
//   E   execute on write
//   D   default attribute
//   I   internal attribute
//   N   Value NOT required when set
//   C   Configurable
//   A   Save attribute when archived
//   K   key attribute
//   P   input from other objects
//   V   Attribute Default is redirected
//   R   the reliable_attr describes this attribute
//   F   allow signup if COV_PMI
//   Q   BACnet Required attribute
//   O   BACnet Optional attribute
//   U   unused

#define O(v) offsetof(MSTP_SGSL_OBJ,v)


ATTR_TBL mstp_sgsl_attr_tbl [] = {
/* Attribute #        Data Type                  Memory offset
                                                 Ptr extra
                                                 default
                                                 W Z E D I N C A K P V R F Q O U U U U*/
A2(INPUT_LIST_ATTR, LISTOF_DATA_TYPE,            O(sgslInput_List),
                                                 &mstpSgslAttrbRefListInfo,
                                                 NO_DEFAULT,
//                                               W Z E D I N C A K P V R F Q O U U U U
                                                 1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0)},

A2(JCI_INPUT_LIST_ATTR, LISTOF_DATA_TYPE,        NONE_FFFF,
                                                 &mstpJCISgslInputListRef,
                                                 NO_DEFAULT,
//                                               W Z E D I N C A K P V R F Q O U U U U
                                                 1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0)},

A2(AVERAGE_OUTPUT_ATTR,ATTRIBUTE_REFERENCE_DATA_TYPE, O(sgslAverage_Output),
                                                 NULL,
                                                 NO_DEFAULT,
//                                               W Z E D I N C A K P V R F Q O U U U U
                                                 1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0)},

A2(JCI_AVERAGE_OUTPUT_ATTR,ATTRIBUTE_REFERENCE_DATA_TYPE, NONE_FFFF,
                                                 NULL,
                                                 NO_DEFAULT,
//                                               W Z E D I N C A K P V R F Q O U U U U
                                                 1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0)},

A2(HIGH_OR_ATTR, ATTRIBUTE_REFERENCE_DATA_TYPE,  O(sgslHigh_OR_Output),
                                                 NULL,
                                                 NO_DEFAULT,
//                                               W Z E D I N C A K P V R F Q O U U U U
                                                 1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0)},

A2(JCI_HIGH_OR_ATTR, ATTRIBUTE_REFERENCE_DATA_TYPE,  NONE_FFFF,
                                                 NULL,
                                                 NO_DEFAULT,
//                                               W Z E D I N C A K P V R F Q O U U U U
                                                 1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0)},

A2(LOW_AND_ATTR, ATTRIBUTE_REFERENCE_DATA_TYPE,  O(sgslLow_AND_Output),
                                                 NULL,
                                                 NO_DEFAULT,
//                                               W Z E D I N C A K P V R F Q O U U U U
                                                 1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0)},

A2(JCI_LOW_AND_ATTR, ATTRIBUTE_REFERENCE_DATA_TYPE,  NONE_FFFF,
                                                 NULL,
                                                 NO_DEFAULT,
//                                               W Z E D I N C A K P V R F Q O U U U U
                                                 1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0)},

A2(POINT_TYPE_ATTR, ENUM_DATA_TYPE,              O(sgslPoint_Type),
                                                 &mstpSgslPointType,
                                                 NO_DEFAULT,
//                                               W Z E D I N C A K P V R F Q O U U U U
                                                 1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0)},

A2(RELIABILITY_ATTR, ENUM_DATA_TYPE,             O(sgslReliability),
                                                 &cmnRelInfo,
                                                 NO_DEFAULT,
//                                               W Z E D I N C A K P V R F Q O U U U U
                                                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},

A2(FAILSOFT_ATTR,    FLOAT_DATA_TYPE,            O(FailSoft),
                                                 NULL,
                                                 NO_DEFAULT,
//                                               W Z E D I N C A K P V R F Q O U U U U
                                                 1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0)},

A2(SETUP_ATTR, ENUM_DATA_TYPE,                   O(Setup),
                                                 &mstpSgslSetupEnumInfo,
                                                 NO_DEFAULT,
//                                               W Z E D I N C A K P V R F Q O U U U U
                                                 0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0)},

A2(PRESENT_VALUE_ATTR, ENUM_DATA_TYPE,           O(PresentValue),
                                                 &mstpSgslPresentValueInfo,
                                                 NO_DEFAULT,
//                                               W Z E D I N C A K P V R F Q O U U U U
                                                 0,0,0,1,0,0,1,1,0,0,0,0,1,0,0,0,0,0,0)},

END_OF_ATTR_TABLE};
