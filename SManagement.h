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
    void insertdata( int , string, int );
    void showtable();
    void deleteEntry( int ) ;
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

void DB :: insertdata( int id , string name, int score )
{
    string sql ;
    sql = "INSERT INTO Student( ID , NAME, TOTAL_MARKS ) VALUES('"+ to_string(id) +"' , '" +name+ "'," + to_string(score) + ")";
    rc = sqlite3_exec( db , sql.c_str() , callback , 0 , &zErrmsg ) ;
    checkerr() ;
}

void DB :: deleteEntry( int x )
{
    string sql ;
    sql = "DELETE FROM Student WHERE ID = '"+ to_string(x) + "' ; " ;
    rc = sqlite3_exec( db , sql.c_str() , callback , 0 , &zErrmsg ) ;

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

