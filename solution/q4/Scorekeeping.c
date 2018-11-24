#include <stdio.h>
typedef long long int lli;       //using a short name for data type

lli max(lli a,lli b)
{
	if(a>b) return a;
	else return b;
}

int main()
{
	lli n,value,i;
	scanf("%lld",&n);

	lli sum1=0,bestsum1=0;
	for(i=0;i<n;i++)			//taking input for array 1 and checking best subarray sum
	{
		scanf("%lld",&value);
		sum1 = max(sum1+value,value);
		bestsum1 = max(sum1,bestsum1);
	}

	lli sum2=0,bestsum2=0;
	for(i=0;i<n;i++) 			//taking input for array 2 and checking best subarray sum
	{
		scanf("%lld",&value);
		sum2 = max(sum2+value,value);
		bestsum2 = max(sum2,bestsum2);
	}

	if(bestsum1 > bestsum2)
		printf("1");
	else
		printf("2");
	return 0;
}