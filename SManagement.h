#include<iostream>
#include<sqlite3.h>
#include<string.h>
#include<stdlib.h>

using namespace std ;

class DB
{
    sqlite3* db ;
    char* zErrmsg = 0 ;
    sqlite3_stmt* stmt ; // Compiled SQL statement

    int rc ;

    static int callback(void* NotUsed, int argc, char** argv, char** azColName) 
        {
        for(int i = 0; i < argc; i++) 
        {    
            cout << azColName[i] << ": " << argv[i] << endl;
        }
        cout << endl;
        return 0;
    }

    public:

    DB();
    void createtable();
    void insertdata( char* , char* , char* );
    void showtable();
    void deleteEntry( char* ) ;
    void checkerr();
    void closeDB() ;
};

DB :: DB()
{
    rc = sqlite3_open("Student.db", &db ) ;
    void checkerr() ;
}

void DB :: checkerr()
{
    if(rc)
    {
        cout<<"\n\nDB error:"<<sqlite3_errmsg(db)<<"\n\n" ;
        closeDB() ;
    }
}



void DB :: createtable()
{
    char* zErrmsg = 0 ;
    int rc = 0 ;
    string sql ;
    sql = "CREATE TABLE IF NOT EXISTS  Student("
          "ID INT PRIMARY KEY NOT NULL,"
          "NAME VARCHAR(40) NOT NULL,"
          "TOTAL_MARKS INT NOT NULL);" ;
    rc = sqlite3_exec( db , sql.c_str() , callback , 0 , &zErrmsg ) ;    
    if( rc != SQLITE_OK )
    {
        cout<<"\n\n" ;
        fprintf(stderr, "SQL error: %s\n", zErrmsg);
        sqlite3_free(zErrmsg);
    }
    else
    {
          fprintf(stdout, "Table created successfully with attributes : ID, Name, Total Marks\n\n");
    }
} 

void DB :: insertdata( char* id , char* name, char* score )
{
    char* query ;
    asprintf( &query, "INSERT INTO Student(ID, NAME, TOTAL_MARKS) VALUES( ' %s ',' %s ',' %s ' );",id, name, score ) ;
    //Prepare query
    sqlite3_prepare( db, query, strlen(query), &stmt, NULL ) ;
    //Test it
    rc = sqlite3_step(stmt) ;
    checkerr() ;
}

void DB :: deleteEntry( char* x )
{
    char* query ;
    asprintf( &query, "DELETE FROM TABLE Student WHERE ID = ''%s';", x ) ;  			   
    sqlite3_prepare( db, query, strlen(query), &stmt, NULL ) ;
    rc = sqlite3_step(stmt) ;
    checkerr() ;
}

void DB :: showtable()
{
    string sql ;
    sql = "SELECT * FROM 'Student';" ;
    rc = sqlite3_exec( db , sql.c_str(),  callback , 0 , &zErrmsg ) ;
    checkerr() ;
}

void DB :: closeDB()
{
    sqlite3_close(db) ;
}

