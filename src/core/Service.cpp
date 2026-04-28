#include "Service.hpp"

#include <zmq.hpp>

#include "core/Logger.hpp"
#include "core/Runner.hpp"

namespace calculator {

void Service::Start( bool withSignals ) {
    workerThread = std::thread( &Service::WorkerHandle, this );

    if ( withSignals ) {
        sigset_t set;
        sigemptyset( &set );
        sigaddset( &set, SIGTERM );

        pthread_sigmask( SIG_BLOCK, &set, nullptr );

        int sig = 0;
        const int s = sigwait( &set, &sig );

        if ( s == 0 ) {
            needStop = true;
        }
    }
}

void Service::Stop() {
    needStop = true;
}

void Service::Wait() {
    if ( workerThread.joinable() ) {
        workerThread.join();
    }
}

void Service::WorkerHandle() {
    try {
        zmq::context_t ctx;
        zmq::socket_t sock( ctx, zmq::socket_type::rep );
        sock.bind( "tcp://*:5555" );

        const int rcvttimeoMs = 500;
        sock.set( zmq::sockopt::rcvtimeo, rcvttimeoMs );

        Runner runner{};
        runner.Init();

        while ( !needStop ) {
            zmq::message_t reqMsg;
            auto res = sock.recv( reqMsg, zmq::recv_flags::none );

            if ( !res ) {
                continue;
            }

            const std::string reqStr = reqMsg.to_string();

            Logger::Instance().Info( "Incoming request: " + reqStr );

            auto responseStr = runner.Run( reqStr ).ToJsonStr();

            sock.send( zmq::buffer( responseStr ), zmq::send_flags::none );
        }

        Logger::Instance().Info( "End worker handle!" );
    } catch ( const std::exception& ex ) {
        Logger::Instance().Error( ex.what() );
    }
}

}  // namespace calculator
