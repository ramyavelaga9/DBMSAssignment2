#include<bits/stdc++.h>
#include"dbms.h"
using namespace std;
table* tarray[100];
int index1=0;
int count1=0;
table* T[100]; //global array that stores table pointers
ofstream f("log.txt");
void select1(string str)
{
  string s1,s2,s3;
  str.erase(remove(str.begin(),str.end(),' '),str.end());//removes spaces from given string
  str.erase(0,6);  //remove select keyword
  int i=str.find("from");
  s1=str.substr(0,i); //find attribute list
  str.erase(0,i+4);
  int j=str.find("where");
  if(j==-1){
  	s3="true";  //condition is true if there is no where clause
  	s2=str;
  	}
  else
  {
  	s2=str.substr(0,j);
  	str.erase(0,j+5);
  	s3=str;
  }
  j=s2.find(",");
  string s4;
  if(j==-1)
  {
    s4="sigma("+s3+",dump("+s2+"))";//generate required string if only one table is given
  }
  else
  {
    s4="sigma("+s3+",cross("+s2+"))";//generate required string if two tables are given
  }
  pi1(s1,s4);
}
void pi1(string str1,string str2)
{
   string s1="",s2,str;
   int i;
       str=str2.substr(6,str2.length()-6);
       for(i=0;i<str.length();i++)
       {
         if(str[i]==',')
         {
           break;
         }
         else
         {
           s1+=str[i];
         }
       }
       s2=str.substr(i+1,str.length()-i-2);
       sigma1(s1,s2);
       pi(str1,T[count1]); //calling actual pi function
}
void sigma1(string str1,string str2)
{
    string str="",s1;
    int i;
    if(str2[0]=='c') //if it contains cross
    {
        i=6;
        while(str2[i]!=',')
        {
            str=str+str2[i];   
            i++;
        }
        s1=str2.substr(i+1,str2.length()-i-2);
       
        cross1(str,s1);
    }
    else if(str2[0]=='d')//if it contains dump
    {
        i=5;
        while(str2[i]!=')')
        {
            str=str+str2[i];   
            i++;
        }
        T[count1]=dump(str);
    }
      T[++count1]=sigma(str1,T[count1]);
}
void cross1(string str1,string str2)
{
  T[count1]=dump(str1); //get table pointer for first table
  count1++;
  T[count1]=dump(str2);//get table pointer for second table
  count1++;
  T[count1]=cross(T[count1-1],T[count1-2]);
}
void create1(string str)
{
    str.erase(remove(str.begin(),str.end(),' '),str.end());//remove spaces from string
    string s=str.substr(6,str.length()-6); //removing create keyword
    string s1="";
    int i=0;
    while(s[i]!='(')//getting table name
    {
       s1+=s[i];
       i++;
    }
    string s2=s.substr(i+1,s.length()-i-2);//remaining string containing parameters
    create(s1,s2);
}
void insert1(string str)
{
    str.erase(remove(str.begin(),str.end(),' '),str.end());//remove spaces from string
    string s=str.substr(10,str.length()-10);//removing insert into keyword
    string s1="";
    int i=0;
    while(s[i]!='(') //getting table name
    {
       s1+=s[i];
       i++;
    }
    s1.erase(s1.size()-6);
    table* T=dump(s1);
    string s2=s.substr(i+1,s.length()-i-2);//remaining string containing parameters
    s2.erase(remove(s2.begin(),s2.end(),'\''),s2.end()); //removing single quotes from string
    insert(s2,T);
}
void delete1(string str)
{
  str.erase(remove(str.begin(),str.end(),' '),str.end());//to remove spaces
  str.erase(0,10);//to remove deletefrom keyword
  int i=str.find("where");
  string s1=str.substr(0,i);
  table* T=dump(s1);
  str.erase(0,i+5);
  Delete(str,T);
} 

  
  
table* dump(string str)//this function gets table pointer from table name 
{
   for(int i=0;i<100;i++)
   {
      if(tarray[i]->name==str)
      {
        return tarray[i];
      }
   }
   return NULL;
}
table* cross(table* T1,table* T2)
{
   table* T3=new table;
   int count1=0;
   T3->nattr=(T1->nattr)+(T2->nattr); 
   T3->nrow=(T1->nrow)*(T2->nrow);
   for(int i=0;i<T1->nrow;i++)
   {
     row* r1=T1->rows[i];
     for(int j=0;j<T2->nrow;j++)
     {
       row* r2=T2->rows[j];
       row* r3=new row;
       r3->ncols=r1->ncols+r2->ncols;
       for(int k=0;k<r1->ncols;k++)
       {
         if(T1->attrtype[k]==true)    strcpy(r3->cols[k].str,r1->cols[k].str);
         else r3->cols[k].x=r1->cols[k].x;
       }
       for(int k=r1->ncols;k<r2->ncols;k++)
       {
          if(T2->attrtype[k-(r1->ncols)]==true)    strcpy((r3->cols[k]).str,(r2->cols[k-(r1->ncols)]).str);
          else (r3->cols[k]).x=(r2->cols[k-(r1->ncols)]).x;
       }
       T3->rows[count1]=r3;
       count1++;
     }
   }
       for(int k=0;k<T1->nattr;k++) //appending first attributes
       {
         T3->attr[k]=T1->attr[k];
         T3->attrtype[k]=T1->attrtype[k];
       }
       for(int k=T1->nattr;k<T2->nattr;k++)//appending second attributes
       {
          T3->attr[k]=T2->attr[k-(T1->nattr)];
          T3->attrtype[k]=T2->attrtype[k-(T1->nattr)];
       }
      return T3;
}
int find(string s,table* T) //find attribute position from attr array
{
  for(int i=0;i<T->nattr;i++)
  {
    if(T->attr[i]==s)
    {
      return i;
    }
  }
  return -1;
}
void pi(string str,table* T)
{
  f<<"pi function is called"<<endl;
  int a[T->nattr];
  int j=0;
  string s="";
  for(int i=0;i<=str.length();i++)
  {
     if(str[i]==',' || i==str.length())// getting position of attributes seperated by commas
     {
       a[j]=find(s,T);
       j++;
       s="";
     }
     else
     {
       s+=str[i];
     }
  }
  cout<<"------------------"<<endl;
  for(int i=0;i<j;i++)
  {
    cout<<T->attr[a[i]]<<" ";
  }
  cout<<endl;
  cout<<"------------------"<<endl;
  for(int i=0;i<T->nrow;i++)
  {
    row* r=T->rows[i];
    for(int k=0;k<j;k++)
    {
      int m=a[k];
      if(T->attrtype[m]==true) 
      {
         string z(r->cols[m].str);
         cout<<z<<" ";
      }
      else  cout<<r->cols[m].x<<" ";
    }
    cout<<endl;
   }
   cout<<"------------------"<<endl;
}
void create(string str1,string str2)
{
        f<<"table "<<str1<<" is created"<<endl;
   	table* T=new table;//creating new table
   	T->nattr=0;
   	T->nrow=0;
   	T->name=str1;
   	string s1="";
   	string s2="";
   	int b=0;
   	for(int i=0;i<str2.length();i++)
   	{
   		if(str2[i]==',' || i==str2.length()-1)
   		{
   		  T->attr[T->nattr]=s1;
   		  if(s2=="PK") //if it is primary attribute
   		  {
   		     T->PK[T->nattr]=true;
   		     T->attrtype[T->nattr]=true;
   		  }
   		  else if(s2=="int") T->attrtype[T->nattr]=false; 
   		  else T->attrtype[T->nattr]=true;
                   //foreign key implementation need to be done
                   (T->nattr)++;
                   s1="";
                   s2="";
   		}
   		
   		else if(str2[i]=='(')
   		{
   		  b=1;
   		}
   		else if(str2[i]==')')
   		{
   		  b=0;
   		}  		
   		else
   		{
   		    if(b==0)
   		    s1=s1+str2[i]; //getting attribute name
   		    else
   		    s2=s2+str2[i]; //getting parameter given to attribute
   		}
   	}
   	
   	tarray[index1]=T;
   	index1++;
   	cout<<"Table  "<<str1<<"  created"<<endl;
}
void insert(string str,table* T)
{
  f<<"A row is inserted"<<endl;
  row* r=new row;
  T->rows[T->nrow]=r;
  r->ncols=T->nattr;
  T->nrow++;
  int c=0;
  string s="";
  for(int i=0;i<str.length();i++)
  {
    if(str[i]==',' || i==str.length()-1)
    {
      if(T->PK[c]==true)
      {
         if(s=="NULL") 
         {
           cout<<"Entity Integrity constraint is violated"<<endl;
           T->nrow--;
           return;
         }
         else 
         {
            for(int j=0;j<T->nrow-1;j++)
            {
              row* R=T->rows[j];
              if(strcmp(R->cols[c].str,s.c_str())==0)
              {
                cout<<"Key constraint is violated"<<endl;
           	T->nrow--;
           	return;
              }
            }
            strcpy((r->cols[c]).str,s.c_str());
          }
       }    
      else if(T->attrtype[c]==false)  (r->cols[c]).x=atoi(s.c_str());   
      else strcpy((r->cols[c]).str,s.c_str());
      c++;
      s="";
    }
    else
    {
      s+=str[i];
    }
   }
   cout<<"1 Row inserted"<<endl;
}
void satisfy(table* T,string str,int r[100],int &idx)
{
        int o[7],i,j;
	string s[7],s2;
	int y;
	
	o[0]=str.find("!=");
	s[0]="!=";
	o[1]=str.find("<>");
	s[1]="<>";
	o[2]=str.find(">=");
	s[2]=">=";
	o[3]=str.find("<=");
	s[3]="<=";
	o[4]=str.find("=");
	s[4]="=";
	o[5]=str.find(">");
	s[5]=">";
	o[6]=str.find("<");
	s[6]="<";
	
	for(i=0;i<=6;i++)
	{
		if(o[i]!=-1)
		break;
	}
	s2=str.substr(o[i]+s[i].length(),str.length()-(o[i]+s[i].length()));
	string attname=str.substr(0,o[i]);
	j=find(attname,T);
	bool flag;
	if(T->attrtype[j]==true)
	{
	   flag=true;
	   s2.erase(remove(s2.begin(),s2.end(),'\''),s2.end());
	}
	else
	{
	   flag=false;
	   y=atoi(s2.c_str());
	}
	for(int k=0;k<T->nrow;k++)
	{
	  row* R=T->rows[k];
	  if(!flag)
	  {
	     int z=R->cols[j].x;
	     switch(i)
	     {
	       case 0: if(z!=y) {
	                    r[idx]=k;
	                    idx++;
	                    }
	                break;
	       case 1: if(z!=y) {
	                    r[idx]=k;
	                    idx++;
	                    }
	                break;
	       case 2: if(z>=y) {
	                    r[idx]=k;
	                    idx++;
	                    }
	                break;
	       case 3: if(z<=y) {
	                    r[idx]=k;
	                    idx++;
	                    }
	                break;
	      case 4: if(z==y) {
	                    r[idx]=k;
	                    idx++;
	                    }
	                break;
	     case 5: if(z>y) {
	                    r[idx]=k;
	                    idx++;
	                    }
	                break;
	    case 6: if(z<y) {
	                    r[idx]=k;
	                    idx++;
	                    }
	                break; 
	      default:break;
	    } 
	   }
	   else
	   {
	     char s[100];
	     strcpy(s,R->cols[j].str);
	     string z(s);
	     switch(i)
	     {
	       case 0: if(z!=s2) {
	                    r[idx]=k;
	                    idx++;
	                    }
	                break;
	       case 1: if(z!=s2) {
	                    r[idx]=k;
	                    idx++;
	                    }
	                break;
	       case 2: if(z>=s2) {
	                    r[idx]=k;
	                    idx++;
	                    }
	                break;
	       case 3: if(z<=s2) {
	                    r[idx]=k;
	                    idx++;
	                    }
	                break;
	      case 4: if(z==s2) {
	                    r[idx]=k;
	                    idx++;
	                    }
	                break;
	     case 5: if(z>s2) {
	                    r[idx]=k;
	                    idx++;
	                    }
	                break;
	    case 6: if(z<s2) {
	                    r[idx]=k;
	                    idx++;
	                    }
	                break; 
	      default:break;
	           
	   }
	  }
	 }
   }             
void Delete( string str,table* T)
{
  int r[100];
  int idx=0;
  satisfy(T,str,r,idx);
   f<<idx<<"rows are deleted"<<endl;
  cout<<idx<<" Rows deleted"<<endl; 
  for(int i=0;i<idx;i++)
  {
    r[i]=r[i]-i;
  }
  for(int i=0;i<idx;i++)
  {
    for(int j=0;j<T->nrow;j++)
    {
      if(j>=r[i])
      {
        T->rows[j]=T->rows[j+1];
      }
    }
    T->nrow--;
   } 
}
      
table* sigma(string str,table* T)
{
  f<<"sigma function is called"<<endl; 
  if(str=="true") return T;
  else
  {
     table* T1=new table;
     T1->nattr=T->nattr;
     int idx=0;
     int r[100];
     satisfy(T,str,r,idx);
     T1->nrow=idx;
     for(int i=0;i<T->nattr;i++)
     {
        T1->attr[i]=T->attr[i];
        T1->attrtype[i]=T->attrtype[i];
     }
     for(int i=0;i<idx;i++)
     {
       T1->rows[i]=T->rows[r[i]];
     }
     return T1;
   }
}
