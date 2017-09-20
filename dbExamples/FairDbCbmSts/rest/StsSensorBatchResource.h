/**
* @file StsSensorBatchResource.h
* @brief Sts Sensor Batch Entity FairDb web resource class. Generated automatically
* @author Generator by Evgeny Lavrik <evgeny.lavrik@uni-tuebingen.de>
* @date 20.9.2017
**/

#ifndef STSSENSORBATCHRESOURCE_H
#define STSSENSORBATCHRESOURCE_H

#include <WServer>
#include <WResource>
#include <Wt/Http/Request>
#include <Wt/Http/Response>

#include "json/json.h"

class StsSensorBatchResource: public Wt::WResource
{
  public:
    StsSensorBatchResource(Wt::WServer& server, Wt::WObject *parent = 0);

    ~StsSensorBatchResource();

    void handleRequest(const Wt::Http::Request& request,
                             Wt::Http::Response& response);

  private:
    void Get(Json::Value json, Wt::Http::Response& response);
    void GetArray(Json::Value json, Wt::Http::Response& response);
    void GetAll(Json::Value json, Wt::Http::Response& response);
    void Store(Json::Value json, Wt::Http::Response& response);
    void StoreArray(Json::Value json, Wt::Http::Response& response);

    void GetByNumber(Json::Value json, Wt::Http::Response& response);

    void GetSensors(Json::Value json, Wt::Http::Response& response);
};

#endif /* !STSSENSORBATCHRESOURCE_H */

