#include"mstp_gds_obj.h"

// Global Data Share object class functions
CLASS_FUNC mstp_gds_func [] =
{ /* class methods               function pointer */
   CLASSREADATTRIBUTE,            mstpGdsClassReadAttribute,
   CLASSWRITEATTRIBUTE,           mstpGdsClassWriteAttribute,
   CLASSDELETE,                   mstpGdsDeleteFunc,
   INVALIDMETHOD
};


// MSTP GDS object class header
CLASS_HDR mstp_gds_header [] = MSTP_GDS_HEADER(mstp_gds_func);