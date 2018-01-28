#ifndef GDS_OBJ_H
#define GDS_OBJ_H

#include "mstp_shared_obj.h"

extern VIEW_TABLE mstp_gds_view_tbl[];
extern ATTR_TBL mstp_gds_attr_tbl [];
//extern CMD_PROP_TBL XXXX[];
extern UNSIGNED8 mstp_gds_default[];

// Define a GDS_OBJ object
typedef struct {
  ATTRREF      Master;           // ATTRREF TYPE
  ATTRREF      Alt_Master;       // Alternate Master
  //MSPT_DEV_PROPERTY_REF MasterAttr;
 // MSTP_OBJECT_REF jciSlavelist;
  MSTP_OBJECT_REF jciMaster;
  MSTP_OBJECT_REF jciAltMaster;
  PARM_DATA writtenListOfSlaveRefs;
  PARM_DATA jciMasterRef;
  PARM_DATA jciAltMasterRef;
//  PARM_DATA    Value;            // Last Master Value
//  PARM_DATA    AltMasterValue;   // Last Alternate Master value
//  PARM_DATA    LastReliable;     // Last known reliable value
  FLOAT32      FailSoft;         // Default value configured incase Master and alt master unreliable
  UNSIGNED16   Reliability;      // Reliability
  UNSIGNED16   Refresh_Timer;    // time between automatic refresh
  UNSIGNED16   Setup;            // Enumeration
//  UNSIGNED16   AltMasterReliable;// reliability for alternate Master
  UNSIGNED16   PresentValue;     // This enum specifies whether Master, Alt Master,Fail Soft or Last Reliable value is passed to output
  OID_TYPE     SlavesList;       // LISTOF TYPE
//  TIMER_INDEX  ExecuteTimerIndex;// Index to timer for EXECUTE_METHOD
//  VAR_ARRAY    gwIndexList;
  UNSIGNED8    Priority;         // Priority for writing
  OID_TYPE jciSlavesList;
  } MSTP_GDS_OBJ;



// MSTP GLOBAL DATA object class header macro
#define MSTP_GDS_HEADER(mstp_gds_func)  \
{                             \
  GLOBAL_DATA_MAPPER_CLASS,       /* Class ID                                   */ \
  MAPPER_CLASS,          /* Super Class ID                             */ \
  sizeof(MSTP_GDS_OBJ), /* Size of object's data structure            */ \
  mstp_gds_func,          /* Pointer to Function Table                  */ \
  mstp_gds_attr_tbl,      /* Pointer to Attribute Table                 */ \
  mstp_gds_view_tbl,      /* Pointer to View Info                       */ \
  NULL,       /* Pointer to command property and params     */ \
  mstp_gds_default,       /* Default value pointer                      */ \
  1,                     /* Major Version Number                       */ \
  0,                     /* Minor Version Number                       */ \
  GLOBAL_DATA_CLASS,     /* bacnet Class ID                            */ \
  CC_FIELD_POINT,        /* class category                             */ \
  FALSE,                 /* Default value: not an internal object      */ \
  TRUE,                  /* set user creatable                         */ \
  FALSE,                 /* File Associated Flag                       */ \
  0,                     /* Not Extension                              */ \
  BACNET_EXPOSED_PROG    /* Programmatically exposed on BACnet devce   */ \
}

// function prototypes
void mstpGdsDeleteFunc           (void * NullParms);
void mstpGdsClassReadAttribute (OBJ_INFO *objInfo);
//void mstpGdsWrite (WRITE_INFO *pWriInfo);
//void mstpGdsReadAttribute(OBJ_INFO *pObjInfo);
void mstpGdsClassWriteAttribute(WRITE_DATA * pWriteData);
//void mstpGdsUpdateRefs (void * unused);
void mstpGdsResolveSlaveListRefs(PARM_DATA *pWriteList);
void mstpResolveAttrReadRef(PARM_DATA* prmRefData, ATTRREF inputAttr);
ERROR_STATUS mstpResolveAttrWriteRequest(PARM_DATA* prmWriteData, MSTP_OBJECT_REF* objectAttrRef, PARM_DATA* objectPrmData, UNSIGNED16 attrReqNum);
#endif