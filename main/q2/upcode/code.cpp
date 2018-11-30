#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll popcount(ll n)
{
	ll ans=0;
	while(n)
	{
		ans+=n%2;
		n /=2;
	}
	return ans;
}
int main()
{
	ll n;
	cin>>n;
	cout<<pow(2,popcount(n));
}
