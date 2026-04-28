#include "Response.hpp"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace calculator {

std::string Response::ToJsonStr() const {
    json j;
    j["status"] = status;

    if ( status == 0 ) {
        j["result"] = result;
    } else {
        j["errorMsg"] = errorMsg;
    }

    return j.dump();
}

}  // namespace calculator