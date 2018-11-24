#include <bits/stdc++.h>
using namespace std;

int main()
{
	fstream fout("input0.txt");
	int n=10000;
	for(int j=0;j<n;j++){	
	fout<<rand()%10000<<" "<<rand()%10000<<endl;
	}
	fout.close();
}


