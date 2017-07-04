#include "QueueMessageHandler.h"

QueueMessageHandler::QueueMessageHandler(int listenPort, PinHandlerManager* pinHandlerManager) {
    this->pinHandlerManager = pinHandlerManager;
    this->listenPort = listenPort;

    cout << "Starting zero mq on port: " << this->listenPort << "\n";

    string socketAddress("tcp://127.0.0.1:");
    socketAddress += to_string(this->listenPort);

    this->socket.bind (socketAddress.c_str());

    cout << "Starting to process queue @: " << socketAddress << endl;

    this->running = true;

    this->queueThread = thread(&QueueMessageHandler::threadFunction, this);
}

void QueueMessageHandler::threadFunction() {
    string message;

    zmq::message_t request;

    while(this->running) {
        if (this->socket.recv (&request, ZMQ_DONTWAIT)) {

            message.append((char*)request.data(), request.size());

            cout << "Got message: " << message << endl;

            string replyMessage;

            try {
                replyMessage = this->handleMessage(message);
            } catch (exception& e) {
                cout << "Error processing message '" << message << "'. Error: " << e.what() << endl;
                replyMessage = buildErrorMessage("Unhandled Exception." + string(e.what()));
            }

            zmq::message_t reply (replyMessage.size());
            memcpy (reply.data(), replyMessage.c_str(), replyMessage.size());

            this->socket.send (reply);

            message.clear();
        } else {
            delayMicroseconds(100000);
        }
    }
}

string QueueMessageHandler::handleMessage(string message) {
    string messageType = message.substr(0, message.find_first_of(':'));
    string messageData = message.substr(message.find_first_of(':') + 1);
    string replyMessage = buildErrorMessage("Message Type: " + messageType + " is invalid.");

    if (messageType == CONFIG_MESSAGE_ID) {
        replyMessage = this->handleConfigMessage(messageData);
    } else if (messageType == QUERY_MESSAGE_ID) {
        replyMessage = this->handleQueryMessage(messageData);
    } else if (messageType == GPIO_MESSAGE_ID) {
        replyMessage = this->handleGpioMessage(messageData);
    }

    return replyMessage;
}

string QueueMessageHandler::handleConfigMessage(string messageData) {
    string configMessageType;

    if (messageData.find_first_of(':') == string::npos) {
        configMessageType = messageData;
    } else {
        configMessageType = messageData.substr(0, messageData.find_first_of(':'));
    }

    if (configMessageType == CONFIG_MESSAGE_QUIT) {
        this->running = false;
        return buildSuccessMessage("");
    } else if (configMessageType == CONFIG_MESSAGE_SET_ALL_VALUE_0) {
        this->pinHandlerManager->loopHandlers([](PinHandlerNode* node, int index, bool first, bool last) {
            node->handler->setValue(0.0f);
        });
        return buildSuccessMessage("");
    } else if (configMessageType == CONFIG_MESSAGE_CREATE_GPIO) {
        if (messageData.find_first_of(':') == string::npos) {
            return buildErrorMessage("Invalid message format for create GPIO.");
        }

        string pinData = messageData.substr(messageData.find_first_of(':') + 1);
        string pin = pinData.substr(0, 3);
        string gpioType = messageData.substr(messageData.find_first_of(':') + 5, 2);

        int iPin = stoi(pin);

        BasePinHandler* handler = this->pinHandlerManager->GetHandler(iPin);

        if (handler != NULL) {
            this->pinHandlerManager->DeleteHandler(iPin);
        }

        BasePinHandler* newHandler;

        if (gpioType == PIN_TYPE_PWM) {
            newHandler = (BasePinHandler*)new PwmPinHandler(iPin);
        } else if (gpioType == PIN_TYPE_SWITCH) {
            newHandler = (BasePinHandler*)new SwitchPinHandler(iPin);
        } else {
            return buildErrorMessage("Gpio pin type: " + gpioType + " is invalid.");
        }

        newHandler->setValue(0.0f);
        newHandler->run();

        this->pinHandlerManager->AddHandler(newHandler);

        return buildSuccessMessage("");
    } else if (configMessageType == CONFIG_MESSAGE_DELETE_GPIO) {
        string pin = messageData.substr(messageData.find_first_of(':') + 1, 3);
        int iPin = stoi(pin);
        this->pinHandlerManager->DeleteHandler(iPin);

        return buildSuccessMessage("");
    } else if (configMessageType == CONFIG_MESSAGE_DELETE_ALL) {
        this->pinHandlerManager->DeleteAllHandlers();

        return buildSuccessMessage("");
    }

    return buildErrorMessage("Config message type: " + configMessageType + " is invalid.");
}

string QueueMessageHandler::handleGpioMessage(string messageData) {
    string gpioMessageType = messageData.substr(0, messageData.find_first_of(':'));

    if (gpioMessageType == GPIO_MESSAGE_SET_VALUE) {
        string pin = messageData.substr(messageData.find_first_of(':') + 1, 3);
        string gpioNewValue = messageData.substr(messageData.find_first_of(':') + 5);

        int iPin = stoi(pin);
        float fGpioNewValue = stof(gpioNewValue);

        BasePinHandler* basePinHandler = this->pinHandlerManager->GetHandler(iPin);

        if (basePinHandler != NULL) {
            basePinHandler->setValue(fGpioNewValue);

            return buildSuccessMessage("");
        } else {
            return buildErrorMessage("Pin " + pin + " hasn't been initialized.");
        }
    }

    return buildErrorMessage("Gpio message type: " + gpioMessageType + " is invalid.");
}

string QueueMessageHandler::handleQueryMessage(string messageData) {

    string queryMessageType;

    if (messageData.find_first_of(':') == string::npos) {
        queryMessageType = messageData;
    } else {
        queryMessageType = messageData.substr(0, messageData.find_first_of(':'));
    }

    if (queryMessageType == QUERY_MESSAGE_GPIO) {

        if (messageData.find_first_of(':') == string::npos) {
            return buildErrorMessage("Invalid message format for query GPIO.");
        }

        string queryMessageData = messageData.substr(messageData.find_first_of(':') + 1);
        string pin = queryMessageData.substr(0, 3);

        int iPin = stoi(pin);

        BasePinHandler* handler = this->pinHandlerManager->GetHandler(iPin);

        if (handler == NULL) {
            return buildErrorMessage("Pin: " + pin + " is not initialized.");
        }

        string pinJson = buildGpioMessage(handler);

        return buildSuccessMessage(pinJson);
    } else if (queryMessageType == QUERY_MESSAGE_ALL_GPIOS) {
        string replyJson = "[";

        /*
        this->pinHandlerManager->loopHandlers([] (BasePinHandler* handler, int index, bool first, bool last) {
            string pinJson;
            pinJson += "{\"wiringPiPin\":\"";
            pinJson += handler->getPin();
            pinJson += "\",\"type\":\"";
            pinJson += handler->getType();
            pinJson += "\",\"value\":";
            pinJson += handler->getValue();
            pinJson += "}";

            replyJson += pinJson;

            if (!last) {
                replyJson += ",";
            }
        });
        */

        replyJson += "]";

        return buildSuccessMessage(replyJson);
    } else if (queryMessageType == QUERY_MESSAGE_DAEMON_STATUS) {
    }

    return buildErrorMessage("Query message type: " + queryMessageType + " is invalid.");
}

string QueueMessageHandler::buildGpioMessage(BasePinHandler* handler) {
    string message;
    message += "{\"wiringPiPin\":\"";
    message += std::to_string(handler->getPin());
    message += "\",\"type\":\"";
    message += handler->getType();
    message += "\",\"value\":";
    message += std::to_string(handler->getValue());
    message += "}";

    return message;
}

string QueueMessageHandler::buildSuccessMessage(string successValue) {
    string message;
    message += "{\"status\":\"success\",\"value\":\"";
    message += successValue;
    message += "\"}";

    return message;
}

string QueueMessageHandler::buildErrorMessage(string errorMessage) {
    string message;

    message += "{\"status\":\"error\",\"message\":\"";
    message += errorMessage;
    message += "\"}";

    return message;
}

bool QueueMessageHandler::isRunning() {
    return this->running;
}

QueueMessageHandler::~QueueMessageHandler() {

    cout << "Closing zero mq." << endl;

    this->socket.close();

    this->running = false;

    this->queueThread.join();
}
