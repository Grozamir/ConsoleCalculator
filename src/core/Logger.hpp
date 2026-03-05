#pragma once

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

class Logger {
public:
    static std::shared_ptr<spdlog::logger> Instance() {
        static auto logger = spdlog::stdout_color_st( "console" );
        return logger;
    }

private:
    Logger() = default;
    ~Logger() = default;

    Logger( const Logger& ) = delete;
    Logger& operator=( const Logger& ) = delete;
};
