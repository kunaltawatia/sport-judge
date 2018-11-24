#include <bits/stdc++.h>
using namespace std;

int main(int argc,char *argv[])
{
        if(argc == 3)
        {
                int len = strlen(argv[1]);
                if(len>20 || len < 5)
                        return 1;
                ofstream fout("user.txt",ios::app);
                fout<<argv[1]<<" "<<argv[2]<<"\n";
		fout.close();
                return 0;
        }
        else return 1;
}
                                                                            
                                        
