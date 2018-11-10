#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n;
vector<vector<ll> > obstacles;
vector<ll> result;

void solve (ll sz)
{
	if(sz<2) return;
	ll mn= 2147483647,height=n-sz+1,length=n-sz+1,i,j,index;
	vector<vector<ll> > arr(n,vector<ll>(n,0));
	for(i=0;i<n;i++)
	{
		ll k=obstacles[i].size()-1,count=0,qsz =0;
		queue<ll> q;
		for(index=n-1;index>=0 ;--index)
		{
			if(qsz>0 && index == q.front())
			{
				q.pop();
				qsz--;
				count--;
			}
			if(k>=0 && obstacles[i][k]==index)
			{
				count++;
				k--;
				q.push(index-sz);
				qsz++;
			}
			arr[i][index]=count;
		}
	}
	for(i=0;i<length;i++)
	{
		ll sum=0;
		for(j=n-1;j>=height-1;--j)
			sum += arr[j][i];
		mn=min(sum,mn);
		for(;j>=0;--j)
		{
			sum += arr[j][i]-arr[j+sz][i];
			mn=min(sum,mn);
		}
	}
	result[sz]=mn;
	if(mn==0) return;
	else solve(sz-1);
}
int main()
{
	ll q,i,j;
	cin>>n;
	ll arr[n][n];
	obstacles.resize(n);
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			cin>>arr[i][j];
			if(arr[i][j])
			    obstacles[i].push_back(j);
		}
	}
    result.resize(n+1);
	solve (n);
	for (i=0;i<result.size();i++)
    	if(result[i])
    	{
    		cout<<i-1;
    		break;
    	}
	return 0;
}
