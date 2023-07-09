//
// Created by David on 8/07/2023.
//

#include <ctime>
#include "Interval.h"

Interval::Interval()
{
    StartTime = clock();
}

unsigned int Interval::Value() const
{
    return (unsigned int) ((clock() - StartTime) / (CLOCKS_PER_SEC / 1000));
}

void Interval::Reset()
{
    StartTime = clock();
}