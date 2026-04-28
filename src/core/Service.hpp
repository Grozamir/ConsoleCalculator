#pragma once

#include <thread>

namespace calculator {

class Service {
public:
    void Start( bool withSignals = true );
    void Stop();
    void Wait();

private:
    std::atomic<bool> needStop = false;

    std::thread signalThread;
    std::thread workerThread;

    void SignalHandle( sigset_t set );

    void WorkerHandle();
};

}  // namespace calculator
