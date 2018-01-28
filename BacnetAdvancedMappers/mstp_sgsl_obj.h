#ifndef SGSL_OBJ_H
#define SGSL_OBJ_H

#include "mstp_shared_obj.h"

#define  MIN_INPUTS  1
#define  MAX_INPUTS  12

extern VIEW_TABLE mstp_sgsl_view_tbl[];
extern ATTR_TBL mstp_sgsl_attr_tbl [];
//extern CMD_PROP_TBL XXXX[];
//extern UNSIGNED8 XXXX[];

/*typedef union {
  FLOAT32     AiValue;
  UNSIGNED8   BiValue;
  } POINTVALUE_UNION ;

//Input point info structure
typedef struct {
  POINTVALUE_UNION    PointValue;       //Point Value
  ERROR_STATUS        Status;           //Point Status
  OID_TYPE            Oid;              //Point Oid Reference
  UNSIGNED8           Enabled;          //Point Enabled
  } POINT_STRUCT;*/

/* Define a MSTP_SGSL_OBJ object */
typedef struct
{
  //POINT_STRUCT PointInfo[MAX_INPUTS];   //Input Points Info Array
  ATTRREF      sgslAverage_Output ;     // Average_Output
  ATTRREF      sgslHigh_OR_Output ;     // High_OR_Output
  ATTRREF      sgslLow_AND_Output ;     // Low_AND_Output

  MSTP_OBJECT_REF jciSgslAverage_Output;// JCI Reference Average_Output
  MSTP_OBJECT_REF jciSgslHigh_OR_Output;// JCI Reference High_OR_Output
  MSTP_OBJECT_REF jciSgslLow_AND_Output;// JCI Reference Low_AND_Output

  PARM_DATA prmDataAverage_Output;
  PARM_DATA prmDataHigh_OR_Output;
  PARM_DATA prmDataLow_AND_Output;
  PARM_DATA prmDataInputList;
  //FLOAT32      LastReliableAverage;     //Last Reliable Average Value
  //FLOAT32      LastReliableHighOR;      //Last Reliable High OR Value
  //FLOAT32      LastReliableLowAnd;      //Last Reliable Low/AND value
  FLOAT32      FailSoft;                //Fail Soft value

  UNSIGNED16   sgslPoint_Type ;         // Point_Type - Analog/binary
  UNSIGNED16   sgslReliability;         // ENUM TYPE
  UNSIGNED16   Setup;                   //Enumeration
  UNSIGNED16   PresentValue;            //This enum specifies whether calculated value,
                                        //Fail Soft or Last Reliable value is passed to output
  //Internal
  //ERROR_STATUS AvgOutputStatus;         //Average Output Point Status
  //ERROR_STATUS HighOROutputStatus;      //High/OR Output Point Status
  //ERROR_STATUS LowANDOutputStatus;      //Low/AND Output Point Status

  //UNSIGNED16   AvgOutGWIndex;           //Average GW Index
  //UNSIGNED16   HighOROutGWIndex;        //High/OR GW Index
  //UNSIGNED16   LowANDOutGWIndex;        //Low/AND GW Index

  //Externally Accessible
  OID_TYPE     sgslInput_List ;         // Input_List
  OID_TYPE	   jciSgslInput_List;
} MSTP_SGSL_OBJ;

// MSTP SIGNAL SELECT object class header macro
#define MSTP_SGSL_HEADER(mstp_sgsl_func)  \
{																					 \
  SIGNAL_SELECT_MAPPER_CLASS,       /* Class ID                                   */ \
  MAPPER_CLASS,            			/* Super Class ID                             */ \
  sizeof(MSTP_SGSL_OBJ),   			/* Size of object's data structure            */ \
  mstp_sgsl_func,          			/* Pointer to Function Table                  */ \
  mstp_sgsl_attr_tbl,      			/* Pointer to Attribute Table                 */ \
  mstp_sgsl_view_tbl,      			/* Pointer to View Info                       */ \
  NULL,					   			/* Pointer to command property and params     */ \
  NULL,					   			/* Default value pointer                      */ \
  1,                       			/* Major Version Number                       */ \
  0,                       			/* Minor Version Number                       */ \
  SIGNAL_SELECT_CLASS,     			/* bacnet Class ID                            */ \
  CC_FIELD_POINT,          			/* class category                             */ \
  FALSE,                   			/* Default value: not an internal object      */ \
  TRUE,                    			/* set user creatable                         */ \
  FALSE,                   			/* File Associated Flag                       */ \
  0,                       			/* Not Extension                              */ \
  BACNET_EXPOSED_PROG      			/* Programmatically exposed on BACnet devce   */ \
}

// function prototypes
void mstpSgslDeleteFunc (void *NullParms);
void mstpSgslClassReadAttribute (OBJ_INFO *objInfo);
void mstpSgslClassWriteAttribute(WRITE_DATA * pWriteData);
void mstpResolveRemoteAttrRef(PARM_DATA* prmRefData, ATTRREF inputAttr);
ERROR_STATUS mstpResolveRemoteAttrWriteRequest(PARM_DATA* prmWriteData, MSTP_OBJECT_REF* objectAttrRef, PARM_DATA* objectPrmData, UNSIGNED16 attrReqNum);
void mstpGdsResolveInputListRefs(PARM_DATA *pWriteList);
#endif