//
// Created by David on 8/07/2023.
//

#include "StatsCtrl.h"
#include "plugins/Vision.h"
#include "utils/Stats.h"

void StatsCtrl::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto* VisionPtr = app().getPlugin<Vision>();

    Json::Value Values;
    Values["fps"] = VisionPtr->GetFps();
    Values["cpu_temp"] = Stats::GetCpuTemp();
    Values["gpu_temp"] = Stats::GetGpuTemp();

    HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(Values);
    callback(resp);
}
