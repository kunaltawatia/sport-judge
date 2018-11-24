#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(int argc,char * argv[])
{
	ifstream ans(argv[1]),out(argv[2]);
	ll n1,n2;
	while((ans>>n1))
	{
		out>>n2;
		if(n1 != n2)
		{
			cout<<1;
			return 0;
		}
	}
	cout<<0;
	return 0;
}