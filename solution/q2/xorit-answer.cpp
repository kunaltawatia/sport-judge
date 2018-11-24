#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
	ll n;
	cin>>n;
	cout<<pow(2, __builtin_popcount(n));
}