
#include"mstp_sgsl_obj.h"

UNSIGNED16  mstp_sgsl_focus_status [] = {
// Attribute numbers
   ENABLED_ATTR,
   RELIABILITY_ATTR,
   NONE_FFFF
};

UNSIGNED16  mstp_sgsl_focus_engval [] = {
   ITEM_REFERENCE_ATTR,
   VERSION_ATTR,
   JCI_INPUT_LIST_ATTR,
   JCI_AVERAGE_OUTPUT_ATTR,
   JCI_HIGH_OR_ATTR,
   JCI_LOW_AND_ATTR,
   POINT_TYPE_ATTR,
   FAILSOFT_ATTR,
   SETUP_ATTR,
   NONE_FFFF
};

UNSIGNED16  mstp_sgsl_cfg_engval [] = {
   JCI_INPUT_LIST_ATTR,
   JCI_AVERAGE_OUTPUT_ATTR,
   JCI_HIGH_OR_ATTR,
   JCI_LOW_AND_ATTR,
   POINT_TYPE_ATTR,
   FAILSOFT_ATTR,
   SETUP_ATTR,
   NONE_FFFF
};

UNSIGNED16  mstp_sgsl_cmd_basic [] = {
   ENABLE_COMMAND,
   DISABLE_COMMAND,
   NONE_FFFF
};

//*********************************************************************
// View Groups
//*********************************************************************
GROUP_TABLE  mstp_sgsl_focus_group [] = {
// Group ID                type                items (attrs/cmds)
{  OBJECT_GRP,             BASIC_GRP_TYPE,      cmn_focus_object   },
{  STATUS_GRP,             BASIC_GRP_TYPE,      mstp_sgsl_focus_status  },
{  ENG_VALUES_GRP,         ADVANCED_GRP_TYPE,   mstp_sgsl_focus_engval  },
{  EXECUTION_GRP,          ADVANCED_GRP_TYPE,   cmn_execution      },
{  BACNET_GRP,             BACNET_GRP_TYPE,     cmn_focus_bac  },
{  NONE_FFFF }
};

GROUP_TABLE  mstp_sgsl_cnfg_group [] = {
// Group ID                type                 items (attrs/cmds)
{  OBJECT_GRP,             BASIC_GRP_TYPE,      cmn_cfg_object_enabled  },
{  ENG_VALUES_GRP,         BASIC_GRP_TYPE,      mstp_sgsl_cfg_engval    },
{  EXECUTION_GRP,          ADVANCED_GRP_TYPE,   cmn_execution           },
{  BACNET_GRP,             BACNET_GRP_TYPE,     cmn_cfg_bac             },
{  NONE_FFFF }
};

GROUP_TABLE  mstp_sgsl_cmd_group [] = {
// Group ID      type                  items (attrs/cmds)
{  NO_GRP,       BASIC_GRP_TYPE,       mstp_sgsl_cfg_engval    },
{  NONE_FFFF }
};


//*********************************************************************
// Views
//*********************************************************************
VIEW_TABLE  mstp_sgsl_view_tbl [] = {
// view id            view type                 d  groups
{  FOCUS_VIEW,        FOCUS_VIEW_TYPE,          1, mstp_sgsl_focus_group },
{  CONFIG_VIEW,       CONFIG_VIEW_TYPE,         0, mstp_sgsl_cnfg_group  },
{  COMMAND_VIEW,      COMMAND_VIEW_TYPE,        0, mstp_sgsl_cmd_group   },
{  TREND_VIEW,        EXTENSION_VIEW_TYPE,      0, NULL             	 },
{  TOTALIZATION_VIEW, EXTENSION_VIEW_TYPE,      0, NULL             	 },
{  ALARM_VIEW,        EXTENSION_VIEW_TYPE,      0, NULL             	 },
{  AVERAGING_VIEW,    EXTENSION_VIEW_TYPE,      0, NULL             	 },
{  NONE_FFFF }
};

