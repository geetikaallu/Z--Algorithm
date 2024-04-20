#include<iostream>
#include<fstream>
using namespace std;

void getZarr(string str, int Z[]);

void search(string text, string pattern)
{
 string concat = pattern + "$" + text;
 int l = concat.length();

 int Z[l];
 getZarr(concat, Z);
int count=0;
 for (int i = 0; i < l; ++i)
 {
    if (Z[i] == pattern.length()){
     cout << "Pattern found at index "<< i - pattern.length() -1 << endl;
     count=1;
    }
   }
   if(count==0){
   	cout<<"Pattern not found"<<endl;
   }
}

void getZarr(string str, int Z[])
{
 int n = str.length();
 int L, R, k;

 L = R = 0;
 for (int i = 1; i < n; ++i)
 {
    if (i > R)
    {
       L = R = i;
        while (R<n && str[R-L] == str[R]){
          R++;
         }
       Z[i] = R-L;
       R--;
    }
    else
    {
       k = i-L;
       if (Z[k] < R-i+1){
          Z[i] = Z[k];
        }  
       else {
          L = i;
          while (R<n && str[R-L] == str[R]){
             R++;
          }
          Z[i] = R-L;
          R--;
       }
    }
  }
}

int main()
{	int i;
	    ifstream inputFile("Input-CPP.txt");
	    if (!inputFile) {
	        cerr << "Error: Unable to open input file." << endl;
	        return 1;
	    }
	
		string text,pattern;
		for(i=1;i<=4;i++){
			cout<<"Input "<<i<<":"<<endl;
			if (getline(inputFile, text) && getline(inputFile, pattern)) {
			        search(text, pattern);
			    } 
			else {
			        cerr << "Error: Failed to read input from file." << endl;
			        break;
			    }
	}
	inputFile.close();
	return 0;
}
