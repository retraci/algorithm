// Problem: 都市的柏油路太硬
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/11178/D
// Memory Limit: 1048576 MB
// Time Limit: 6000 ms
//
// Powered by CP Editor (https://cpeditor.org)

//#pragma GCC target("avx")
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
//#pragma GCC optimize("Ofast")
// created by myq
#include<iostream>
#include<cstdlib>
#include<string>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<climits>
#include<cmath>
#include<cctype>
#include<stack>
#include<queue>
#include<list>
#include<vector>
#include<set>
#include<map>
#include<sstream>
#include<unordered_map>
#include<unordered_set>
using namespace std;
typedef long long ll;
#define x first
#define y second
typedef pair<int,int> pii;
const int mod=998244353;
typedef unsigned long long ull;
inline ull myRand(ull &k1, ull &k2){
    ull k3 = k1, k4 = k2;
    k1 = k4;
    k3 ^= (k3 <<23);
    k2 = k3 ^ k4 ^ (k3 >>17) ^ (k4 >>26);
    return k2 + k4;
}
inline pair<int,int>myRanq(ull&k1,ull&k2,int MAXN){
    int x=myRand(k1,k2)%MAXN+1,y=myRand(k1,k2)%MAXN+1;
    if(x>y)return make_pair(y,x);
    else return make_pair(x,y);
}

const int N=300010;
int p[N];
vector<int>v[N];
int dep[N];
int id[N];
int idx;
int in[N];
int out[N];
int Lg[N];
int val[N];
int st[N][20];
int cnt;
int find(int x)
{
    if(p[x]!=x)	p[x]=find(p[x]);
    return p[x];
}
struct edge{
    int a;
    int b;
    int c;
    bool operator<(const edge&w)const
    {
        return c<w.c;
    }
}e[500010];
int cmp(int a,int b){
    if(dep[a]<dep[b])	return a;
    else				return b;
}
void init_st(){
    for(int i=1;i<=cnt;i++)	Lg[i]=(int)log2(i);
    for(int i=1;i<=cnt;i++)	st[i][0]=id[i];
    for(int i=1;i<=19;i++)
    {
        for(int j=1;j+(1<<i)-1<=cnt;j++){
            st[j][i]=cmp(st[j][i-1],st[j+(1<<i-1)][i-1]);
        }
    }
}
void dfs(int u,int fa){
    id[++cnt]=u;
    in[u]=cnt;
    dep[u]=dep[fa]+1;
    for(auto j:v[u]){
        dfs(j,u);
        id[++cnt]=u;
    }
}
int get_lca(int l,int r){
    if(in[r]<in[l])
        swap(l,r);

    cout << l << " " << r << " " << in[l] << " " << in[r] << "\n";

    // cout<<l<<" "<<r<<endl;
    int len=Lg[in[r]-in[l]+1];
    // cout<<len<<endl;
    return cmp(st[in[l]][len],st[in[r]-(1<<len)+1][len]);
}
int main()
{
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=2*n-1;i++)	p[i]=i;
    int idx=n+1;
    for(int i=0;i<m;i++){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        e[i]={a,b,c};
    }
    sort(e,e+m);
    for(int i=0;i<m;i++)
    {
        int a=e[i].a,b=e[i].b;
        int c=e[i].c;
        a=find(a);
        b=find(b);
        if(a!=b)
        {
            v[idx].push_back(a);
            v[idx].push_back(b);
            val[idx]=c;
            p[a]=idx;
            p[b]=idx;
            idx++;

            cout << idx - 1 << " " << a << " " << b << "\n";
        }
    }
    int root=2*n-1;

    dfs(root,0);
    init_st();
    int q;
    scanf("%d",&q);
    ull a,b;
    scanf("%llu%llu",&a,&b);
    int x;
    int y;
    pii P;
    int dd;
    int ans=0;
    while(q--)
    {
        P=myRanq(a,b,n);
        x=P.x;
        y=P.y;



        dd=get_lca(x,y);
//         cout<<x<<" "<<y<<" "<<dd<<endl;
        ans^=val[dd];
    }
    cout<<ans<<endl;
    return 0;

}