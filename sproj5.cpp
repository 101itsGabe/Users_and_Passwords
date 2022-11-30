#include <iostream>
#include <string>
#include "hashtable.h"
#include "passserver.h"

//Gabriel Mannheimer

using namespace std;
using namespace cop4530;

void Menu()
{
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "Enter Choice: ";
}

int main()
{
 size_t size;
 cout << "Enter the size of the HashTable: ";
 cin >> size;
 cout << "\n";
 char choice;
 string name, pass;
 PassServer p(size);


 while(choice != 'x')
 {
  cout << "\n\n";
  Menu();
  cin >> choice;
  choice = tolower(choice);
  cout << "\n";

  switch(choice)
  {
    case 'a':
    {
      cout << "Enter a name: ";
      cin >> name;
      cout << "\n";
      cout << "Enter a password: ";
      pass = p.my_getpass();
      cout << "\n";
      std::pair<string,string> huh(name,pass);
      p.addUser(huh);
      break;
    }
 
    case 'd':
    {
     p.dump();
     break;
    }
    
    case 'r':
     cout << "Enter a name: ";
     cin >> name;
     cout << "\n";
     if(p.removeUser(name))
      cout << "Success!\n";
     else
      cout << "Fail" << endl;
     break;

   case 's':
    cout << "Size of the table: " << p.size() << endl;
    break;
 
   case 'f':
    cout << "Enter a name to find: ";
    cin >> name;
    cout << "\n";
    if(p.find(name))
     cout << name << " found!" << endl;
    else
     cout << "Looks like " << name << " doent exist" << endl;
    break;

  case 'c':
  {
   string np;
   cout << "Enter the name: ";
   cin >> name;
   cout << "\n";
   cout << "Enter the password: ";
   pass = p.my_getpass();
   cout << "\n";
   cout << "Enter the new password: ";
   np = p.my_getpass();
   cout << "\n";
    
   std::pair<string,string> huh(name,pass);
   if(p.changePassword(huh,np))
    cout << "Success!" << endl;
   else
    cout << "Fail!" << endl;
   break;   
  }

  case 'l':
  {
   string filename;
   cout << "Enter the name of the file you want to open: ";
   cin >> filename;
   const char * c = filename.c_str();
   p.load(c);
   break;
  }

  case 'w':
  {
   string filename;
   cout << "Enter the name of the file you want to write out to: ";
   cin >> filename;
   cout << "\n";
   const char * c = filename.c_str();
   p.write_to_file(c);
   break;
  } 
  
  case 'x':
   break;

  default:
   cout << "Not a valid option. Please try again" << endl;
       
  }


 }

 return 0;
}
