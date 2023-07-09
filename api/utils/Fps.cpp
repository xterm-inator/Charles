//
// Created by David on 8/07/2023.
//
#include "Fps.h"

void Fps::Update()
{
    FpsCount++;
    if (FpsInterval.Value() > 1000)
    {
        CurrentFps = FpsCount;
        FpsCount = 0;
        FpsInterval.Reset();
    }
}