/**
* @file StsSensorBatch.h
* @brief Sts Sensor Batch Entity FairDb class. Generated automatically
* @author Generator by Evgeny Lavrik <evgeny.lavrik@uni-tuebingen.de>
* @date 21.9.2017
**/

#ifndef STSSENSORBATCH_H
#define STSSENSORBATCH_H

#include "FairDbRelationalParSet.h"

#ifndef __CINT__
#include "json/json.h"
#endif


class StsSensor;

class StsSensorBatch : public FairDbRelationalParSet<StsSensorBatch>
{
  using TObject::Compare;

  public :
    StsSensorBatch(FairDbDetector::Detector_t detid = FairDbDetector::kSts,
          DataType::DataType_t dataid = DataType::kData,
          const char* name = "StsSensorBatch",
          const char* title = "Sts Sensor Batch Entity",
          const char* context = "StsSensorDefaultContext",
          Bool_t ownership=kTRUE);

    StsSensorBatch(const StsSensorBatch& from);
    StsSensorBatch& operator=(const StsSensorBatch& from);
    virtual ~StsSensorBatch(void);

    // Dump Object
    void   Print();

    // Add-ons: SQL descriptors for the parameter class
    virtual std::string GetTableDefinition(const char* Name = 0);

    // Atomic IO (intrinsic)
    virtual void Fill(FairDbResultPool& res_in,
                      const FairDbValRecord* valrec);
    virtual void Store(FairDbOutTableBuffer& res_out,
                       const FairDbValRecord* valrec) const;

    UInt_t GetIndex(UInt_t /*def*/) const { return fId; }

    TObjArray* GetSensors();


    Int_t GetId() const { return fId; }
    string GetNumber() const { return fNumber; }
    ValTimeStamp GetDate() const { return fDate; }
    string GetComment() const { return fComment; }

    void SetId(Int_t value) { fId = value; SetCompId(fId); }
    void SetNumber(string value) { fNumber = value; }
    void SetDate(ValTimeStamp value) { fDate = value; }
    void SetComment(string value) { fComment = value; }


#ifndef __CINT__
    virtual void FillFromJson(Json::Value json);
    virtual void StoreToJson(Json::Value& json);
#endif

  private:
    TObjArray* fSensors; //! transient relation to StsSensor, Has Many

    string fNumber;
    ValTimeStamp fDate;
    string fComment;

    ClassDef(StsSensorBatch, 1); // ROOT class definition
};

#endif /* !STSSENSORBATCH_H */

