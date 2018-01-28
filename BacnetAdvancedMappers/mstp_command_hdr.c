#include "mstp_command_obj.h"

#ifndef NO_METHODS
//* mstp command class functions */
CLASS_FUNC mstp_command_func [] = {
  //CLASSWRITEATTRIBUTE,           mstpCommandWriteFunc,
  CLASSREADATTRIBUTE,            mstpCommandReadFunc,
  CLASSDELETE,                   mstpCommandDeleteFunc,
  INVALIDMETHOD
  };
#endif


/* SGSL object class header */
CLASS_HDR mstp_command_header [] = MSTP_COMMAND_HEADER(mstp_command_func);
