#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
vector <ll> a,b,p;
ll n,m,ans,rnk,suma=0;
ld p1,p2;
void binarystitch()
{
	if(p2<=p1+1) 
	{
	    ans =  p2;
	    return;
	}
	ll phf = (p1+p2)/2,sum=0,count=0;
	for(ll i=0;i<n;i++)
	{
		ll rem = phf%b[i];
		if(p[i]<phf)
			sum += a[i];
		else if (p[i]==phf)
		{
			count++;
			sum += a[i]-1;
		}
		else
		{
			if(rem == 0)
			{
				count++;
				sum += phf/b[i] - 1 ;
			}
			else
				sum += (phf-rem)/b[i];
		}
	}	
	if(rnk>sum + count)
		p1 = (ld) phf + 0.25;
	else if(rnk <= sum)
		p2 = (ld) phf - 0.75;
	else 
		p2 = (ld) phf +0.25;
	binarystitch();
}
int main()
{
	ll i,mx=0;
	cin>>n;
	a.resize(n);
	b.resize(n);
	p.resize(n);
	for(i=0;i<n;i++)
		{
			cin>>a[i]>>b[i];
			suma+=a[i];
			p[i]=a[i]*b[i];
			mx=max(mx,p[i]);
		}
	cin>>rnk;
	p1=0.25;
	p2= (ld) mx + 0.25;
	if(rnk<=0) cout<<0;
	else
	{
		binarystitch();
		cout<<ans;
	}
	return 0;
}