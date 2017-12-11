/**
* @file FairDbWtAuthResource.h
* @brief FairDb web resource class. Generated automatically
* @author Generator by Evgeny Lavrik <evgeny.lavrik@uni-tuebingen.de>
* @date 30.11.2017
**/

#ifndef FAIRDBWTAUTHRESOURCE_H
#define FAIRDBWTAUTHRESOURCE_H

#include <WServer>
#include <WResource>
#include <Wt/Http/Request>
#include <Wt/Http/Response>

#include "json/json.h"

class FairDbWtAuthResource: public Wt::WResource
{
  public:
    FairDbWtAuthResource(Wt::WServer& server, Wt::WObject *parent = 0);

    ~FairDbWtAuthResource();

    void handleRequest(const Wt::Http::Request& request,
                             Wt::Http::Response& response);

    void Login(const Wt::Http::Request& request, Json::Value requestData, Wt::Http::Response& response, Json::Value &responseData);
};

#endif /* !FAIRDBWTAUTHRESOURCE_H */

