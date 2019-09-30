#include"SManagement.h"

int main()
{
    char id[30] ;
    char name[30] ;
    char marks[30] ;
    DB O1 ;
    int choice ;
    do
    {
        cout<<"Enter Choice \n1.Create Table \n2.Show table \n3.Insert Data \n4.Delete an entry \n5.Exit: " ;
        cin>>choice ;
        switch(choice)
        {
        case 1:O1.createtable() ;
                  break;  
        
        case 2:O1.showtable() ;
                  break ;

        case 3:cout<<"Enter id: " ;
               cin>>id ;
               cout<<"Enter name: ";
               cin>>name ;
               cout<<"Enter total marks: " ;
               cin>>marks ;
               O1.insertdata(id , name, marks) ;
               break ;

            
        case 4:char* id2 ;
               cout<<"Enter id:" ;
               cin>>id2 ;
               O1.deleteEntry(id) ;
               break ;

        default:
            break;
        }
    } while (choice!=5);
    
    
}