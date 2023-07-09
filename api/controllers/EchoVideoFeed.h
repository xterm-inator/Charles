//
// Created by David on 8/07/2023.
//

#pragma once
#include <drogon/WebSocketController.h>
using namespace drogon;

class EchoVideoFeed:public drogon::WebSocketController<EchoVideoFeed>
{
public:
    EchoVideoFeed();

    ~EchoVideoFeed() override;

    void handleNewMessage(const WebSocketConnectionPtr& WsConnPtr, std::string&& Message, const WebSocketMessageType& Type) override;
    void handleNewConnection(const HttpRequestPtr& WsReqPtr, const WebSocketConnectionPtr& WsConnPtr) override;
    void handleConnectionClosed(const WebSocketConnectionPtr& WsConnPtr) override;
    WS_PATH_LIST_BEGIN
    WS_PATH_ADD("/echo/video_feed");
    WS_PATH_LIST_END

private:
    std::thread ThreadHandler;
    std::vector<WebSocketConnectionPtr> Connections;
    void HandleVideoSteam();
    std::atomic<bool> bShouldRun{true};
};