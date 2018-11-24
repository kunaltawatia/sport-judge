#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[])
{	
	fstream fin("user.txt");
	string handler,ip;
	while(fin>>handler>>ip)
	{
		if(ip==argv[1])
			cout<<handler;
	}
	return 0;
}
