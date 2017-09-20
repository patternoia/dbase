Message("-- Wt is FOUND .... FairDbCbmStsREST will be compiled ... ")

set(INCLUDE_DIRECTORIES
   ${BASE_INCLUDE_DIRECTORIES}
   ${ROOT_INCLUDE_DIR}
   ${Boost_INCLUDE_DIRS}
   ${Wt_INCLUDE_DIR}
   ${Wt_INCLUDE_DIR}/Wt

   ${CMAKE_SOURCE_DIR}/dbase/db3rdParty/jsoncpp/
   ${CMAKE_SOURCE_DIR}/dbase/dbExamples/FairDbCbmSts/src
 )

include_directories(${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
    ${ROOT_LIBRARY_DIR}
    ${Boost_LIBRARY_DIRS}
)

link_directories(${LINK_DIRECTORIES})

set(HEADERS
  FairDbCbmStsREST.h

  StsSensorResource.h
  StsSensorBatchResource.h
)

set(SRCS
  FairDbCbmStsREST.cxx

  StsSensorResource.cxx
  StsSensorBatchResource.cxx
)

set(LIBRARY_NAME FairDbCbmStsREST)

set(DEPENDENCIES
  RHTTP
  Base FairDB ParBase
  boost_thread boost_system boost_serialization boost_signals boost_locale
  boost_date_time  boost_regex boost_program_options boost_signals boost_random boost_system
  ${Wt_LIBRARY} ${Wt_HTTP_LIBRARY} ${Wt_LIBRARIES}
  FairDbCbmSts
)

GENERATE_LIBRARY()

set(Exe_Names
  FairDbCbmStsREST.wt
)

set(Exe_Source
  FairDbCbmStsREST.cxx
)

list(LENGTH Exe_Names _length)
math(EXPR _length ${_length}-1)

foreach(_file RANGE 0 ${_length})
  list(GET Exe_Names ${_file} _name)
  list(GET Exe_Source ${_file} _src)
  set(EXE_NAME ${_name})
  set(SRCS ${_src})
  set(DEPENDENCIES FairDbCbmStsREST)
  GENERATE_EXECUTABLE()
endforeach(_file RANGE 0 ${_length})

