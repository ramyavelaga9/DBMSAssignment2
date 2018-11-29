#include<bits/stdc++.h>
using namespace std;
#define MAX_COLS 100
#define MAX_ROWS 100
#define MAX_ATTR 100

typedef union cell_t{
	char str[100];
	int x;
   }cell;
   
typedef struct row_t{
	cell cols[MAX_COLS];
	int ncols;
   }row;
   
typedef struct table_t{
	string name;
	row* rows[MAX_ROWS];
	int nrow;
	string attr[MAX_ATTR];
	bool attrtype[MAX_ATTR];
	int nattr;
	bool PK[MAX_ATTR];
   }table;
void select1(string);
void pi1(string str1,string str2);
void sigma1(string str1,string str2);
void cross1(string str1,string str2);
void create1(string str);
void insert1(string str);
void delete1(string str);
table* dump(string str);
void create(string,string);
void pi(string str,table* );
void insert(string,table* );
void Delete( string,table*);
table* sigma(string str,table*);
table* cross(table*,table*);
