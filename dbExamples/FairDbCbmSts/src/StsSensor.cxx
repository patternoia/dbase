/**
* @file StsSensor.cxx
* @brief Sts Sensor Entity FairDb class. Generated automatically
* @author Generator by Evgeny Lavrik <evgeny.lavrik@uni-tuebingen.de>
* @date 20.9.2017
**/

#include "StsSensor.h"
#include "StsSensorBatch.h"

ClassImp(StsSensor);

static FairDbGenericParRegistry<StsSensor> ClassRegistry("StsSensor", FairDbDetector::kSts, DataType::kData);

#include "FairDbRelationalParSet.tpl"
template class FairDbRelationalParSet<StsSensor>;

#include "FairDbGenericParSet.tpl"
template class FairDbGenericParSet<StsSensor>;

#include "FairDbReader.tpl"
template class FairDbReader<StsSensor>;

#include "FairDbWriter.tpl"
template class FairDbWriter<StsSensor>;

StsSensor::StsSensor(FairDbDetector::Detector_t detid,
              DataType::DataType_t dataid,
              const char* name,
              const char* title,
              const char* context,
              Bool_t ownership):
  FairDbRelationalParSet<StsSensor>(detid, dataid, name, title, context, ownership),
  fBatchId(0),
  fBatch(NULL),
  fBits(NULL),
  fSUID(""),
  fSize(0),
  fArray(NULL)
{
}

StsSensor::~StsSensor()
{
  delete fBatch;
  delete fBits;
  delete[] fArray;
}

void StsSensor::Print()
{
  std::cout << "Sts Sensor Entity Instance:" << std::endl;

  std::cout << "Id = " << fId << std::endl;
  std::cout << "BatchId = " << fBatchId << std::endl;
  std::cout << "Bits = " << fBits << std::endl;
  std::cout << "SUID = " << fSUID << std::endl;
  std::cout << "Size = " << fSize << std::endl;
  std::cout << "Array = " << fArray << std::endl;

  std::cout << std::endl;
}

StsSensorBatch* StsSensor::GetBatch() {
  if (!fBatch) fBatch = StsSensorBatch::GetById(fBatchId);
  return fBatch;
}

void StsSensor::SetBatch(StsSensorBatch& value) {
  delete fBatch;
  fBatch = new StsSensorBatch(value);
  fBatchId = value.GetId();
}

string StsSensor::GetTableDefinition(const char* Name)
{
  string sql("create table ");
  if ( Name ) { sql += Name; }
  else { sql += GetTableName(); }
  sql += "( SEQNO             INT NOT NULL,";
  sql += "  ROW_ID            INT NOT NULL,";

  sql += "  ID INT NOT NULL,";
  sql += "  BATCH_ID INT,";
  sql += "  BITS TEXT,";
  sql += "  SUID TEXT,";
  sql += "  SIZE INT,";
  sql += "  ARRAY TEXT,";

  sql += "  primary key(SEQNO,ROW_ID))";
  return sql;
}

void StsSensor::Fill(FairDbResultPool& res_in,
                        const FairDbValRecord* valrec)
{
  FairDbStreamer BitsStreamer(fBits);
  FairDbStreamer ArrayStreamer(fArray, 0);

  res_in >> fId;
  res_in >> fBatchId;
  res_in >> BitsStreamer;
  res_in >> fSUID;
  res_in >> fSize;
  res_in >> ArrayStreamer;

  if (!BitsStreamer.AsString().IsNull())
  {
    if (!fBits) fBits = new TBits();

    BitsStreamer.Fill(fBits);
  }

  if (!ArrayStreamer.AsString().IsNull())
  {
    if (!fArray) fArray = new Double_t[fSize];
    ArrayStreamer.SetSize(fSize);
    ArrayStreamer.Fill(fArray);
  }
}

void StsSensor::Store(FairDbOutTableBuffer& res_out,
                         const FairDbValRecord* valrec) const
{
  FairDbStreamer BitsStreamer(fBits);
  FairDbStreamer ArrayStreamer(fArray, fSize);

  res_out << fId;
  res_out << fBatchId;
  res_out << BitsStreamer;
  res_out << fSUID;
  res_out << fSize;
  res_out << ArrayStreamer;
}

StsSensor::StsSensor(const StsSensor& from){
  SetCompId(from.GetCompId());

  SetId(from.GetId());
  SetBatchId(from.GetBatchId());
  SetBits(from.GetBits());
  SetSUID(from.GetSUID());
  SetSize(from.GetSize());
  SetArray(from.GetArray());
}

StsSensor& StsSensor::operator=(const StsSensor& from){
  SetCompId(from.GetCompId());

  SetId(from.GetId());
  SetBatchId(from.GetBatchId());
  SetBits(from.GetBits());
  SetSUID(from.GetSUID());
  SetSize(from.GetSize());
  SetArray(from.GetArray());

  return *this;
}

TObjArray* StsSensor::GetByBatchId(Int_t BatchId, UInt_t rid)
{
  return StsSensor::GetBy(
    [&BatchId](StsSensor *inst) -> bool
      {
        return BatchId == inst->GetBatchId();
      });
}

TObjArray* StsSensor::GetBySUID(string SUID, UInt_t rid)
{
  return StsSensor::GetBy(
    [&SUID](StsSensor *inst) -> bool
      {
        return SUID == inst->GetSUID();
      });
}

void StsSensor::FillFromJson(Json::Value json)
{
  SetId(json["Id"].asInt());
  SetBatchId(json["BatchId"].asInt());
  SetSUID(json["SUID"].asString());
  SetSize(json["Size"].asInt());

  const Json::Value ArrayArr = json["Array"];
  if (!ArrayArr.isNull())
  {
    Int_t count = ArrayArr.size();
    Double_t* TempArray = new Double_t[count];
    for (Int_t i = 0; i < count; i++)
    {
      TempArray[i] = ArrayArr[i].asDouble();
    }
    SetArray(TempArray);
    delete[] TempArray;
  }
}

void StsSensor::StoreToJson(Json::Value& json)
{
  json["Id"] = fId;
  json["BatchId"] = fBatchId;
  json["SUID"] = fSUID;
  json["Size"] = fSize;

  if (fArray)
  {
    Json::Value ArrayArr(Json::arrayValue);
    ArrayArr.resize(fSize);
    for (Int_t i = 0; i < fSize; ++i)
    {
      ArrayArr[i] = fArray[i];
    }
    json["Array"] = ArrayArr;
  } else {
    json["Array"] = Json::Value(Json::nullValue);
  }

  json["Batch"] = Json::Value(Json::nullValue);
  json["Bits"] = Json::Value(Json::nullValue);

}

