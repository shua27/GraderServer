#include <iostream>

#include "cpr/cpr.h"
#include "json.hpp"

int main()
{
    auto response = cpr::Get(cpr::Url{"http://127.0.0.1:5000/"});
    std::cout << response.text;
    return 0;
}
