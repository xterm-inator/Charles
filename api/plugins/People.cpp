//
// Created by David on 11/07/2023.
//

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

}

void People::LoadList()
{
    DbClientPtr ClientPtr = drogon::app().getDbClient();
    try
    {
        Result Result = ClientPtr->execSqlSync("SELECT * FROM people LEFT JOIN features on features.person_id = people.id");

        for (const Row& row : Result)
        {
            LOG_INFO << row["name"].as<std::string>();
        }
    }
    catch (const DrogonDbException& e)
    {
        LOG_ERROR << e.base().what();
        return;
    }
}
