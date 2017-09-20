#include "FairDbCbmStsREST.h"

#include <WServer>
#include <iostream>

#include "StsSensorResource.h"
#include "StsSensorBatchResource.h"

#include "TSystem.h"

int main(int argc, char **argv)
{
  // gProgName is not initialized when running wt; makes FairDbLogEntry to hang
  gSystem->SetProgname(argv[0]);
  try {
    Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);

    new StsSensorResource(server);
    new StsSensorBatchResource(server);

    server.run();
  } catch (Wt::WServer::Exception& e) {
    std::cout << "Server Exception: " <<  e.what() << std::endl;
  } catch (std::exception &e) {
    std::cout << "Exception: " <<  e.what() << std::endl;
  }
}
