
#include"mstp_sgsl_obj.h"

/* SIGNAL SELECT object class functions */
CLASS_FUNC mstp_sgsl_func [] =
{
   /* class methods              function pointer */
	CLASSREADATTRIBUTE,            mstpSgslClassReadAttribute,
	CLASSWRITEATTRIBUTE,           mstpSgslClassWriteAttribute,
	CLASSDELETE,                   mstpSgslDeleteFunc,
	INVALIDMETHOD
};

/* SGSL object class header */
CLASS_HDR mstp_sgsl_header [] = MSTP_SGSL_HEADER(mstp_sgsl_func);