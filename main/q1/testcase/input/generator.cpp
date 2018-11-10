#include <bits/stdc++.h>
using namespace std;

int main()
{
	fstream fout("input00.txt");
	int n=50;
	fout<<n<<endl;
	for(int i=0;i<n;i++){
	for(int j=0;j<n;j++)	
	fout<<rand()%2<<" ";
	fout<<endl;
	}
	fout.close();
}


