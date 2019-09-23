#include <iostream>
#include <string>
#include <sqlite3.h>

#define SQLITE_OK 0 
using namespace std;


int callback(void *NotUsed, int argc, char **argv, char **azColName)
{

    for(int i = 0; i < argc; i++) 
    {    
        cout << azColName[i] << ": " << argv[i] << endl;
    }
    cout << endl;
    return 0;
}
  
int main() {

    // Pointer to SQLite connection
    sqlite3 *db;

    // Save any error messages
    char *zErrMsg = 0;

    // Save the result of opening the file
    int rc;

    // Save any SQL
    string sql;

    // Save the result of opening the file
    rc = sqlite3_open("example.db", &db);
    
    if( rc ){
        // Show an error message
        cout << "DB Error: " << sqlite3_errmsg(db) << endl;
        // Close the connection
        sqlite3_close(db);
        // Return an error
        return(1);
    }

    // Save SQL to create a table
    
    /*sql = "CREATE TABLE IF NOT EXISTS students(ID INT PRIMARY KEY NOT NULL);";*/
    cin>>sql ;
    // Run the SQL (convert the string to a C-String with c_str() )
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    if( rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else 
    {
          fprintf(stdout, "Records created successfully\n");
    }
    // Close the SQL connection
    sqlite3_close(db);
    
    return 0;
}