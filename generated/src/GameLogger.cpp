#include "GameLogger.h"

/**
 * @brief Updates the logger with a new message.
 * Logs the message to the console.
 *
 * @param message The message to log.
 */
void GameLogger::update(const std::string& message) {
    std::cout << "LOG: " << message << std::endl;
}


