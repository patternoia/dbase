/**
* @file StsSensorBatchResource.cxx
* @brief Sts Sensor Batch Entity FairDb web resource class. Generated automatically
* @author Generator by Evgeny Lavrik <evgeny.lavrik@uni-tuebingen.de>
* @date 21.9.2017
**/

#include "StsSensorBatchResource.h"

#include "StsSensorBatch.h"
#include "StsSensor.h"

StsSensorBatchResource::StsSensorBatchResource(Wt::WServer& server, Wt::WObject *parent)
  : Wt::WResource(parent)
{
  server.addResource(this, "/StsSensorBatch/Get");
  server.addResource(this, "/StsSensorBatch/GetArray");
  server.addResource(this, "/StsSensorBatch/GetAll");
  server.addResource(this, "/StsSensorBatch/Store");
  server.addResource(this, "/StsSensorBatch/StoreArray");

  server.addResource(this, "/StsSensorBatch/GetSensors");
}

StsSensorBatchResource::~StsSensorBatchResource()
{
  beingDeleted();
}

void StsSensorBatchResource::handleRequest(const Wt::Http::Request& request,
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

    if (url == "/StsSensorBatch/Get")
    {
      Get(json, request, response);
      return;
    }

    if (url == "/StsSensorBatch/GetArray")
    {
      GetArray(json, request, response);
      return;
    }

    if (url == "/StsSensorBatch/GetAll")
    {
      GetAll(json, request, response);
      return;
    }

    if (url == "/StsSensorBatch/Store")
    {
      Store(json, request, response);
      return;
    }

    if (url == "/StsSensorBatch/StoreArray")
    {
      StoreArray(json, request, response);
      return;
    }

    if (url == "/StsSensorBatch/GetSensors")
    {
      GetSensors(json, request, response);

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

void StsSensorBatchResource::Get(Json::Value json, const Wt::Http::Request& request, Wt::Http::Response& response)
{
  Int_t id = json.get("id", -1).asInt();
  Int_t rid = json.get("rid", 0).asInt();
  StsSensorBatch *instance = StsSensorBatch::GetById(id, rid);

  if (instance)
  {
    response.out() << instance->ToJsonString();
  } else {
    response.setStatus(400);
  }
  delete instance;
}

void StsSensorBatchResource::GetArray(Json::Value json, const Wt::Http::Request& request, Wt::Http::Response& response)
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

  TObjArray *array = StsSensorBatch::GetByIds(ids, idsCount, rid);
  Json::Value jsonArray = StsSensorBatch::ToJsonArray(array);
  response.out() << jsonArray;
  delete[] ids;
  delete array;
}

void StsSensorBatchResource::GetAll(Json::Value json, const Wt::Http::Request& request, Wt::Http::Response& response)
{
  Int_t rid = json.get("rid", 0).asInt();
  TObjArray *array = StsSensorBatch::GetAll(rid);
  Json::Value jsonArray = StsSensorBatch::ToJsonArray(array);
  response.out() << jsonArray;
  delete array;
}

void StsSensorBatchResource::Store(Json::Value json, const Wt::Http::Request& request, Wt::Http::Response& response)
{
  Int_t rid = json.get("rid", 0).asInt();
  Json::Value object = json.get("object", Json::Value(Json::nullValue));
  StsSensorBatch *instance = StsSensorBatch::FromJson(object);
  if (instance)
  {
    std::string logTitle = "FairDbCbmStsREST::StsSensorBatchResource::Store() from " + request.clientAddress();
    instance->SetLogTitle(logTitle);
    instance->store();
  } else {
    response.setStatus(400);
  }
  delete instance;
}

void StsSensorBatchResource::StoreArray(Json::Value json, const Wt::Http::Request& request, Wt::Http::Response& response)
{
  Int_t rid = json.get("rid", 0).asInt();
  Json::Value jsonArray = json.get("array", Json::Value(Json::nullValue));
  
  TObjArray *array = StsSensorBatch::FromJsonArray(jsonArray);
  if (array)
  {
    std::string logTitle = "FairDbCbmStsREST::StsSensorBatchResource::StoreArray() from " + request.clientAddress();
    StsSensorBatch::StoreArray(array, rid, logTitle);
  } else {
    response.setStatus(400);
  }
  delete array;
}

void StsSensorBatchResource::GetSensors(Json::Value json, const Wt::Http::Request& request, Wt::Http::Response& response)
{
  Int_t id = json.get("id", -1).asInt();
  StsSensorBatch *instance = StsSensorBatch::GetById(id);

  if (instance)
  {
    TObjArray *array = instance->GetSensors();
    Json::Value jsonArray = StsSensor::ToJsonArray(array);
    response.out() << jsonArray;
    delete array;
  } else {
    response.setStatus(400);
  }
  
  delete instance;
}

