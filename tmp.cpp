// #pragma GCC optimize(2)
// #pragma GCC optimize(3)
// #pragma GCC optimize("Ofast")
#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
#include<utility>
#include<cstring>
#include<iomanip>
#include<unordered_set>
#include<unordered_map>
#include<set>
#include<map>
#include<queue>
#include<numeric>
using namespace std;
#define rep(i, x, y) for(int i = (int)x; i < (int)y; ++ i)
#define _rep(i, x, y) for(int i = (int)x; i > (int)y; -- i)
#define PII pair<int,int>
#define eb emplace_back
#define pb push_back
#define fi first
#define se second
#define PQ priority_queue
#define lb lower_bound
#define ub upper_bound
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define SZ(x) (int)(x).size()
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef vector<int> VI;
typedef vector<VI> VII;
typedef vector<ll> VL;
typedef vector<vector<ll>> VLL;
constexpr int mod = 1e9 + 7;
constexpr int KINF = 0x3f3f3f3f;
constexpr int INF = 0x7f7f7f7f;

int fa[100];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int main(){
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false); cin.tie(nullptr), cout.tie(nullptr);
    iota(fa, fa + 10, 0);

    {
        int tx = find(1), ty = find(2);
        fa[tx] = ty;
    }
    {
        int tx = find(1), ty = find(1);
        fa[tx] = ty;
    }
    find(1);


    return 0;
}