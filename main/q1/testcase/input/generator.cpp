#include <bits/stdc++.h>
using namespace std;

int main()
{
	fstream fout("input4.txt");
	int n=1000;
	fout<<n<<endl;
	for(int i=0;i<n;i++){
	for(int j=0;j<n;j++)	
	fout<<"0";
	fout<<endl;
	}
	fout.close();
}


