//
// Created by David on 8/07/2023.
//

#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class VideoFeedCtrl:public drogon::HttpSimpleController<VideoFeedCtrl>
{
public:
    void asyncHandleHttpRequest(const HttpRequestPtr &req,
                                        std::function<void (const HttpResponsePtr &)> &&callback)override;
    PATH_LIST_BEGIN
    PATH_ADD("/video_feed",Get);
    PATH_LIST_END
};