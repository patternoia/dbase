#include "FairDbRelationalParSet.h"

ClassImpT(FairDbRelationalParSet,T)

template<typename T>
FairDbRelationalParSet<T>::FairDbRelationalParSet()
  : FairDbGenericParSet<T>(),
  fId(0)
{
}

template<typename T>
FairDbRelationalParSet<T>::FairDbRelationalParSet(FairDbDetector::Detector_t detid,
              DataType::DataType_t dataid,
              const char* name,
              const char* title,
              const char* context,
              Bool_t ownership)
  : FairDbGenericParSet<T>(detid, dataid, name, title, context, ownership),
  fId(0)
{
}

template<typename T>
FairDbRelationalParSet<T>::FairDbRelationalParSet(const FairDbRelationalParSet& from)
  : FairDbGenericParSet<T>(from)
{
  fId = from.fId;
}

template<typename T>
FairDbRelationalParSet<T>& FairDbRelationalParSet<T>::operator=(const FairDbRelationalParSet& from)
{
  if (this == &from) { return *this; }

  FairDbGenericParSet<T>::operator=(from);
  SetId(from.GetId());

  return *this;
}

template<typename T>
FairDbRelationalParSet<T>::~FairDbRelationalParSet()
{
}

template<typename T>
T* FairDbRelationalParSet<T>::GetById(Int_t id, UInt_t rid)
{
  return T::GetByIndex(id, rid);
}

template<typename T>
TObjArray* FairDbRelationalParSet<T>::GetByIds(Int_t* ids, UInt_t count, UInt_t rid)
{
  if (!ids)
    return NULL;

  return T::GetBy(
    [&ids, &count](T *inst) -> bool
      {
        for (Int_t i=0; i < count; i++)
        {
          if (ids[i] == inst->GetId())
          {
            return true;
          }
        }
        return false;
      });
}

template<typename T>
TObjArray* FairDbRelationalParSet<T>::GetByIds(std::vector<Int_t> ids, UInt_t rid)
{
  Int_t count = ids.size();
  return T::GetBy(
    [&ids, &count](T *inst) -> bool
      {
        for (Int_t i=0; i < count; i++)
        {
          if (ids[i] == inst->GetId())
          {
            return true;
          }
        }
        return false;
      });
}

template<typename T>
T* FairDbRelationalParSet<T>::FromJsonString(string jsonString)
{
  Json::Value json;
  string error;
  Json::CharReaderBuilder readerBuilder;
  Json::CharReader *reader = readerBuilder.newCharReader();
  Bool_t result = reader->parse(jsonString.data(), jsonString.data() + jsonString.size(), &json, &error);
  if (!result)
  {
    cout << "FairDbRelationalParSet<T>::FromJsonString" << endl;
    cout << error << endl;
    return NULL;
  }
  delete reader;

  return FromJson(json);
}

template<typename T>
T* FairDbRelationalParSet<T>::FromJson(Json::Value json)
{
  if (!json.isObject())
  {
    return NULL;
  }

  T* instance = new T();
  instance->FillFromJson(json);
  return instance;
}

template<typename T>
TObjArray* FairDbRelationalParSet<T>::FromJsonArray(Json::Value jsonArray)
{
  if (!jsonArray.isArray())
  {
    return NULL;
  }

  TObjArray *result = NULL;
  Int_t count = jsonArray.size();

  if (count)
  {
    result = new TObjArray(count);
    for (Int_t i = 0; i < count; i++)
    {
      result->Add(FromJson(jsonArray[i]));
    }
  }

  return result;
}

template<typename T>
string FairDbRelationalParSet<T>::ToJsonString()
{
  ostringstream stream;
  Json::StreamWriterBuilder writerBuilder;
  Json::StreamWriter *writer = writerBuilder.newStreamWriter();

  writer->write(ToJson(), &stream);
  delete writer;
  return stream.str();
}

template<typename T>
Json::Value FairDbRelationalParSet<T>::ToJson()
{
  Json::Value result;

  StoreToJson(result);

  return result;
}

template<typename T>
Json::Value FairDbRelationalParSet<T>::ToJsonArray(TObjArray* array)
{
  Json::Value jsonArray(Json::arrayValue);
  if (array)
  {
    Int_t count = array->GetEntries();
    jsonArray.resize(count);
    for (Int_t i = 0; i < count; i++)
    {
      jsonArray[i] = ((T*) array->At(i))->ToJson();
    }
  }

  return jsonArray;
}
