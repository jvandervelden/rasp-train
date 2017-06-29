#include "PinHandlerManager.h"

PinHandlerManager::PinHandlerManager() {
    //ctor
}

void PinHandlerManager::AddHandler(BasePinHandler* handler) {
    PinHandlerNode* node = new PinHandlerNode;

    if (this->FindNode(handler->getPin()) != NULL) {
        throw "Pin allocated already.";
    }

    node->next = NULL;
    node->prev = NULL;
    node->handler = handler;

    if (this->handlerListHead == NULL) {
        this->handlerListHead = node;
        this->handlerListTail = node;
    } else {
        this->handlerListTail->next = node;
        node->prev = this->handlerListTail;
        this->handlerListTail = node;
    }
}

BasePinHandler* PinHandlerManager::GetHandler(int pin) {
    PinHandlerNode* node = this->FindNode(pin);

    if (node != NULL) {
        return node->handler;
    }

    return NULL;
}

void PinHandlerManager::DeleteHandler(int pin) {
    PinHandlerNode* node = this->FindNode(pin);

    if (node == this->handlerListHead) {
        this->handlerListHead = node->next;
    } else {
        node->prev->next = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    }

    node->handler->setValue(0.0f);
    node->handler->stop();

    delete node;
}

PinHandlerNode* PinHandlerManager::FindNode(int pin) {
    PinHandlerNode* current = this->handlerListHead;

    while (current != NULL) {
        if (current->handler->getPin() == pin) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

void PinHandlerManager::loopHandlers(NodeLoopHandler callback) {
    PinHandlerNode* current = this->handlerListHead;

    while (current != NULL) {
        callback(current);
        current = current->next;
    }
}

void PinHandlerManager::DeleteAllHandlers() {
    PinHandlerNode* current = this->handlerListHead;
    PinHandlerNode* prev = NULL;

    while (current != NULL) {
        prev = current;
        current = current->next;
        prev->handler->setValue(0.0f);
        prev->handler->stop();
        delete prev;
    }
}

PinHandlerManager::~PinHandlerManager() {
    DeleteAllHandlers();
}
