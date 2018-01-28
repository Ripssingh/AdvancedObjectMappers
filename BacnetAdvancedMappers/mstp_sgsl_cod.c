
#include"mstp_sgsl_obj.h"

extern LISTOF_INFO mstpSgslAttrbRefListInfo;
extern LISTOF_INFO mstpJCISgslInputListRef;

/*---------------------------------------------------------------------------
Module:
  mstpSgslDeleteFunc
Purpose:
  This is the CLASSDELETE method.  It is used to perform class specific
  operations to delete this object class
Inputs:
  None
Outputs:
  None
---------------------------------------------------------------------------*/
void mstpSgslDeleteFunc (void *NullParms)
{
MSTP_SGSL_OBJ *pObj = stdGetSubclassInstancePtr();

lstOfDelete(&pObj->sgslInput_List);
}


void mstpSgslClassReadAttribute (OBJ_INFO *objInfo)
{
	MSTP_SGSL_OBJ* pObj = stdGetSubclassInstancePtr();
	LISTOF_DATA listData;
	ATTRREF *pRef;
	REFERENCE_DATA refData={0};
	PARM_DATA *pParm;
	objInfo->status = OK;
	switch ( objInfo->attrNum )
	{
	case JCI_AVERAGE_OUTPUT_ATTR:
		mstpResolveRemoteAttrRef(&objInfo->value, pObj->sgslAverage_Output);
		break;
	case JCI_HIGH_OR_ATTR:
		mstpResolveRemoteAttrRef(&objInfo->value, pObj->sgslHigh_OR_Output);
		break;
	case JCI_LOW_AND_ATTR:
		mstpResolveRemoteAttrRef(&objInfo->value, pObj->sgslLow_AND_Output);
		break;
	case JCI_INPUT_LIST_ATTR:
		listData.firstCall = TRUE;
		listData.pOid = &pObj->sgslInput_List;
		listData.pInfo = &mstpSgslAttrbRefListInfo;
		apsNewList(&objInfo->value, lstOfNbrElements(listData.pOid));
		while (pRef = lstOfGetNext(&listData)){
			pParm = NULL;
			pParm = apsNextListElement(&objInfo->value);
			if(!pParm){
				objInfo->status = INIT_ERROR;
				return;
			}
			if (pRef->Oid && pRef->attrNbr && odbGetObjectPointer(pRef->Oid)){
				ATTRREF objRef;
				objRef.attrNbr = pRef->attrNbr;
				objRef.Oid = pRef->Oid;
				mstpResolveRemoteAttrRef(pParm, objRef);
			}
		}
		break;
	default:
		objInfo->status = READ_NOT_HANDLED;
		break;
	}
}

void mstpSgslClassWriteAttribute(WRITE_DATA * pWriData)
{
	MSTP_SGSL_OBJ* pObj = stdGetSubclassInstancePtr();
	UNSIGNED16 totalElements, i;
	LISTOF_DATA lstOfData;
	MSTP_OBJECT_REF *pRef;
	PARM_DATA *pAttrParm, *pRefParm;

	switch (pWriData->attrNum)
	{
	case JCI_AVERAGE_OUTPUT_ATTR:
		pWriData->status = mstpResolveRemoteAttrWriteRequest(&pWriData->value, 
			&pObj->jciSgslAverage_Output, &pObj->prmDataAverage_Output, AVERAGE_OUTPUT_ATTR);
		break;
	case JCI_HIGH_OR_ATTR:
		pWriData->status = mstpResolveRemoteAttrWriteRequest(&pWriData->value, 
			&pObj->jciSgslHigh_OR_Output, &pObj->prmDataHigh_OR_Output, HIGH_OR_ATTR);
		break;
	case JCI_LOW_AND_ATTR:
		pWriData->status = mstpResolveRemoteAttrWriteRequest(&pWriData->value, 
			&pObj->jciSgslLow_AND_Output, &pObj->prmDataLow_AND_Output, LOW_AND_ATTR);
		break;
	case JCI_INPUT_LIST_ATTR:
		totalElements = apsNbrListElements(&pWriData->value);
		pWriData->status = lstOfInitialize(&pObj->jciSgslInput_List, totalElements, &mstpSgslAttrbRefListInfo);
		// if list failed to write - then exit
		if (pWriData->status != OK)
			break;
		lstOfData.firstCall = TRUE;
		lstOfData.pOid = &pObj->jciSgslInput_List;
		lstOfData.pInfo = &mstpJCISgslInputListRef;
		
		// for each reference being written - open connection to it
		// close a connection to any existing reference
		for (i=0; i < totalElements; i++)
		{
			if ((pRefParm = apsGetListElement(&pWriData->value, i, NONE_DATA_TYPE)) && 
				(pAttrParm = apsGetListElement(pRefParm, N_ATTR, ENUM_DATA_TYPE)))
			{
				pRef = NULL;
				pRef = lstOfAddNext(&lstOfData);
				if(pRef){
					pRef->ref.attrNbr = pAttrParm->parmValue.tEnum;
					if (pRef->ref.Oid)
						apsCloseConnection(pRef->ref.Oid);
					pRef->ref.Oid = apsOpenConnection(pRefParm);
					pRef->resolved = FALSE;
				}
			}
		}
		mstpGdsResolveInputListRefs(&pWriData->value);
		break;
	default:
		pWriData->status = WRITE_NOT_HANDLED;
		break;
	
	}
}


void mstpGdsResolveInputListRefs(PARM_DATA *pWriteList)
{
  MSTP_SGSL_OBJ *pObj = stdGetSubclassInstancePtr();
  LISTOF_DATA lstOfData;
  MSTP_OBJECT_REF *pRef;
  BAC_GET_OID_DATA devOid={0};
  BAC_GET_OID_DATA data={0};
  //UNSIGNED8 writeRemote = TRUE;
  UNSIGNED8 update = FALSE;
  OID_TYPE surOid;
  WRITE_ATTR_REQUEST * pReq;
  INVOKEID             invokeId;
  PARM_DATA *pParm, *pParm2;
  UNSIGNED16 writeCount = 0;

  // get schedule obj's device oid for later use
  cdbCallSuperclassMethod(GET_DEVICE_OID, &devOid);

  lstOfData.firstCall = TRUE;
  lstOfData.pOid = &pObj->jciSgslInput_List;
  lstOfData.pInfo = &mstpJCISgslInputListRef;

  // resolve all references to remote BACoids if possible
  while (pRef = lstOfGetNext(&lstOfData))
  {
    if (cdbCallMethod(GET_MAPPED_BACOID, pRef->ref.Oid, &pRef->bacOid) == OK)
    {
      cdbCallMethod(GET_DEVICE_OID, pRef->ref.Oid, &data);
      pRef->devOid.asBacoid32 = data.bacOid;

      //if the reference is on the same box, clear out the optional device portion
      if (bacoidsAreEqual(pRef->devOid.asBacoid32, devOid.bacOid))
      {
        pRef->devOid.asUnsigned32 = 0;
        pRef->devOid.asBacoid32.classid = NO_CLASS;
      }
      pRef->resolved = TRUE;
    }
  }
    

    // Free the prior written value, if any
    apsReleaseParm( &pObj->prmDataInputList );

    apsNewList(&pObj->prmDataInputList, lstOfNbrElements(&pObj->jciSgslInput_List));

    lstOfData.firstCall = TRUE;
    lstOfData.pOid = &pObj->jciSgslInput_List;
    lstOfData.pInfo = &mstpJCISgslInputListRef;

    while (pRef = lstOfGetNext(&lstOfData))
    {
     if (pRef->resolved)
     {
		pParm = NULL;
        pParm = apsNextListElement(&pObj->prmDataInputList);
		if(pParm)
		{
			
			apsNewList(pParm, OBJREF_SIZE);

			 // leave blanks for string reference and func name
			pParm2 = apsNextListElement(pParm);
			pParm2 = apsNextListElement(pParm);

			pParm2 = apsNextListElement(pParm);
			pParm2->dataType = ENUM_DATA_TYPE;
			pParm2->parmValue.tEnum = pRef->ref.attrNbr;
			
			pParm2 = apsNextListElement(pParm);
			pParm2->dataType = BAC_OID_DATA_TYPE;
			pParm2->parmValue.tBacoid32 = pRef->bacOid.asBacoid32;
			
			if(pRef->devOid.asBacoid32.classid != NO_CLASS)
			{
				pParm2 = apsNextListElement(pParm);
				pParm2 = apsNextListElement(pParm);

				pParm2 = apsNextListElement(pParm);
				pParm2->dataType = BAC_OID_DATA_TYPE;
				pParm2->parmValue.tBacoid32 = pRef->devOid.asBacoid32;
			}
		}
	  }
	 else{
		 pParm = NULL;
		 pParm2 = NULL;
		 pParm = apsNextListElement(&pObj->prmDataInputList);
		pParm2 = apsGetListElement(pWriteList, writeCount, NONE_DATA_TYPE);
		if(pParm && pParm2)
			apsCopyParm(pParm,pParm2);
	 }
		writeCount++;
    }

    cdbCallSuperclassMethod(GET_SUR_INFO, &surOid);

    pReq = OSacquire( sizeof(WRITE_ATTR_REQUEST) + (sizeof(WRITE_ATTR_DATA)) );
    pReq->hdr.srcOid = stdGetCurrentOid();
    pReq->hdr.desOid = surOid;
    pReq->hdr.priority = stdGetCurrentPriority();
    pReq->count = 1; 
    pReq->attrWriteList[0].attrNum = INPUT_LIST_ATTR;
    pReq->attrWriteList[0].attrPriority = PRIORITY_DEFAULT;
    pReq->attrWriteList[0].parm_data = pObj->prmDataInputList;

    invokeId = apsWriteAttributes(pReq);  //Send the write out to the FAC
}



void mstpResolveRemoteAttrRef(PARM_DATA* prmRefData, ATTRREF inputAttr)
{
	REFERENCE_DATA refData={0};
	PARM_DATA *pParm, *pParm2, *pParm3;
	BAC_GET_OID_DATA objectData={0};
	BAC_GET_OID_DATA deviceData={0};
	refData.pParm = prmRefData;
	refData.AddBindInfo = TRUE;
	cdbCallMethod(GET_REFERENCE_INFO, inputAttr.Oid, &refData);
	pParm = apsGetListElement(refData.pParm, N_OID, BAC_OID_DATA_TYPE);
	if(pParm)
	  {
		objectData.bacOid = pParm->parmValue.tBacoid32;
	  }
	pParm2 = apsGetListElement(refData.pParm, N_DEVICEID, BAC_OID_DATA_TYPE);
	if(pParm2)
	{
		deviceData.bacOid = pParm2->parmValue.tBacoid32;
	}
	cdbCallSuperclassMethod(FIND_MAPPED_DEVICE, &deviceData);
	cdbCallMethod(FIND_MAPPED_CHILD, deviceData.oid, &objectData);
	cdbCallMethod(GET_REFERENCE_INFO, objectData.oid, &refData);
	pParm3 = apsGetListElement(refData.pParm, N_ATTR, NONE_DATA_TYPE);
	if(pParm3)
	{
		pParm3->dataType = ENUM_DATA_TYPE;
		pParm3->parmValue.tEnum = inputAttr.attrNbr;
	}
}

ERROR_STATUS mstpResolveRemoteAttrWriteRequest(PARM_DATA* prmWriteData, MSTP_OBJECT_REF* objectAttrRef, PARM_DATA* objectPrmData, UNSIGNED16 attrReqNum)
{
	MSTP_OBJECT_REF *pRef;
	PARM_DATA *pAttrParm, *pRefParm;
	ERROR_STATUS runStatus = OK;
	if((pRefParm = prmWriteData) && (pAttrParm = apsGetListElement(pRefParm, N_ATTR, ENUM_DATA_TYPE)))
	{
		BAC_GET_OID_DATA devOid={0};
		BAC_GET_OID_DATA data={0};
		PARM_DATA *pParm, *pParm2;
		OID_TYPE surOid;
		WRITE_ATTR_REQUEST * pReq;
		INVOKEID             invokeId;
		pRef = objectAttrRef;
		if(pRef){
			pRef->ref.attrNbr = pAttrParm->parmValue.tEnum;
			if (pRef->ref.Oid)
				apsCloseConnection(pRef->ref.Oid);
			pRef->ref.Oid = apsOpenConnection(pRefParm);
			pRef->resolved = FALSE;
			if (cdbCallMethod(GET_MAPPED_BACOID, pRef->ref.Oid, &pRef->bacOid) == OK)
			{
			  cdbCallMethod(GET_DEVICE_OID, pRef->ref.Oid, &data);
			  pRef->devOid.asBacoid32 = data.bacOid;

			  //if the reference is on the same box, clear out the optional device portion
			  if (bacoidsAreEqual(pRef->devOid.asBacoid32, devOid.bacOid))
			  {
				pRef->devOid.asUnsigned32 = 0;
				pRef->devOid.asBacoid32.classid = NO_CLASS;
			  }
			  pRef->resolved = TRUE;
			}
			if (pRef->resolved){
				pParm = objectPrmData;
				if(pParm){
					
					apsNewList(pParm, OBJREF_SIZE);

					 // leave blanks for string reference and func name
					pParm2 = apsNextListElement(pParm);
					pParm2 = apsNextListElement(pParm);

					pParm2 = apsNextListElement(pParm);
					pParm2->dataType = ENUM_DATA_TYPE;
					pParm2->parmValue.tEnum = pRef->ref.attrNbr;
					
					pParm2 = apsNextListElement(pParm);
					pParm2->dataType = BAC_OID_DATA_TYPE;
					pParm2->parmValue.tBacoid32 = pRef->bacOid.asBacoid32;
					
					if(pRef->devOid.asBacoid32.classid != NO_CLASS)
					{
						pParm2 = apsNextListElement(pParm);
						pParm2 = apsNextListElement(pParm);

						pParm2 = apsNextListElement(pParm);
						pParm2->dataType = BAC_OID_DATA_TYPE;
						pParm2->parmValue.tBacoid32 = pRef->devOid.asBacoid32;
					}
				}
			}
			else{
				pParm = prmWriteData;
			}
		}

		cdbCallSuperclassMethod(GET_SUR_INFO, &surOid);

		pReq = OSacquire( sizeof(WRITE_ATTR_REQUEST) + (sizeof(WRITE_ATTR_DATA)) );
		pReq->hdr.srcOid = stdGetCurrentOid();
		pReq->hdr.desOid = surOid;
		pReq->hdr.priority = stdGetCurrentPriority();
		pReq->count = 1; 
		pReq->attrWriteList[0].attrNum = attrReqNum;
		pReq->attrWriteList[0].attrPriority = PRIORITY_DEFAULT;
		pReq->attrWriteList[0].parm_data = *pParm;

		invokeId = apsWriteAttributes(pReq);  //Send the write out to the FAC
		return(OK);

	}
	return runStatus;
}