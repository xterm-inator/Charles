#include <iostream>
#include <csignal>
#include <jetson-utils/logging.h>
#include <algorithm>
#include <drogon/drogon.h>

int main() {
    drogon::app().loadConfigFile("../config.json");

    drogon::app().registerPostHandlingAdvice(
        [](const drogon::HttpRequestPtr &req, const drogon::HttpResponsePtr &resp) {
            const std::string& origin = req->getHeader("Origin");
            resp->addHeader("Access-Control-Allow-Origin", origin);
            resp->addHeader("Access-Control-Allow-Methods", "OPTIONS,POST");
            resp->addHeader("Access-Control-Allow-Headers",
                                           "x-requested-with,content-type");
            resp->addHeader("Access-Control-Allow-Credentials","true");
        });

    drogon::app().run();

    return 0;
}
