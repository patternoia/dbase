/**
* @file FairDbWtUserSessionStore.cxx
* @author Evgeny Lavrik <evgeny.lavrik@uni-tuebingen.de>
* @date 30.11.2017
**/

#include "FairDbWtUserSessionStore.h"

#include <Wt/Auth/PasswordVerifier>
#include <Wt/Auth/HashFunction>
#include <Wt/Auth/PasswordHash>
#include <Wt/WString>

FairDbWtUserSessionStore* FairDbWtUserSessionStore::fInstance  = 0;

FairDbWtUserSessionStore* FairDbWtUserSessionStore::Instance()
{
  if (!fInstance) {
    fInstance = new FairDbWtUserSessionStore();
  }
  return fInstance;
}

FairDbWtUserSessionStore::FairDbWtUserSessionStore()
  : fSessionAuth()
{
}

FairDbWtUserSessionStore::~FairDbWtUserSessionStore()
{
}

std::string FairDbWtUserSessionStore::GetToken(std::string email, std::string password)
{
  TObjArray *users = FairDbUser::GetByEmail(email, ValTimeStamp());
  if (!users) {
    return std::string();
  }

  FairDbUser *user = (FairDbUser *) users->First();
  if (user->GetStatus() != FairDbUserStatus::kActive) {
    return std::string();
  }

  Wt::Auth::PasswordVerifier *verifier = new Wt::Auth::PasswordVerifier();
  Wt::Auth::BCryptHashFunction *bcrypt = new Wt::Auth::BCryptHashFunction(7);
  verifier->addHashFunction(bcrypt);

  Wt::Auth::PasswordHash hash(bcrypt->name(), user->GetPasswordSalt(), user->GetPasswordHash());
  bool result = verifier->verify(password, hash);

  if (!result) {
    return std::string();
  }

  std::string token(verifier->hashPassword("").value());
  fSessionAuth[token] = user;

  delete users;
  return token;
}

FairDbUser* FairDbWtUserSessionStore::Login(std::string email, std::string password)
{
  TObjArray *users = FairDbUser::GetByEmail(email, ValTimeStamp());
  if (!users) {
    return nullptr;
  }

  FairDbUser *user = (FairDbUser *) users->First();
  if (user->GetStatus() != FairDbUserStatus::kActive) {
    return nullptr;
  }

  Wt::Auth::PasswordVerifier *verifier = new Wt::Auth::PasswordVerifier();
  Wt::Auth::BCryptHashFunction *bcrypt = new Wt::Auth::BCryptHashFunction(7);
  verifier->addHashFunction(bcrypt);

  Wt::Auth::PasswordHash hash(bcrypt->name(), user->GetPasswordSalt(), user->GetPasswordHash());
  bool result = verifier->verify(password, hash);

  if (!result) {
    return nullptr;
  }

  std::string token(verifier->hashPassword("").value());
  user->SetToken(token);
  fSessionAuth[token] = user;

  delete users;
  FairDbUser *copy = new FairDbUser();
  *copy = *user;
  return copy;
}

FairDbUser* FairDbWtUserSessionStore::GetUser(std::string token)
{
  if (fSessionAuth.find(token) == fSessionAuth.end()) {
    return nullptr;
  }

  FairDbUser *user = fSessionAuth[token];
  FairDbUser *copy = new FairDbUser();
  *copy = *user;
  return copy;
}

bool FairDbWtUserSessionStore::VerifyToken(std::string token)
{
  return fSessionAuth.find(token) != fSessionAuth.end() && fSessionAuth[token] != nullptr;
}

bool FairDbWtUserSessionStore::CheckUserRole(std::string token, FairDbUserRole::UserRole_t role)
{
  return VerifyToken(token) && fSessionAuth[token]->GetRole() >= role;
}
