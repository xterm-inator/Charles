//
// Created by David on 9/07/2023.
//

#include <trantor/utils/Logger.h>
#include <fstream>
#include "Stats.h"

int Stats::GetCpuTemp()
{
    std::ifstream CpuFile("/sys/devices/virtual/thermal/thermal_zone1/temp");

    if (!CpuFile.is_open())
    {
        LOG_ERROR << "Failed to get CPU temp";
        return 0;
    }

    std::string TempString;
    CpuFile >> TempString;

    CpuFile.close();

    return (int) (stoi(TempString) / 1000);
}

int Stats::GetGpuTemp()
{
    std::ifstream CpuFile("/sys/devices/virtual/thermal/thermal_zone2/temp");

    if (!CpuFile.is_open())
    {
        LOG_ERROR << "Failed to get GPU temp";
        return 0;
    }

    std::string TempString;
    CpuFile >> TempString;

    CpuFile.close();

    return (int) (stoi(TempString) / 1000);
}