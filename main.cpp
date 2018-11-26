#include<bits/stdc++.h>
#include"dbms.h"
using namespace std;
int main()
{
   ifstream f;
   f.open("input.txt");
   string str;
   while( getline(f, str))
   {
      if(str[0]=='c') create1(str);
      else if(str[0]=='i') insert1(str);
      else if(str[0]=='s') select1(str);
      else if(str[0]=='d') delete1(str);    
   }
   return 0;
}
