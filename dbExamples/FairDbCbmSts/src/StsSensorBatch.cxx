/**
* @file StsSensorBatch.cxx
* @brief Sts Sensor Batch Entity FairDb class. Generated automatically
* @author Generator by Evgeny Lavrik <evgeny.lavrik@uni-tuebingen.de>
* @date 20.9.2017
**/

#include "StsSensorBatch.h"
#include "StsSensor.h"

ClassImp(StsSensorBatch);

static FairDbGenericParRegistry<StsSensorBatch> ClassRegistry("StsSensorBatch", FairDbDetector::kSts, DataType::kData);

#include "FairDbRelationalParSet.tpl"
template class FairDbRelationalParSet<StsSensorBatch>;

#include "FairDbGenericParSet.tpl"
template class FairDbGenericParSet<StsSensorBatch>;

#include "FairDbReader.tpl"
template class FairDbReader<StsSensorBatch>;

#include "FairDbWriter.tpl"
template class FairDbWriter<StsSensorBatch>;

StsSensorBatch::StsSensorBatch(FairDbDetector::Detector_t detid,
              DataType::DataType_t dataid,
              const char* name,
              const char* title,
              const char* context,
              Bool_t ownership):
  FairDbRelationalParSet<StsSensorBatch>(detid, dataid, name, title, context, ownership),
  fSensors(NULL),
  fNumber(""),
  fDate(ValTimeStamp::GetBOT()),
  fComment("")
{
}

StsSensorBatch::~StsSensorBatch()
{
  delete fSensors;
}

void StsSensorBatch::Print()
{
  std::cout << "Sts Sensor Batch Entity Instance:" << std::endl;

  std::cout << "Id = " << fId << std::endl;
  std::cout << "Number = " << fNumber << std::endl;
  std::cout << "Date = " << fDate << std::endl;
  std::cout << "Comment = " << fComment << std::endl;

  std::cout << std::endl;
}

TObjArray* StsSensorBatch::GetSensors()
{
  if (!fSensors) fSensors = StsSensor::GetByBatchId(fId);
  return fSensors;
}

string StsSensorBatch::GetTableDefinition(const char* Name)
{
  string sql("create table ");
  if ( Name ) { sql += Name; }
  else { sql += GetTableName(); }
  sql += "( SEQNO             INT NOT NULL,";
  sql += "  ROW_ID            INT NOT NULL,";

  sql += "  ID INT NOT NULL,";
  sql += "  NUMBER TEXT,";
  sql += "  DATE DATETIME,";
  sql += "  COMMENT TEXT,";

  sql += "  primary key(SEQNO,ROW_ID))";
  return sql;
}

void StsSensorBatch::Fill(FairDbResultPool& res_in,
                        const FairDbValRecord* valrec)
{

  res_in >> fId;
  res_in >> fNumber;
  res_in >> fDate;
  res_in >> fComment;
}

void StsSensorBatch::Store(FairDbOutTableBuffer& res_out,
                         const FairDbValRecord* valrec) const
{

  res_out << fId;
  res_out << fNumber;
  res_out << fDate;
  res_out << fComment;
}

StsSensorBatch::StsSensorBatch(const StsSensorBatch& from){
  SetCompId(from.GetCompId());

  SetId(from.GetId());
  SetNumber(from.GetNumber());
  SetDate(from.GetDate());
  SetComment(from.GetComment());
}

StsSensorBatch& StsSensorBatch::operator=(const StsSensorBatch& from){
  SetCompId(from.GetCompId());

  SetId(from.GetId());
  SetNumber(from.GetNumber());
  SetDate(from.GetDate());
  SetComment(from.GetComment());

  return *this;
}

TObjArray* StsSensorBatch::GetByNumber(string Number, UInt_t rid)
{
  return StsSensorBatch::GetBy(
    [&Number](StsSensorBatch *inst) -> bool
      {
        return Number == inst->GetNumber();
      });
}

void StsSensorBatch::FillFromJson(Json::Value json)
{
  SetId(json["Id"].asInt());
  SetNumber(json["Number"].asString());
  SetDate(json["Date"].asInt());
  SetComment(json["Comment"].asString());


}

void StsSensorBatch::StoreToJson(Json::Value& json)
{
  json["Id"] = fId;
  json["Number"] = fNumber;
  json["Date"] = (Int_t) fDate;
  json["Comment"] = fComment;


  json["Sensors"] = Json::Value(Json::nullValue);

}

