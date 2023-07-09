//
// Created by David on 8/07/2023.
//

#pragma once

#include "Interval.h"

class Fps {
public:
    Fps() = default;
    void Update();

private:
    unsigned int CurrentFps{0};
    unsigned int FpsCount{0};
    Interval FpsInterval;

public:
    [[nodiscard]] inline unsigned int Get() const { return CurrentFps; };
};
