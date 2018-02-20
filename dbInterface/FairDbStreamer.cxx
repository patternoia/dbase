/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairDbStreamer.h"
#include "FairUtilStream.h"

#include "TClass.h"
#include "TBufferFile.h"
#include <iostream>                     // for cout
using std::cout;
using std::endl;


ClassImp(FairDbStreamer)

FairDbStreamer::FairDbStreamer()
  : TObject(),
    fString(""),
    fSize(0),
    fType(FairDb::kInt)
{
}

FairDbStreamer::FairDbStreamer(TString string)
  : TObject(),
    fString(string),
    fSize(0),
    fType(FairDb::kInt)
{
}

FairDbStreamer::FairDbStreamer(std::string string)
  : TObject(),
    fString(string),
    fSize(0),
    fType(FairDb::kInt)
{
}

FairDbStreamer::FairDbStreamer(const TObject* obj,FairDb::DataTypes type)
  : TObject()
    //    fString(FairDb::StreamAsString(obj,fSize)), 
    //    fSize(0),
    //    fType(type)
{
  fString = FairDb::StreamAsString(obj,fSize);
  fType=type;

}

FairDbStreamer::FairDbStreamer(const Int_t* iarr, Int_t size, FairDb::DataTypes type)
  : TObject(),
    fString(FairDb::StreamAsString(iarr,size)), 
    fSize(size),
    fType(type)
{
/*
  fString = FairDb::StreamAsString(iarr,size);
  fSize=size;
  fType=type;
*/
}

FairDbStreamer::FairDbStreamer(const UInt_t* iarr, Int_t size, FairDb::DataTypes type)
  : TObject(),
    fString(FairDb::StreamAsString(iarr,size)), 
    fSize(size),
    fType(type)
{
/*
  fString = FairDb::StreamAsString(iarr,size);
  fSize=size;
  fType=type;
*/
}


FairDbStreamer::FairDbStreamer(const Short_t* iarr, Int_t size, FairDb::DataTypes type)
  : TObject(),
    fString(FairDb::StreamAsString(iarr,size)), 
    fSize(size),
    fType(type)
{
/*
  fString = FairDb::StreamAsString(iarr,size);
  fSize=size;
  fType=type;
*/
}

FairDbStreamer::FairDbStreamer(const UShort_t* iarr, Int_t size, FairDb::DataTypes type)
  : TObject(),
    fString(FairDb::StreamAsString(iarr,size)), 
    fSize(size),
    fType(type)
{
/*
  fString = FairDb::StreamAsString(iarr,size);
  fSize=size;
  fType=type;
*/
}

FairDbStreamer::FairDbStreamer(const Bool_t* iarr, Int_t size, FairDb::DataTypes type)
  : TObject(),
    fString(FairDb::StreamAsString(iarr,size)), 
    fSize(size),
    fType(type)
{
/*
  fString = FairDb::StreamAsString(iarr,size);
  fSize=size;
  fType=type;
*/
}


FairDbStreamer::FairDbStreamer(const Float_t* iarr, Int_t size, FairDb::DataTypes type)
  : TObject(),
    fString(FairDb::StreamAsString(iarr,size)), 
    fSize(size),
    fType(type)
{
/*
  fString = FairDb::StreamAsString(iarr,size);
  fSize=size;
  fType=type;
*/
}

FairDbStreamer::FairDbStreamer(const Double_t* iarr, Int_t size, FairDb::DataTypes type)
  : TObject(),
    fString(FairDb::StreamAsString(iarr,size)), 
    fSize(size),
    fType(type)
{
/*
  fString = FairDb::StreamAsString(iarr,size);
  fSize=size;
  fType=type;
*/
}

FairDbStreamer::FairDbStreamer(const void* anyObject, std::string signature, FairDb::DataTypes type)
  : TObject(),
    fString(FairDb::StreamAsString(anyObject, signature)),
    fSize(),
    fType(type)
{

}


FairDbStreamer::FairDbStreamer(const FairDbStreamer& from)
  : TObject(from),fString(from.fString),fSize(0),fType()
{
}

FairDbStreamer& FairDbStreamer::operator=(const FairDbStreamer& from)
{

  if (this == &from) { return *this; }
  TObject::operator=(from);
  fString=from.fString;
  return *this;
}

FairDbStreamer::~FairDbStreamer()
{
}

void FairDbStreamer::Fill(Int_t* arr)
{
  // Decrypt str
  Int_t arr_size = GetSize();
  Int_t ll = arr_size * sizeof(Int_t);
  Char_t data[ll];
  // Decryption str
  std::string str_hex(fString.Data());
  Util::BinFromHex(str_hex,data);
  // Map to array
  Int_t r_array[arr_size];
  for(int i=0; i<arr_size; i++) { r_array[i]=0; }
  TBufferFile b_read(TBuffer::kRead,ll,data,kFALSE);
  b_read.ReadFastArray(r_array,arr_size);
  for(Int_t i=0; i<arr_size; i++) { arr[i]=r_array[i]; }
}


void FairDbStreamer::Fill(UInt_t* arr)
{
  // Decrypt str
  Int_t arr_size = GetSize();
  Int_t ll = arr_size * sizeof(UInt_t);
  Char_t data[ll];
  // Decryption str
  std::string str_hex(fString.Data());
  Util::BinFromHex(str_hex,data);
  // Map to array
  UInt_t r_array[arr_size];
  for(int i=0; i<arr_size; i++) { r_array[i]=0; }
  TBufferFile b_read(TBuffer::kRead,ll,data,kFALSE);
  b_read.ReadFastArray(r_array,arr_size);
  for(Int_t i=0; i<arr_size; i++) { arr[i]=r_array[i]; }
}


void FairDbStreamer::Fill(Short_t* arr)
{
  // Decrypt str
  Int_t arr_size = GetSize();
  Int_t ll = arr_size * sizeof(Short_t);
  Char_t data[ll];
  // Decryption str
  std::string str_hex(fString.Data());
  Util::BinFromHex(str_hex,data);
  // Map to array
  Short_t r_array[arr_size];
  for(int i=0; i<arr_size; i++) { r_array[i]=0; }
  TBufferFile b_read(TBuffer::kRead,ll,data,kFALSE);
  b_read.ReadFastArray(r_array,arr_size);
  for(Int_t i=0; i<arr_size; i++) { arr[i]=r_array[i]; }
}

void FairDbStreamer::Fill(UShort_t* arr)
{
  // Decrypt str
  Int_t arr_size = GetSize();
  Int_t ll = arr_size * sizeof(UShort_t);
  Char_t data[ll];
  // Decryption str
  std::string str_hex(fString.Data());
  Util::BinFromHex(str_hex,data);
  // Map to array
  UShort_t r_array[arr_size];
  for(int i=0; i<arr_size; i++) { r_array[i]=0; }
  TBufferFile b_read(TBuffer::kRead,ll,data,kFALSE);
  b_read.ReadFastArray(r_array,arr_size);
  for(Int_t i=0; i<arr_size; i++) { arr[i]=r_array[i]; }
}


void FairDbStreamer::Fill(Bool_t* arr)
{
  // Decrypt str
  Int_t arr_size = GetSize();
  Int_t ll = arr_size * sizeof(Bool_t);
  Char_t data[ll];
  // Decryption str
  std::string str_hex(fString.Data());
  Util::BinFromHex(str_hex,data);
  // Map to array
  Bool_t r_array[arr_size];
  for(int i=0; i<arr_size; i++) { r_array[i]=0; }
  TBufferFile b_read(TBuffer::kRead,ll,data,kFALSE);
  b_read.ReadFastArray(r_array,arr_size);
  for(Int_t i=0; i<arr_size; i++) { arr[i]=r_array[i]; }
}

void FairDbStreamer::Fill(Float_t* arr)
{
  // Decrypt str
  Int_t arr_size = GetSize();
  Int_t ll = arr_size * sizeof(Float_t);
  Char_t data[ll];
  // Decryption str
  std::string str_hex(fString.Data());
  Util::BinFromHex(str_hex,data);
  // Map to array
  Float_t r_array[arr_size];
  for(int i=0; i<arr_size; i++) { r_array[i]=0; }
  TBufferFile b_read(TBuffer::kRead,ll,data,kFALSE);
  b_read.ReadFastArray(r_array,arr_size);
  for(Int_t i=0; i<arr_size; i++) { arr[i]=r_array[i]; }
}

void FairDbStreamer::Fill(Double_t* arr)
{
  // Decrypt str
  Int_t arr_size = GetSize();
  Int_t ll = arr_size * sizeof(Double_t);
  Char_t data[ll];
  // Decryption str
  std::string str_hex(fString.Data());
  Util::BinFromHex(str_hex,data);
  // Map to array
  Double_t r_array[arr_size];
  for(int i=0; i<arr_size; i++) { r_array[i]=0.; }
  TBufferFile b_read(TBuffer::kRead,ll,data,kFALSE);
  b_read.ReadFastArray(r_array,arr_size);
  for(Int_t i=0; i<arr_size; i++) { arr[i]=r_array[i];}
}



void FairDbStreamer::Fill(TObject* obj)
{
  if (!obj || fString.IsNull())
    return;

  // <DB> changed according to Jorg Förtsch
  //      date 28.03.2017
  // Decryption str
  std::string str_hex(fString.Data());
  size_t halb = str_hex.length()/2;
  UChar_t read_buf[halb];
  Util::BinFromHex(str_hex,read_buf);
  TBufferFile b_read(TBuffer::kRead,halb, read_buf,kFALSE);
  obj->Streamer(b_read);
}

void FairDbStreamer::Fill(void* anyObject, std::string signature)
{
  if (fString.IsNull())
    return;

  std::string str_hex(fString.Data());
  size_t halb = str_hex.length()/2;
  UChar_t read_buf[halb];
  Util::BinFromHex(str_hex,read_buf);
  TBufferFile b_read(TBuffer::kRead,halb, read_buf,kFALSE);

  TClass *cls = TClass(signature.c_str()).GetActualClass(anyObject);
  cls->Streamer(anyObject, b_read);
}


/// vector<>
void FairDbStreamer::Fill(std::vector<Bool_t> &vector)
{
  Fill(&vector, "std::vector<Bool_t>");
}

void FairDbStreamer::Fill(std::vector<Short_t> &vector)
{
  Fill(&vector, "std::vector<Short_t>");
}

void FairDbStreamer::Fill(std::vector<UShort_t> &vector)
{
  Fill(&vector, "std::vector<UShort_t>");
}

void FairDbStreamer::Fill(std::vector<Int_t> &vector)
{
  Fill(&vector, "std::vector<Int_t>");
}

void FairDbStreamer::Fill(std::vector<UInt_t> &vector)
{
  Fill(&vector, "std::vector<UInt_t>");
}

void FairDbStreamer::Fill(std::vector<Float_t> &vector)
{
  Fill(&vector, "std::vector<Float_t>");
}

void FairDbStreamer::Fill(std::vector<Double_t> &vector)
{
  Fill(&vector, "std::vector<Double_t>");
}

/// vector< vector<> >
void FairDbStreamer::Fill(std::vector< std::vector<Bool_t> > &vector)
{
  Fill(&vector, "std::vector< std::vector<Bool_t> >");
}

void FairDbStreamer::Fill(std::vector< std::vector<Short_t> > &vector)
{
  Fill(&vector, "std::vector< std::vector<Short_t> >");
}

void FairDbStreamer::Fill(std::vector< std::vector<UShort_t> > &vector)
{
  Fill(&vector, "std::vector< std::vector<UShort_t> >");
}

void FairDbStreamer::Fill(std::vector< std::vector<Int_t> > &vector)
{
  Fill(&vector, "std::vector< std::vector<Int_t> >");
}

void FairDbStreamer::Fill(std::vector< std::vector<UInt_t> > &vector)
{
  Fill(&vector, "std::vector< std::vector<UInt_t> >");
}

void FairDbStreamer::Fill(std::vector< std::vector<Float_t> > &vector)
{
  Fill(&vector, "std::vector< std::vector<Float_t> >");
}

void FairDbStreamer::Fill(std::vector< std::vector<Double_t> > &vector)
{
  Fill(&vector, "std::vector< std::vector<Double_t> >");
}

/// map
void FairDbStreamer::Fill(std::map<std::string, TObject> &map)
{
  Fill(&map, "std::map<std::string, TObject>");
}
