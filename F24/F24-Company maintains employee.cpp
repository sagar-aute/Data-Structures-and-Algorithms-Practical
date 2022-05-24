/*
Company maintains employee information as employee ID, name, designation and salary.  
Allow user to add, delete information of employee. Display information of particular  
employee. If employee does not exist an appropriate message is displayed. If it is, then  
the system displays the employee details. Use index sequential file to maintain the data.
*/
#include <iostream>
#include<fstream>
#include<cstring>
#include<iomanip>
using namespace std;
const int MAX=20;
class Employee
{
 int ID;
 char name[20],designation[20];
 int salary;

public:
 Employee()
{
  strcpy(name,"");
  strcpy(designation,"");
  ID=salary=0;
}
 Employee(int ID,char name[MAX],char designation[MAX],int salary)
 {
  strcpy(this->name,name);
  strcpy(this->designation,designation);
  this->ID=ID;
  this->salary=salary;
 }
 int getID()
 {
  return ID;
 }
 void displayRecord()
 {

  cout<<endl<<setw(5)<<ID<<setw(5)<<name<<setw(5)<<designation<<setw(5)<<salary;
 }
};

class FileOperations
{
 fstream file;
public:
 FileOperations(char* filename)
{
file.open(filename,ios::in|ios::out|ios::ate|ios::binary);
}
 void insertRecord(int ID, char name[MAX],char designation[MAX],int salary)
 {
  Employee s1(ID,name,designation,salary);
  file.seekp(0,ios::end);
  file.write((char *)&s1,sizeof(Employee));
  file.clear();
 }
 void displayAll()
 {
  Employee s1;
  file.seekg(0,ios::beg);
  while(file.read((char *)&s1, sizeof(Employee)))
  {
   s1.displayRecord();
  }
  file.clear();
 }
 void displayRecord(int ID)
 {
  Employee s1;
  file.seekg(0,ios::beg);
  bool flag=false;
  while(file.read((char*)&s1,sizeof(Employee)))
  {
   if(s1.getID()==ID)
   {
    s1.displayRecord();
    flag=true;
    break;
   }
  }
  if(flag==false)
  {
   cout<<"\nRecord of "<<ID<<"is not present.";
  }
  file.clear();
 }
 void deleteRecord(int ID)
 {
  ofstream outFile("new.dat",ios::binary);
  file.seekg(0,ios::beg);
  bool flag=false;
  Employee s1;

  while(file.read((char *)&s1, sizeof(Employee)))
  {
   if(s1.getID()==ID)
   {
    flag=true;
    continue;
   }
   outFile.write((char *)&s1, sizeof(Employee));
  }
  if(!flag)
  {
   cout<<"\nRecord of "<<ID<<" is not present.";
  }
  file.close();
  outFile.close();
  remove("employee.dat");
  rename("new.dat","employee.dat");
  file.open("employee.dat",ios::in|ios::out|ios::ate|ios::binary);
 }
 ~FileOperations()
 {
  file.close();
  cout<<"\nFile Closed.";
 }
};
int main() {
 ofstream newFile("employee.dat",ios::app|ios::binary);
  newFile.close();
  FileOperations file((char*)"employee.dat");
     int ID,salary,choice=0;
     char name[MAX],designation[MAX];
     while(choice!=5)
     {
         cout<<"\n*****Employee Database*****\n";
         cout<<"1. Add New Record\n";
         cout<<"2. Display All Records\n";
         cout<<"3. Display by ID\n";
         cout<<"4. Deleting a Record\n";
         cout<<"5. Exit\n";
         cout<<"Choose your choice: ";
         cin>>choice;
         switch(choice)
         {
             case 1 : //New Record
               cout<<endl<<"Enter ID and name: \n";
               cin>>ID>>name;
               cout<<"Enter designation: \n";
               cin>>designation;
               cout<<"Enter salary: \n";
               cin>>salary;
               file.insertRecord(ID,name,designation,salary);
               cout<<"\nRecord Inserted.";
               break;
             case 2 :
              cout<<endl<<setw(5)<<"ID"<<setw(5)<<"NAME"<<setw(7)<<"DESIGNATION"<<setw(7)<<"SALARY";
               file.displayAll();
               break;
             case 3 :
               cout<<"Enter ID: ";
               cin>>ID;
                file.displayRecord(ID);

               break;
             case 4:
               cout<<"Enter ID:";
               cin>>ID;
               file.deleteRecord(ID);
               break;
            case 5 :break;
         }

     }

 return 0;
}