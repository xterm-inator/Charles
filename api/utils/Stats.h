//
// Created by David on 9/07/2023.
//

#pragma once


class Stats {
public:
    Stats() = default;
    ~Stats() = default;

    static int GetCpuTemp() ;
    static int GetGpuTemp();
};
