//
// Created by David on 8/07/2023.
//

#pragma once


class Interval {
public:
    Interval();
    [[nodiscard]] unsigned int Value() const;
    void Reset();

private:
    unsigned int StartTime;
};
