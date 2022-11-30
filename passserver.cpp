//Gabriel Mannhimer

#include "hashtable.h"
#include "passserver.h"

using namespace std;
using namespace cop4530;

//constructor
PassServer::PassServer(size_t s)
{ t.resize(s); }

//destrcutor
PassServer::~PassServer()
{ t.clear(); }

//addUser
bool PassServer::addUser(std::pair<string,string> & kv)
{
 std::pair<string,string> np;
 np.first = kv.first;
 np.second = encrypt(kv.second);
 t.insert(np); 
}

//addUser, move
bool PassServer::addUser(std::pair<string,string> && kv)
{
 auto temp = kv;
 temp.first = kv.first;
 temp.second = kv.second;
 addUser(temp);
}

//removeUser
bool PassServer::removeUser(const string &k)
{ t.remove(k); }

//dump
void PassServer::dump()
{ t.dump(); }

//encrypt
string PassServer::encrypt(const string & str)
{
  char salt[] = "$1$########";
  string cstr = crypt(str.c_str(), salt);
  return cstr;
}


//size
size_t PassServer::size()
{ return t.size(); }

//find
bool PassServer::find(const string & user)
{ t.contains(user); }


//changePasswrod
bool PassServer::changePassword(const std::pair<string,string> &p, const string & newpassword)
{
 if(p.second == newpassword)
 {
  cout << "Can't use the same password!" << endl;
  return false;
 }

 std::pair<string,string> tp;
 tp.first = p.first;
 tp.second = encrypt(p.second);

 if(t.match(tp))
 {
   std::pair<string,string> np(p.first,encrypt(newpassword));
   t.insert(np);
   return true;
 }
 
 else
  cout << "Looks like your password didnt match" << endl;

 return false;
}

//load
bool PassServer::load(const char *filename)
{
  t.load(filename);
}

//wtire_to_file
bool PassServer::write_to_file(const char *filename)
{
 t.write_to_file(filename);
}

string PassServer::my_getpass()
{
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Hides

    std::string s;
    cin >> s;

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // return to display
    return s;
}
