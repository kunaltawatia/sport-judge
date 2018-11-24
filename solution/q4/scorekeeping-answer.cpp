#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll maxsum(std::vector<ll> v)
{
	ll sum=0,best=0;
	for(ll i =0;i<v.size();i++)
	{
		sum = max(sum+v[i],v[i]);
		best = max(sum,best);
	}
	return best;
}
int main() 
{
    ll n;
    cin>>n;
    std::vector<ll> v1(n),v2(n);
	for (ll k = 0; k < n; k++)
	cin>>v1[k];
	for (ll k = 0; k < n; k++)
	cin>>v2[k];
	cout<<((maxsum(v1)>maxsum(v2))?1:2);
}