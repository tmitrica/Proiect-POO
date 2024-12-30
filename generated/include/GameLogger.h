#ifndef GAMELOGGER_H
#define GAMELOGGER_H

#include "Observer.h"
#include <string>
#include <iostream>

/**
 * @class GameLogger
 * @brief Observer implementation for logging game events to the console.
 */
class GameLogger : public Observer {
public:
    /**
     * @brief Updates the logger with a new message.
     * @param message The message to log.
     */
    void update(const std::string& message) override;
};


#endif // GAMELOGGER_H
