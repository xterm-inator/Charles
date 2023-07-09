//
// Created by David on 8/07/2023.
//

#pragma once

#include <drogon/plugins/Plugin.h>
#include <atomic>
#include "utils/Fps.h"
#include "vision/Image.h"

class Vision : public drogon::Plugin<Vision>
{
public:
    Vision() = default;
    void initAndStart(const Json::Value& config) override;
    void shutdown() override;

    [[nodiscard]] std::string GetBase64Image() const;
    [[nodiscard]] std::string GetImageString() const;

    bool Ready{false};

private:
    std::thread ThreadHandler;
    std::atomic<bool> ShouldRun{true};
    Fps FpsCounter;
    Image FrameImage;

    void Run(std::atomic<bool>& ShouldRun);

public:
    inline unsigned int GetFps() { return FpsCounter.Get(); };
};