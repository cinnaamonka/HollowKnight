#include "pch.h"



void EventEmitter::on(const std::string eventName, const EventCallback callback) {
    callbacks[eventName].push_back(callback);
}

void EventEmitter::emit(const std::string eventName) {
    if (callbacks.find(eventName) != callbacks.end()) {
        const std::vector<EventEmitter::EventCallback> eventCallbacks = callbacks[eventName];

        for (const EventEmitter::EventCallback callback : eventCallbacks) {
            callback();
        }
    }
}
