//
// Created by David on 11/07/2023.
//
//#include <opencv2/core/matx.hpp>
#include <drogon/HttpAppFramework.h>
#include "People.h"

using namespace drogon::orm;

void People::initAndStart(const Json::Value &config)
{
    LoadList();
}

void People::shutdown()
{}

void People::AddUnknown(const cv::Mat& Feature)
{
    Person Unknown;
    Unknown.Name = "Unknown";
    Unknown.Feature = Feature.clone();
    PeopleCache.push_back(Unknown);
}

void People::LoadList()
{
    DbClientPtr ClientPtr = drogon::app().getDbClient();

    if (ClientPtr != nullptr)
    {
//        try
//        {
            Result Result = ClientPtr->execSqlSync(
                    "SELECT * FROM people LEFT JOIN features on features.person_id = people.id");

            for (const Row &row: Result) {
                LOG_INFO << row["name"].as<std::string>();
            }
//        }
//        catch (const DrogonDbException &e)
//        {
//            LOG_ERROR << "Database Error: " << e.base().what();
//            return;
//        }
    }
}

//----------------------------------------------------------------------------------------
//  Computing the cosine distance between input feature and ground truth feature
//----------------------------------------------------------------------------------------
inline float CosineDistance(const cv::Mat& v1, const cv::Mat& v2)
{
//    double dot = v1.dot(v2);
//    double denom_v1 = cv::norm(v1);
//    double denom_v2 = cv::norm(v2);
    return v1.dot(v2) / (sqrt(v1.dot(v1)) * (sqrt(v2.dot(v2))));
}

void People::CheckForKnownFace(const cv::Mat& Feature)
{
    return;
    Person FoundPerson{};
    bool bPersonFound{false};
    LOG_INFO << "people cache size " << PeopleCache.size();
    for (const Person& Person : PeopleCache)
    {
        float Result = CosineDistance(Feature, Person.Feature);

        LOG_INFO << "Result: " << Result;

        if (Result >= 0.5) {
            LOG_INFO << "Person found";
            FoundPerson = Person;
            bPersonFound = true;
        }
        break;
    }

    if (!bPersonFound)
    {
        LOG_INFO << "Unknown face, adding to database";
        AddUnknown(Feature);
    }
    else
    {
        LOG_INFO << FoundPerson.Name;
    }
}


