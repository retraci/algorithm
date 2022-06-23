#include <cstdio>
#include <cstring>
#include <vector>
#pragma GCC optimize(3)


const int N=11;
const int mod=9973;

using namespace std;

int m;
using ll = long long;

struct Matrix
{
    ll w[N][N];
//    vector<vector<ll>> w;

    Matrix() {
//        w = vector<vector<ll>>(11, vector<ll>(11));
    }

    Matrix operator*(const Matrix& t)const
    {
        Matrix c;
        for(int i=1;i<=m;i++)
            for(int j=1;j<=m;j++)
            {
                c.w[i][j]=0;
                for(int k=1;k<=m;k++)
                    (c.w[i][j]+=w[i][k]*t.w[k][j] % mod)%=mod;
            }
        return c;
    }

    int operator^(int k)
    {
        Matrix a = *this;
        Matrix f;
        for(int i=1;i<=m;i++)
            for(int j=1;j<=m;j++)
                f.w[i][j]=i==j;
        while(k)
        {
            if(k&1)f=f*a;
            a=a*a;
            k>>=1;
        }
        int res=0;
        for(int i=1;i<=m;i++)(res+=f.w[i][i])%=mod;
        return res;
    }
};

int ksm(Matrix a,int k)
{
    Matrix f;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=m;j++)
            f.w[i][j]=i==j;
    while(k)
    {
        if(k&1)f=f*a;
        a=a*a;
        k>>=1;
    }
    int res=0;
    for(int i=1;i<=m;i++)(res+=f.w[i][i])%=mod;
    return res;
}

ll ksm(ll a, ll b) {
    a %= mod;
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

ll inv(ll x) {
    return ksm(x, mod - 2);
}

// region 欧拉函数
ll eula(ll x) {
    ll res = x;

    for (ll i = 2; i <= x / i; i++) {
        if (x % i == 0) {
            res = res / i * (i - 1);
            while (x % i == 0) x /= i;
        }
    }
    if (x > 1) res = res / x * (x - 1);

    return res;
}
// endregion

int main()
{
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif
    int task,n,k;
    Matrix g;
    for(scanf("%d",&task);task--;)
    {
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=m;i++)
            for(int j=1;j<=m;j++)
                g.w[i][j]=1;
        while(k--)
        {
            int a,b;
            scanf("%d%d",&a,&b);
            g.w[a][b]=g.w[b][a]=0;
        }
        int res=0;
        for(int d=1;d*d<=n;d++)
            if(n%d==0)
            {
                res=(res+(g^d)*eula(n/d))%mod;
                if(d!=n/d)res=(res+(g^(n/d))*eula(d))%mod;
            }
        printf("%d\n",res*inv(n)%mod);
    }
    return 0;
}
