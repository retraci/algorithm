#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
using namespace std;
#define mod 998244353
typedef long long ll;
const int N=1e7+5;
ll phi[N];
template <class T>
void read(T &x) {
    static char ch;static bool neg;
    for(ch=neg=0;ch<'0' || '9'<ch;neg|=ch=='-',ch=getchar());
    for(x=0;'0'<=ch && ch<='9';(x*=10)+=ch-'0',ch=getchar());
    x=neg?-x:x;
}
int p[N];
int vis[N],prime[N];
int tot=0;
void Calphi()
{
    phi[1]=1;
    for(int i=2;i<N;i++)
    {
        if(!vis[i])
        {
            prime[tot++]=i;
            phi[i]=i-1;
        }
        for(int j=0;j<tot;j++)
        {
            if(i*prime[j]>N)
                break;
            vis[i*prime[j]]=1;
            if(i%prime[j]==0)
            {
                phi[i*prime[j]]=phi[i]*prime[j];
                break;
            }
            else
            {
                phi[i*prime[j]]=phi[i]*(prime[j]-1);
            }

        }
    }
}

ll sangen(__int128 n,__int128 l,__int128 r)
{
    if(n==1)
        return n;
    __int128 mid;
    ll ans;
    while (l<=r)
    {
        mid=(l+r)/2;
        if(mid*mid*mid<=n)
        {
            ans=mid;
            l=mid+1;
        }
        else
        {
            r=mid-1;
        }

    }
    return (ll)ans;
}
ll qpow(ll x,ll y)
{
    ll ans=1;
    while(y)
    {
        if(y&1)
            ans=ans*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return ans;
}
const __int128 maxx=1e8,minn=1;
int main()
{
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif
    int t;
    Calphi();
    //cout<<phi[100]<<endl;
    scanf("%d",&t);
//    int cur = 10000000;
    while(t--){
        __int128 n;
//        read(n);
        n = cur--;
        ll a=sangen(n,minn,maxx);
        ll r=a-1;
        // cout<<a<<" "<<r<<endl;
        ll ans=0;
        __int128 ta=(__int128)a*a*a-1;

        for(ll t=1;t*t<=a;t++)
        {
            if(a%t==0)
            {
                ll tmp1=(((n/t)-ta/t)%mod+mod)%mod;
                ans=(ans+phi[t]*(tmp1)%mod)%mod;
                if(t*t!=a)
                {
                    ll tmp=a/t;
                    ll tmp2=(((n/tmp)-ta/tmp)%mod+mod)%mod;
                    ans=(ans+phi[tmp]*tmp2%mod)%mod;
                }
            }
        }
        ll inv2=qpow(2,mod-2);
        ll inv6=qpow(6,mod-2);
        for(ll t=1;t<=r;t++)
        {
            ll tmp1=(ll)(r/t);
            ll tmp2=3*t%mod*tmp1%mod*(1+tmp1)%mod*(2LL*tmp1%mod+1)%mod*inv6%mod;
            tmp2=(tmp2+3*(1+tmp1)%mod*tmp1%mod*inv2%mod)%mod;
            tmp2=(tmp2+tmp1)%mod*phi[t]%mod;
            ans=(ans+tmp2)%mod;
        }
        printf("%lld\n",ans);
    }
    return 0;
}