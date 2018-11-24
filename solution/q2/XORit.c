#include <stdio.h>
typedef long long int lli;       //using a short name for data type

lli pow(lli num,lli p)			 
{
	if(p==0)
		return 1;
	return num*pow(num,p-1);
}
int main()
{
	lli n,ans,count=0;
	scanf("%lld",&n);
	while(n)					//counting number of 1's in binary representation
	{
		if(n%2)
		count++;
		n/=2;
	}
	ans = pow(2,count);
	printf("%lld",ans);
}