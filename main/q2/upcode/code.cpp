#include "bit.h"
using namespace std;
typedef long long ll;

int main()
{
	ll i,j,n=10;
	for(i=0;i<n;i++)
		for(j=0;j<i;j++)
				cout<<i<<" "<<j<<" "<<(i^j)<<endl;
	return 0;
}
