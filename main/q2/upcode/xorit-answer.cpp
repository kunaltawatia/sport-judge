#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll popcount(ll n)
{
	ll count=0;
	while(n)
	{
		if(n%2)
		count++;
		n /= 2;
	}
	return count;
}
int main()
{
	ll n;
	cin>>n;
	ll i= popcount(n);
	ll ans = 1 << i;
	cout<<ans<<endl;
}