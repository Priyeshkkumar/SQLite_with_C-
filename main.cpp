#include"SManagement.h"

int main()
{
    DB O1 ;
    int choice ;
    cout<<"\nEnter choice \n1.Create Table \n2.Insert data \n3.Show Data \n4.Delete Entry \n5.Exit :" ;
    cin>>choice ;
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

        case 3:char* id ;
               char* name ;
               char* marks ;
               cout<<"Enter id: " ;
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