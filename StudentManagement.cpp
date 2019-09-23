#include<iostream>
#include<string>
#include<sqlite3.h>

using namespace std ;

sqlite3* db ;
char* zErrmsg = 0 ;

int rc = sqlite3_open("student.db", &db ) ;
 
int callback(void *NotUsed, int argc, char **argv, char **azColName)
{

    for(int i = 0; i < argc; i++) 
    {    
        cout << azColName[i] << ": " << argv[i] << endl;
    }
    cout << endl;
    return 0;
}

int createtable()
{
    char* zErrmsg = 0 ;
    int rc = 0 ;
    string sql ;
    string table = "Student" ;
    sql = "CREATE TABLE IF NOT EXISTS  '"+table+"'("
          "ID INT PRIMARY KEY NOT NULL,"
          "NAME VARCHAR(40) NOT NULL,"
          "ROLL_NUMBER INT NOT NULL,"
          "TOTAL_MARKS INT NOT NULL);" ;
    rc = sqlite3_exec( db , sql.c_str() , callback , 0 , &zErrmsg ) ;    
    if( rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrmsg);
        sqlite3_free(zErrmsg);
    }
    else 
    {
          fprintf(stdout, "Records created successfully\n");
    }
    
}

int insert()
{
    int id , roll_no , marks ;
    string name , sql;
    createtable() ;
    cout<<"Enter details of Student:";
    cout<<"\nID: " ;
    cin>>id ;
    cout<<"Name: " ; 
    cin>>name ;
    cout<<"Roll Number: " ;
    cin>>roll_no ;
    cout<<"Total Marks: " ;
    cin>>marks ;


    sql = "INSERT INTO Student( ID , NAME, ROLL_NUMBER, TOTAL_MARKS ) VALUES('"+ to_string(id) +"' , '" +name+ "'," +to_string(roll_no)+ "," + to_string(marks) + ")";
    rc = sqlite3_exec( db , sql.c_str() , callback , 0 , &zErrmsg ) ;
    if( rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrmsg);
        sqlite3_free(zErrmsg);
    }
    else 
    {
          fprintf(stdout, "Records created successfully\n");
    }
}

int showtable()
{
    string sql = "SELECT * FROM 'Student';";
    rc = sqlite3_exec( db , sql.c_str() , callback , 0 , &zErrmsg ) ;
    if( rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrmsg);
        sqlite3_free(zErrmsg);
    }
    else 
    {
          fprintf(stdout, "Records shown successfully\n");
    }
}

int main()
{
    if( rc )
    {
        cout<<"DB error" ;
    }
    else
    {
        cout<<"Database Connected..." ;
    }

    int choice ;
    do
    {
        cout<<"Enter Choice\n1.Create Table\n2.Inserting Tuples\3.Show Contents\n3.Exit\t";
        cin>>choice ;
        switch(choice)
        {
            case 1 : createtable() ;
                     break ;
            case 2 : insert() ;
                     break ;
            case 3 : showtable() ;
                     break ;
            default: cout<<"Enter correct choice!!" ;
        }
    }while(choice != 3) ;
    sqlite3_close(db) ;
    return 0 ;
}