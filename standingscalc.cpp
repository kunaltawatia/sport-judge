#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct submission
{
	ll owner, testcase, codenumber;
};
struct Row
{
  ll sum=0,rank=0;
  std::vector<ll> values{0,0,0,0};
  ll name;
};
ll Compare_Rows(Row a, Row b)
{
  return (a.sum > b.sum);
}
ll iptonum(string s)
{
	ll len = s.size();
	ll num = 0,i=0;
	for(;i<len;i++)
	{
		if(s[i] == '.')
			continue;
		else
			num = ((num*10) + s[i] - 48) ;
	}
	return num;
}
string checkip(ll ip)
{
	ifstream fin("user.txt");
	string name,ipofname;
	while(fin>>name>>ipofname)
	{
		if(iptonum(ipofname)==ip)
		{
			return name;
		}
		
	}
}
ll score(ll quesno,ll testcase)
{
	switch(quesno)
	{
		case 1 : if(testcase == 4) return 150;
				else return 30;
		case 2: if(testcase == 6) return 50;
				else return 0;
		case 3: if(testcase == 2) return 200;
				else return 40;
		case 4: if(testcase == 6) return 100;
				else return 20;
	}
}
int main()
{
	ll quescount =4,i=0;
	submission s;
	string str;
	ll quesno,count=0;
	ll info[1000][4]={};
	set<ll> participants;
	ifstream cin("scorelog.txt");
	ofstream cout("standings.txt");
	while(cin >> s.testcase >> quesno >> str)
	{
		s.owner = iptonum(str);
		ll scr = score (quesno,s.testcase);
		info[count][0]=scr;
		info[count][1]=s.owner;
		info[count][2]=quesno;
		info[count][3]=s.codenumber;
		participants.insert(s.owner);
		count++;
	}
	ll totpart = participants.size();
	Row data[totpart];
	set<ll>::iterator it = participants.begin();
	for(i=0;i<totpart;i++,it++)
	{
		data[i].name = *it;
	}
	for(i=0;i<count;i++)
	{
	    ll j=0;
	    for( j=0 ;j<totpart;j++)
	    {
	        if(data[j].name == info[i][1] )
	        break;
	    }
	    ll qno=info[i][2];
	    data[j].values[qno-1] = max(data[j].values[qno-1],info[i][0]); 
	}
	for(i=0;i<totpart;i++,it++)
		for(ll j=0;j<quescount ;j++)
			    data[i].sum += data[i].values[j];

	sort(data, data + totpart, Compare_Rows);
	count=0;
	cout<<setw(2)<<"Rank\t"<<setw(20)<<"Username\t"<<setw(3)<<"A\t"<<setw(3)<<"B\t"<<setw(3)<<"C\t"<<setw(3)<<"D\t"<<setw(5)<<"Total\n\n";
	for (i = 0; i < totpart; i++, it++)
    	{      	
		count++;
		if(i==0)
		{
			data[i].rank=1;
			cout<<data[i].rank<<"\t";
		}
		else
		{
			if(data[i].sum==data[i-1].sum)
				data[i].rank=data[i-1].rank;
			else data[i].rank = count;
			cout<<setw(3)<<data[i].rank<<"\t";
		}
		cout << left<<setw (20) << checkip(data[i].name)<< "\t";
		for (ll j = 0; j < quescount; j++)	
		{  
			cout << setw (3) << data[i].values[j] << "\t";	
		}	    
		cout <<setw(3)<<data[i].sum << "\n";
    	}
	return 0;
}
