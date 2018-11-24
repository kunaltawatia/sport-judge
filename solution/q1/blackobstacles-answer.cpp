#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n,ans;
vector<vector<ll>> obstacles;

void solve (ll a,ll b)
{
	if(b-a == 1) 
	{
		ans=a;
		return;
	}
	ll sz= (a+b)/2;
	ll mn= 2147483647,height=n-sz+1,length=n-sz+1,i,j,index;
	vector<vector<ll>> arr(n,vector<ll>(n,0));
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
	if(mn==0)
		a=sz;
	else 
		b=sz;
	solve(a,b);
}
int main()
{

	ll q,i,j,cnt=0;
	cin>>n;
	ll arr[n][n];
	obstacles.resize(n);
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			cin>>arr[i][j];
			if(arr[i][j])
			{
				obstacles[i].push_back(j);
				cnt++;
			}
		}
	}
	if(cnt)
	solve (0,n);
	else ans=n;
        cout<<ans<<endl;
	return 0;
}
