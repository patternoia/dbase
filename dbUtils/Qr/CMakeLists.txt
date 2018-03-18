 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################

# Create a library called "FairDbQr"

Message("-- Compiling FairDbQr")

set(INCLUDE_DIRECTORIES
  ${CMAKE_SOURCE_DIR}/dbUtils/Qr
)

include_directories(${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
)

link_directories(${LINK_DIRECTORIES})

set(NO_DICT_SRCS
  ${CMAKE_SOURCE_DIR}/db3rdParty/qr/BitBuffer.cpp
  ${CMAKE_SOURCE_DIR}/db3rdParty/qr/QrCode.cpp
  ${CMAKE_SOURCE_DIR}/db3rdParty/qr/QrSegment.cpp
)

set(SRCS
  FairDbQr.cxx
)

set(NO_DICT_HEADERS
  ${CMAKE_SOURCE_DIR}/db3rdParty/qr/BitBuffer.hpp
  ${CMAKE_SOURCE_DIR}/db3rdParty/qr/QrCode.hpp
  ${CMAKE_SOURCE_DIR}/db3rdParty/qr/QrSegment.hpp
)

set(HEADERS
  FairDbQr.h
)

install(FILES "${CMAKE_SOURCE_DIR}/db3rdParty/qr/BitBuffer.hpp" DESTINATION include/qr)
install(FILES "${CMAKE_SOURCE_DIR}/db3rdParty/qr/QrCode.hpp" DESTINATION include/qr)
install(FILES "${CMAKE_SOURCE_DIR}/db3rdParty/qr/QrSegment.hpp" DESTINATION include/qr)


set(LINKDEF FairDbQrLinkDef.h)
set(LIBRARY_NAME FairDbQr)

set(DEPENDENCIES
  FairDB Core Hist
)

GENERATE_LIBRARY()
