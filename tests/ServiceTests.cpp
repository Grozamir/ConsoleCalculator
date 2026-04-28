#include "../src/core/Service.hpp"

#include <nlohmann/json.hpp>
#include <zmq.hpp>

#include <gtest/gtest.h>

using namespace calculator;

using json = nlohmann::json;

class ServiceTestSuite : public ::testing::Test {
public:
    inline static Service service{};

    static void SetUpTestSuite() {
        service.Start( false );
    }

    static void TearDownTestSuite() {
        service.Stop();
        service.Wait();
    }
};

std::string SendRequest( std::string const& request ) {
    zmq::context_t ctx;
    zmq::socket_t sock( ctx, zmq::socket_type::req );

    sock.connect( "tcp://localhost:5555" );

    sock.send( zmq::buffer( request ), zmq::send_flags::none );

    zmq::message_t resultMsg;
    auto res = sock.recv( resultMsg, zmq::recv_flags::none );

    return resultMsg.to_string();
}

void ExpectSuccess( json const& data, int32_t expected ) {
    ASSERT_EQ( data["status"], 0 );
    ASSERT_TRUE( data.contains( "result" ) );

    const int32_t result = data["result"].get<int32_t>();
    EXPECT_EQ( result, expected );
}

TEST_F( ServiceTestSuite, Mul ) {
    auto resultStr = SendRequest( R"({"numA":10,"numB":2,"operation":"mul"})" );

    const json resultData = json::parse( resultStr );

    ExpectSuccess( resultData, 20 );
}

TEST_F( ServiceTestSuite, Add ) {
    auto resultStr = SendRequest( R"({"numA":10,"numB":2,"operation":"add"})" );

    const json resultData = json::parse( resultStr );

    ExpectSuccess( resultData, 12 );
}

TEST_F( ServiceTestSuite, FactorialNegative ) {
    auto resultStr = SendRequest( R"({"numA":-1,"operation":"factorial"})" );

    const json resultData = json::parse( resultStr );

    ASSERT_EQ( resultData["status"], 1 );
    EXPECT_TRUE( resultData.contains( "errorMsg" ) );
}
