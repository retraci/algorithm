#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[12]={-2,0,1,2,3,4,5,6,7,8,9,-2};
int dx[8]={1,1,1,0,-1,-1,-1,0};
int dy[8]={-1,0,1,1,1,0,-1,-1};
int res;
bool judge()
{
    for(int i=1;i<=10;i++)
    {
        int y=i/4;
        int x=i%4;
        for(int k=0;k<8;k++)
        {
            int ny=y+dy[k];
            int nx=x+dx[k];
            int j=ny*4+nx;
            if(0<=ny&&ny<3&&0<=nx&&nx<4)
            {
                if(abs(a[j]-a[i])==1)
                    return false;
            }
        }
    }
    return true;
}
int main()
{
    do{
        if(judge())
            res++;
    }while(next_permutation(a+1,a+11));

    printf("%d\n",res);

    return 0;
}
/*
res:1580
*/