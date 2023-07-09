//
// Created by David on 8/07/2023.
//

#include "plugins/Vision.h"
#include "VideoFeedCtrl.h"

void VideoFeedCtrl::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    LOG_DEBUG << "video feed controller";

    auto* VisionPtr = app().getPlugin<Vision>();
//    LOG_DEBUG << VisionPtr->GetImageString();

    HttpResponsePtr resp = HttpResponse::newStreamResponse([](char* Data, unsigned long Size) {
        auto* VisionPtr = app().getPlugin<Vision>();
        std::string str = "--frame\r\nContent-Type: image/jpeg\r\n\r\n" + VisionPtr->GetImageString() + "\r\n";
//        std::vector<char> cstr(str.c_str(), str.c_str() + str.size() + 1);
        Data = str.data();
        return 1;
        }, "", CT_CUSTOM, "multipart/x-mixed-replace; boundary=frame");
    callback(resp);

//        resp->setBody("--frame\r\nContent-Type: image/jpeg\r\n\r\n" + VisionPtr->GetImageString() + "\r\n");
//        resp->setContentTypeString("multipart/x-mixed-replace; boundary=frame");
//        callback(resp);
}

//unsigned long VideoFeedCtrl::GetFrame(char* Data, unsigned long Size) {
//    auto* VisionPtr = app().getPlugin<Vision>();
////    Data = "--frame\r\nContent-Type: image/jpeg\r\n\r\n" + VisionPtr->GetImageString() + "\r\n";
//    return 1;
//}
