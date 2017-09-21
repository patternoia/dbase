/**
* @file StsSensorResource.cxx
* @brief Sts Sensor Entity FairDb web resource class. Generated automatically
* @author Generator by Evgeny Lavrik <evgeny.lavrik@uni-tuebingen.de>
* @date 21.9.2017
**/

#include "StsSensorResource.h"

#include "StsSensor.h"
#include "StsSensorBatch.h"

StsSensorResource::StsSensorResource(Wt::WServer& server, Wt::WObject *parent)
  : Wt::WResource(parent)
{
  server.addResource(this, "/StsSensor/Get");
  server.addResource(this, "/StsSensor/GetArray");
  server.addResource(this, "/StsSensor/GetAll");
  server.addResource(this, "/StsSensor/Store");
  server.addResource(this, "/StsSensor/StoreArray");

  server.addResource(this, "/StsSensor/GetByBatchId");

  server.addResource(this, "/StsSensor/GetBySUID");

  server.addResource(this, "/StsSensor/GetBatch");
}

StsSensorResource::~StsSensorResource()
{
  beingDeleted();
}

void StsSensorResource::handleRequest(const Wt::Http::Request& request,
                   Wt::Http::Response& response)
{
  try
  {
    string url(request.path());
    string jsonString(std::istreambuf_iterator<char>(request.in()), {});

    Json::Value json;
    string msg;
    Json::CharReaderBuilder readerBuilder;
    Json::CharReader *reader = readerBuilder.newCharReader();
    Bool_t result = reader->parse(jsonString.data(), jsonString.data() + jsonString.size(), &json, &msg);
    delete reader;

    if (!result)
    {
      Json::Value error;
      error["error"] = msg;
      response.out() << error;
      response.setStatus(400);
      return;
    }

    if (url == "/StsSensor/Get")
    {
      Get(json, request, response);
      return;
    }

    if (url == "/StsSensor/GetArray")
    {
      GetArray(json, request, response);
      return;
    }

    if (url == "/StsSensor/GetAll")
    {
      GetAll(json, request, response);
      return;
    }

    if (url == "/StsSensor/Store")
    {
      Store(json, request, response);
      return;
    }

    if (url == "/StsSensor/StoreArray")
    {
      StoreArray(json, request, response);
      return;
    }

    if (url == "/StsSensor/GetByBatchId")
    {
      GetByBatchId(json, request, response);
      return;
    }

    if (url == "/StsSensor/GetBySUID")
    {
      GetBySUID(json, request, response);
      return;
    }

    if (url == "/StsSensor/GetBatch")
    {
      GetBatch(json, request, response);
      return;
    }

  } catch (Json::Exception &e) {
    Json::Value error;
    error["error"] = e.what();
    response.out() << error;
    response.setStatus(400);
    return;
  }
}

void StsSensorResource::Get(Json::Value json, const Wt::Http::Request& request, Wt::Http::Response& response)
{
  Int_t id = json.get("id", -1).asInt();
  Int_t rid = json.get("rid", 0).asInt();
  StsSensor *instance = StsSensor::GetById(id, rid);

  if (instance)
  {
    response.out() << instance->ToJsonString();
  } else {
    response.setStatus(400);
  }
  delete instance;
}

void StsSensorResource::GetArray(Json::Value json, const Wt::Http::Request& request, Wt::Http::Response& response)
{
  Int_t rid = json.get("rid", 0).asInt();
  Json::Value jsonIdsArray = json.get("ids", Json::Value(Json::arrayValue));
  Int_t idsCount = jsonIdsArray.size();

  if (!idsCount)
  {
    response.out() << Json::Value(Json::arrayValue);
    return;
  }

  Int_t *ids = new Int_t[idsCount];
  for (Int_t i = 0; i < idsCount; i++)
  {
    ids[i] = jsonIdsArray.get(i, -1).asInt();
  }

  TObjArray *array = StsSensor::GetByIds(ids, idsCount, rid);
  Json::Value jsonArray = StsSensor::ToJsonArray(array);
  response.out() << jsonArray;
  delete[] ids;
  delete array;
}

void StsSensorResource::GetAll(Json::Value json, const Wt::Http::Request& request, Wt::Http::Response& response)
{
  Int_t rid = json.get("rid", 0).asInt();
  TObjArray *array = StsSensor::GetAll(rid);
  Json::Value jsonArray = StsSensor::ToJsonArray(array);
  response.out() << jsonArray;
  delete array;
}

void StsSensorResource::Store(Json::Value json, const Wt::Http::Request& request, Wt::Http::Response& response)
{
  Int_t rid = json.get("rid", 0).asInt();
  Json::Value object = json.get("object", Json::Value(Json::nullValue));
  StsSensor *instance = StsSensor::FromJson(object);
  if (instance)
  {
    std::string logTitle = "FairDbCbmStsREST::StsSensorResource::Store() from " + request.clientAddress();
    instance->SetLogTitle(logTitle);
    instance->store();
  } else {
    response.setStatus(400);
  }
  delete instance;
}

void StsSensorResource::StoreArray(Json::Value json, const Wt::Http::Request& request, Wt::Http::Response& response)
{
  Int_t rid = json.get("rid", 0).asInt();
  Json::Value jsonArray = json.get("array", Json::Value(Json::nullValue));
  
  TObjArray *array = StsSensor::FromJsonArray(jsonArray);
  if (array)
  {
    std::string logTitle = "FairDbCbmStsREST::StsSensorResource::StoreArray() from " + request.clientAddress();
    StsSensor::StoreArray(array, rid, logTitle);
  } else {
    response.setStatus(400);
  }
  delete array;
}

void StsSensorResource::GetByBatchId(Json::Value json, const Wt::Http::Request& request, Wt::Http::Response& response)
{
  Int_t rid = json.get("rid", 0).asInt();
  Int_t BatchId = json.get("BatchId", -1).asInt();
  TObjArray *array = StsSensor::GetByBatchId(BatchId, rid);

  Json::Value jsonArray = StsSensor::ToJsonArray(array);
  response.out() << jsonArray;
  delete array;
}

void StsSensorResource::GetBySUID(Json::Value json, const Wt::Http::Request& request, Wt::Http::Response& response)
{
  Int_t rid = json.get("rid", 0).asInt();
  string SUID = json.get("SUID", -1).asString();
  TObjArray *array = StsSensor::GetBySUID(SUID, rid);

  Json::Value jsonArray = StsSensor::ToJsonArray(array);
  response.out() << jsonArray;
  delete array;
}

void StsSensorResource::GetBatch(Json::Value json, const Wt::Http::Request& request, Wt::Http::Response& response)
{
  Int_t id = json.get("id", -1).asInt();
  StsSensor *instance = StsSensor::GetById(id);

  if (instance)
  {
    StsSensorBatch *prop = instance->GetBatch();
    if (prop)
    {
      response.out() << prop->ToJson();
    }
  } else {
    response.setStatus(400);
  }

  delete instance;
}

