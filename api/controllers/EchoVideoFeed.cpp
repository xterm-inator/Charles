//
// Created by David on 8/07/2023.
//

#include "EchoVideoFeed.h"
#include "plugins/Vision.h"

EchoVideoFeed::EchoVideoFeed()
{
    ThreadHandler = std::thread(&EchoVideoFeed::HandleVideoSteam, this);
}

EchoVideoFeed::~EchoVideoFeed() {
    bShouldRun = false;
    ThreadHandler.join();
}

void EchoVideoFeed::handleNewMessage(const WebSocketConnectionPtr& WsConnPtr, std::string&& Message, const WebSocketMessageType& Type)
{

}

void EchoVideoFeed::handleNewConnection(const HttpRequestPtr& WsReqPtr, const WebSocketConnectionPtr& WsConnPtr)
{
    LOG_INFO << "ws connection: " << WsConnPtr->peerAddr().toIp();

    Connections.push_back(WsConnPtr);
}

void EchoVideoFeed::handleConnectionClosed(const WebSocketConnectionPtr& WsConnPtr)
{
    Connections.erase(
            std::remove_if(
                    Connections.begin(),
                    Connections.end(),
                    [](const std::shared_ptr<WebSocketConnection>& Connection) {
                        return !Connection->connected();
                    }
            ),
            Connections.end()
    );
}

void EchoVideoFeed::HandleVideoSteam()
{
    auto* VisionPtr = app().getPlugin<Vision>();

    while (bShouldRun) {
        if (VisionPtr != nullptr && VisionPtr->Ready && !Connections.empty()) {
            std::string Image = VisionPtr->GetBase64Image();
            for (std::shared_ptr<WebSocketConnection> &Connection: Connections) {
                Connection->send(VisionPtr->GetBase64Image());
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}

