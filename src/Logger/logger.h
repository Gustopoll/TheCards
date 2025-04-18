#ifndef LOGGER_H
#define LOGGER_H

#include <QString>

#include <string>
#include <fstream>

namespace Log
{

class Logger
{
public:
    Logger() = default;

    //! Sets the file for logs.
    //!
    //! @param file File with the path to log records.
    void SetFile(const std::string& file);

    //! Cleans the output file.
    void Clean();

    void LogInfo(const char* message);
    void LogInfo(const QString& message);

    void LogError(const char* message);
    void LogError(const QString& message);

private:
    //! Logs the message.
    //!
    //! @param message Log message to the output file.
    void LogMessage(const std::string& message);

    std::string _filename;
    std::ofstream _file;
};

extern Logger Multiplayer;

} // namespace log

#endif // LOGGER_H
