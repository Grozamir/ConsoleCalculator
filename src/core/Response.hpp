#pragma once

#include <string>

namespace calculator {

struct Response {
    int32_t result = 0;
    int32_t status = 0;
    std::string errorMsg;

    static Response Ok( int32_t newResult ) {
        return Response{ .result = newResult, .status = 0 };
    }

    static Response Error( std::string const& newErrorMsg, int32_t newStatus = 1 ) {
        return Response{ .result = 0, .status = newStatus, .errorMsg = newErrorMsg };
    }

    std::string ToJsonStr() const;
};

}  // namespace calculator