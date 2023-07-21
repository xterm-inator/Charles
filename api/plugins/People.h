//
// Created by David on 11/07/2023.
//

#pragma once

#include <drogon/plugins/Plugin.h>
#include <boost/uuid/uuid.hpp>
#include <opencv2/core/mat.hpp>

struct Person
{
    boost::uuids::uuid id;
    std::string Name;
    cv::Mat Feature;
};

class People : public drogon::Plugin<People>
{
public:
    People() = default;

    void initAndStart(const Json::Value& config) override;
    void shutdown() override;

    void AddUnknown(const cv::Mat& Feature);

    void CheckForKnownFace(const cv::Mat& Feature);

private:
    bool bFirstGet{true};
    std::vector<Person> PeopleCache;

    void LoadList();

public:
    inline std::vector<Person>* GetPeople() { return &PeopleCache; };
};