#ifndef MESSAGEDEFINITIONS_H_INCLUDED
#define MESSAGEDEFINITIONS_H_INCLUDED

#include <string>

using namespace std;

const string CONFIG_MESSAGE_ID              = "00";
const string GPIO_MESSAGE_ID                = "01";
const string QUERY_MESSAGE_ID               = "02";

const string CONFIG_MESSAGE_QUIT            = "00";
const string CONFIG_MESSAGE_SET_ALL_VALUE_0 = "01";
const string CONFIG_MESSAGE_CREATE_GPIO     = "02";
const string CONFIG_MESSAGE_DELETE_GPIO     = "03";
const string CONFIG_MESSAGE_DELETE_ALL      = "04";

const string PIN_TYPE_PWM                   = "01";
const string PIN_TYPE_SWITCH                = "02";

const string GPIO_MESSAGE_SET_VALUE         = "00";

const string QUERY_MESSAGE_GPIO             = "00";
const string QUERY_MESSAGE_ALL_GPIOS        = "01";
const string QUERY_MESSAGE_DAEMON_STATUS    = "02";

#endif // MESSAGEDEFINITIONS_H_INCLUDED
