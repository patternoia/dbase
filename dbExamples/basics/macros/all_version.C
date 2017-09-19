
Int_t  all_version()
{
  // Create a Runtime Database singleton.
  FairRuntimeDb* db = FairRuntimeDb::instance();

  // Set the SQL IO as first input
  FairParTSQLIo* inp = new FairParTSQLIo();
  
  FairDbConnectionPool c_pool = inp->GetConnections();
  
  FairDbConnection* con(c_pool.GetConnection(0));

  TSQLServer* server(con->GetServer());
  server->EnableErrorOutput();
  TSQLStatement* stmtTSQL(server->Statement("select * from TUTPARDEFAULTVAL order by TIMESTART desc;"));
  stmtTSQL->Process();
  stmtTSQL->StoreResult();
  while ( stmtTSQL->NextResultRow() ) {
    cout << "Table info:" 
         << " col 0: " << stmtTSQL->GetInt(0)
         << " col 1: " << stmtTSQL->GetString(1)
         << " col 2: " << stmtTSQL->GetString(2)
         << " col 3: " << stmtTSQL->GetInt(3)
         << " col 4: " << stmtTSQL->GetInt(4)
         << " col 5: " << stmtTSQL->GetInt(5)
         << " col 6: " << stmtTSQL->GetString(6)
         << " col 7: " << stmtTSQL->GetString(7)
         << " col 8: " << stmtTSQL->GetString(8)
         << endl;
  }
  delete stmtTSQL;
  stmtTSQL = 0;
  
  if (db) delete db;
  return 0;
}
