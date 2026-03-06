#pragma once

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace calculator {

class Logger {
public:
    static Logger& Instance() {
        static Logger instance;
        return instance;
    }

    void Error( std::string_view msg ) {
        spdlogger->error( msg );
    }

private:
    std::shared_ptr<spdlog::logger> spdlogger;

private:
    Logger() {
        spdlogger = spdlog::stdout_color_st( "console" );
    }
    ~Logger() = default;

    Logger( const Logger& ) = delete;
    Logger& operator=( const Logger& ) = delete;
};

}  // namespace calculator
