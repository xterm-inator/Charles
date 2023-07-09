//
// Created by David on 8/07/2023.
//

#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class StatsCtrl : public drogon::HttpSimpleController<StatsCtrl>
{
  public:
    void asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) override;
    PATH_LIST_BEGIN
    PATH_ADD("/stats",Get);
    PATH_LIST_END
};
