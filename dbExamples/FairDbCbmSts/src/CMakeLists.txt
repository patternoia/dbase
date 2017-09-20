# Create a library called "FairDbCbmSts" which includes the source files given in
# the array .

Set(INCLUDE_DIRECTORIES
  ${BASE_INCLUDE_DIRECTORIES}
  
  ${CMAKE_SOURCE_DIR}/dbase/db3rdParty/jsoncpp/
  ${CMAKE_SOURCE_DIR}/dbase/dbExamples/FairDbCbmSts/src
)

Set(SYSTEM_INCLUDE_DIRECTORIES
  ${Boost_INCLUDE_DIR}
)

Include_Directories(${INCLUDE_DIRECTORIES})
Include_Directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

Set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
)

Link_Directories(${LINK_DIRECTORIES})

set(HEADERS
  StsSensor.h
  StsSensorBatch.h
)

set(SRCS
  StsSensor.cxx
  StsSensorBatch.cxx
)

set(LINKDEF FairDbCbmStsLinkDef.h)
Set(LIBRARY_NAME FairDbCbmSts)

Set(DEPENDENCIES Base ParBase FairDB)

GENERATE_LIBRARY()

