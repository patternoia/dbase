#include "StsSensor.h"
#include "StsSensorBatch.h"

ClassImp(StsSensor);

static FairDbGenericParRegistry<StsSensor> ClassRegistry("StsSensor", FairDbDetector::kSts, DataType::kData);

#include "FairDbGenericParSet.tpl"
template class FairDbGenericParSet<StsSensor>;

#include "FairDbRelationalParSet.tpl"
template class FairDbRelationalParSet<StsSensor>;

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
  FairDbRelationalParSet(detid, dataid, name, title, context, ownership),
  fBatchId(0),
  fSUID("")
{
}

StsSensor::~StsSensor()
{
}

void StsSensor::Print()
{
  std::cout << "Sts Sensor Entity Instance:" << std::endl;

  std::cout << "Id = " << fId << std::endl;
  std::cout << "SUID = " << fSUID << std::endl;

  std::cout << std::endl;
}

const StsSensorBatch* StsSensor::GetBatch() {
  if (!fBatch) fBatch = StsSensorBatch::GetById(fBatchId);
  return fBatch;
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
  sql += "  SUID TEXT,";

  sql += "  primary key(SEQNO,ROW_ID))";
  return sql;
}

void StsSensor::Fill(FairDbResultPool& res_in,
                        const FairDbValRecord* valrec)
{
  res_in >> fId;
  res_in >> fBatchId;
  res_in >> fSUID;
}

void StsSensor::Store(FairDbOutTableBuffer& res_out,
                         const FairDbValRecord* valrec) const
{
  res_out << fId;
  res_out << fBatchId;
  res_out << fSUID;
}

StsSensor::StsSensor(const StsSensor& from){
  SetCompId(from.GetCompId());

  SetId(from.GetId());
  SetBatchId(from.GetBatchId());
  SetSUID(from.GetSUID());
}

StsSensor& StsSensor::operator=(const StsSensor& from){
  SetCompId(from.GetCompId());

  SetId(from.GetId());
  SetBatchId(from.GetBatchId());
  SetSUID(from.GetSUID());

  return *this;
}

TObjArray* StsSensor::GetByBatchId(Int_t BatchId, UInt_t rid)
{
  return GetBy(
    [&BatchId](StsSensor *inst) -> bool
      {
        return BatchId == inst->GetBatchId();
      });
}

TObjArray* StsSensor::GetBySUID(string SUID, UInt_t rid)
{
  return GetBy(
    [&SUID](StsSensor *inst) -> bool
      {
        return SUID == inst->GetSUID();
      });
}

void StsSensor::FillFromJson(Json::Value& json)
{
  SetId(json["Id"].asInt());
  SetBatchId(json["BatchId"].asInt());
  SetSUID(json["SUID"].asString());
}

void StsSensor::StoreToJson(Json::Value& json)
{
  json["Id"] = GetId();
  json["BatchId"] = fBatchId;
  json["SUID"] = fSUID;

  json["Batch"] = Json::Value(Json::nullValue);
}
