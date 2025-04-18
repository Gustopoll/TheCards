#include "logger.h"

#include <chrono>
#include <iomanip>

namespace Log
{

namespace
{

std::string GetCurrentTime()
{
    const auto now = std::chrono::system_clock::now();
    const auto nowInMs = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1'0000;
    const auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S") << "."
       << std::setfill('0') << std::setw(4) << nowInMs.count();
    return "[" + ss.str() + "]";
}

} // anon namespace

void Logger::SetFile(const std::string& file)
{
    if (_file.is_open())
        _file.close();

    _filename = file;
    _file.open(file);
}

void Logger::Clean()
{
    std::remove(_filename.c_str());
}

void Logger::LogInfo(const char* message)
{
    LogMessage(GetCurrentTime() + " Info: " + message + "\n");
}

void Logger::LogInfo(const QString& message)
{
    LogInfo(message.toStdString().c_str());
}

void Logger::LogError(const char* message)
{
    LogMessage(GetCurrentTime() + " Error: " + message + "\n");
}

void Logger::LogError(const QString& message)
{
    LogError(message.toStdString().c_str());
}

void Logger::LogMessage(const std::string& message)
{
    if (!_file.is_open())
        _file.open(_filename, std::ios::app);

    _file << message;
    _file.flush();
    _file.close();
}

Logger Multiplayer;

} // namespace log
