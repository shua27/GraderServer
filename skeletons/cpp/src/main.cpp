#include <iostream>

#include "cpr/cpr.h"
#include "json.hpp"

int main()
{
    auto response = cpr::Get(cpr::Url{"http://127.0.0.1:5000/CreateChallenge/1"});
    auto responseAsJson(nlohmann::json::parse(response.text));

    auto args(responseAsJson.find("Args"));

    std::cout << responseAsJson.dump(4);

    return 0;
}
