#include "mstp_command_obj.h"


UNSIGNED16  mstp_command_status [] = {
   ENABLED_ATTR,
   IN_PROCESS_ATTR,
   WRITES_SUCCESSFUL_ATTR,
   ALARM_STATE_ATTR,
   NONE_FFFF
};

UNSIGNED16  mstp_command_focus_eng [] = {
  ITEM_REFERENCE_ATTR,
  VERSION_ATTR,
  LAST_EXECUTED_DATE_ATTR,
  LAST_EXECUTED_TIME_ATTR,
  NONE_FFFF
};

UNSIGNED16  mstp_command_focus_bacnet [] = {
   OBJECT_NAME_ATTR,
   USER_NAME_IS_BACNET_OBJ_NAME_ATTR,
   OBJECT_IDENTIFIER_ATTR,
   ACTION_ATTR,
   ACTION_TEXT_ATTR,
   NONE_FFFF
};

UNSIGNED16 mstp_command_cmd_basic [] = {
   SET_STATE_COMMAND,
   ENABLE_COMMAND,
   DISABLE_COMMAND,
   NONE_FFFF
};

UNSIGNED16 mstp_command_action [] = {
  COMMAND_COUNT_ATTR,
  JCI_COMMAND_ACTION_ATTR,
  NONE_FFFF
};

UNSIGNED16 mstp_command_action_adv [] = {
  STATES_TEXT_ATTR,
  NONE_FFFF
};

/* ***********************************************************************
 * View Groups
 * ********************************************************************* */
GROUP_TABLE  mstp_command_cfg_group [] = {
// Group ID
{  OBJECT_GRP,     BASIC_GRP_TYPE,       cmn_cfg_object              },
{  BACNET_GRP,     BACNET_GRP_TYPE,      cmn_cfg_bac                 },
{  NONE_FFFF }
};

GROUP_TABLE  mstp_command_focus_group [] = {
// Group ID                type                 items (attrs/cmds)
{  OBJECT_GRP,             BASIC_GRP_TYPE,      cmn_focus_object     },
{  STATUS_GRP,             BASIC_GRP_TYPE,      mstp_command_status           },
{  ENG_VALUES_GRP,         ADVANCED_GRP_TYPE,   mstp_command_focus_eng        },
{  BACNET_GRP,             BACNET_GRP_TYPE,     mstp_command_focus_bacnet     },
{  NONE_FFFF }
};

GROUP_TABLE mstp_command_action_group [] = {
  { COMMANDS_GRP,              BASIC_GRP_TYPE,       mstp_command_action       },
  { ACTION_TABLE_GRP,          ADVANCED_GRP_TYPE,    mstp_command_action_adv   },
  { NONE_FFFF }
};

GROUP_TABLE mstp_command_cmd_group [] = {
{  NO_GRP,                 BASIC_GRP_TYPE,      mstp_command_cmd_basic },
{  NONE_FFFF }

};


/* ***********************************************************************
 * Views
 * ********************************************************************* */

VIEW_TABLE  mstp_command_view_tbl[] = {
// view id               view type                 d  groups
{  FOCUS_VIEW,           FOCUS_VIEW_TYPE,          1, mstp_command_focus_group   },
{  ACTION_TABLES_VIEW,   FOCUS_VIEW_TYPE,          0, mstp_command_action_group  },
{  CONFIG_VIEW,          CONFIG_VIEW_TYPE,         0, mstp_command_cfg_group     },
{  ACTION_TABLES_VIEW,   CONFIG_VIEW_TYPE,         0, mstp_command_action_group  },
{  COMMAND_VIEW,         COMMAND_VIEW_TYPE,        0, mstp_command_cmd_group     },
{  TREND_VIEW,           EXTENSION_VIEW_TYPE,      0, NULL              },
{  TOTALIZATION_VIEW,    EXTENSION_VIEW_TYPE,      0, NULL              },
{  ALARM_VIEW,           EXTENSION_VIEW_TYPE,      0, NULL              },
{  AVERAGING_VIEW,       EXTENSION_VIEW_TYPE,      0, NULL              },
{  NONE_FFFF }
};
