/**
* @file StsSensorResource.h
* @brief Sts Sensor Entity FairDb web resource class. Generated automatically
* @author Generator by Evgeny Lavrik <evgeny.lavrik@uni-tuebingen.de>
* @date 20.9.2017
**/

#ifndef STSSENSORRESOURCE_H
#define STSSENSORRESOURCE_H

#include <WServer>
#include <WResource>
#include <Wt/Http/Request>
#include <Wt/Http/Response>

#include "json/json.h"

class StsSensorResource: public Wt::WResource
{
  public:
    StsSensorResource(Wt::WServer& server, Wt::WObject *parent = 0);

    ~StsSensorResource();

    void handleRequest(const Wt::Http::Request& request,
                             Wt::Http::Response& response);

  private:
    void Get(Json::Value json, Wt::Http::Response& response);
    void GetArray(Json::Value json, Wt::Http::Response& response);
    void GetAll(Json::Value json, Wt::Http::Response& response);
    void Store(Json::Value json, Wt::Http::Response& response);
    void StoreArray(Json::Value json, Wt::Http::Response& response);

    void GetByBatchId(Json::Value json, Wt::Http::Response& response);

    void GetBySUID(Json::Value json, Wt::Http::Response& response);

    void GetBatch(Json::Value json, Wt::Http::Response& response);
};

#endif /* !STSSENSORRESOURCE_H */

