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

    std::thread workerThread;

    void WorkerHandle();
};

}  // namespace calculator
