#ifndef CHESS_SFML_NOTIFICATIONMANAGER_H
#define CHESS_SFML_NOTIFICATIONMANAGER_H


#include <memory>
#include <queue>
#include "Notification.h"

class NotificationManager {
    std::queue<std::unique_ptr<Notification>> pending;

public:

    void addNotification(Notification notification) {
        pending.push(std::make_unique<Notification>(notification));
    }

    Notification* getCurrentNotification() {
        if (pending.empty())
            return nullptr;
        return pending.front().get();
    }

    void refresh() {
        if (!pending.empty() && !getCurrentNotification()->isActive()) {
            pending.pop();
            if (!pending.empty())
                getCurrentNotification()->activate();
        }
    }

};


#endif //CHESS_SFML_NOTIFICATIONMANAGER_H
