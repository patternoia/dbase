/**
* @file StsSensor.h
* @brief Sts Sensor Entity FairDb class. Generated automatically
* @author Generator by Evgeny Lavrik <evgeny.lavrik@uni-tuebingen.de>
* @date 20.9.2017
**/

#ifndef STSSENSOR_H
#define STSSENSOR_H

#include "TBits.h"

#include "DataType.h"
#include "FairDbRelationalParSet.h"
#include "TString.h"
#include "TObjArray.h"
#include "Rtypes.h"

#ifndef __CINT__
#include "json/json.h"
#endif

#include <iostream>
#include <string>

class StsSensorBatch;

class StsSensor : public FairDbRelationalParSet<StsSensor>
{
  using TObject::Compare;

  public :
    StsSensor(FairDbDetector::Detector_t detid = FairDbDetector::kSts,
          DataType::DataType_t dataid = DataType::kData,
          const char* name = "StsSensor",
          const char* title = "Sts Sensor Entity",
          const char* context = "StsSensorDefaultContext",
          Bool_t ownership=kTRUE);

    virtual ~StsSensor(void);
    StsSensor(const StsSensor& from);
    StsSensor& operator=(const StsSensor& from);

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

    StsSensorBatch* GetBatch();

    void SetBatch(StsSensorBatch& value);

    Int_t GetId() const { return fId; }
    Int_t GetBatchId() const { return fBatchId; }
    TBits* GetBits() const { return fBits; }
    string GetSUID() const { return fSUID; }
    Int_t GetSize() const { return fSize; }
    Double_t* GetArray() const { return fArray; }

    void SetId(Int_t value) { fId = value; SetCompId(fId); }
    void SetBatchId(Int_t value) { fBatchId = value; }
    void SetBits(TBits* value) { fBits = value; }
    void SetSUID(string value) { fSUID = value; }
    void SetSize(Int_t value) { fSize = value; }
    void SetArray(Double_t* value) { if (!fArray) fArray = new Double_t[fSize]; for (Int_t i = 0; i < fSize; i++ ) { fArray[i] = value[i]; } }

    static TObjArray* GetByBatchId(Int_t BatchId, UInt_t rid=0);
    static TObjArray* GetBySUID(string SUID, UInt_t rid=0);

#ifndef __CINT__
    virtual void FillFromJson(Json::Value json);
    virtual void StoreToJson(Json::Value& json);
#endif

  private:
    StsSensorBatch* fBatch; //! transient relation to StsSensorBatch, Has One

    Int_t fId;
    Int_t fBatchId;
    TBits* fBits;
    string fSUID;
    Int_t fSize;
    Double_t* fArray; //[fSize]

    ClassDef(StsSensor, 1); // ROOT class definition
};

#endif /* !STSSENSOR_H */

