#ifndef CHESS_SFML_NOTIFICATIONMANAGER_H
#define CHESS_SFML_NOTIFICATIONMANAGER_H


#include <memory>
#include <queue>
#include "Notification.h"

class NotificationManager {
private:
    NotificationManager() = default;
    NotificationManager& operator=(const NotificationManager&) = delete;

    std::queue<std::unique_ptr<Notification>> pending;

public:
    NotificationManager(const NotificationManager&) = delete;

    static NotificationManager& Instance() {
        static NotificationManager _instance;
        return _instance;
    }

    void addNotification(Notification notification) {
        pending.push(std::make_unique<Notification>(notification));
    }

    Notification* getCurrentNotification() const {
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
