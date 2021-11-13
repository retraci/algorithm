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
#include<tuple>
#include<numeric>
#include <chrono>
#include <random>
#include <type_traits>

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

template<typename T>
inline void rd(T &x) {
    T ret = 0, sgn = 1;
    char c = getchar();
    while (!isdigit(c)) sgn = (c == '-' ? -1 : 1), c = getchar();
    while (isdigit(c)) ret = (ret << 3) + (ret << 1) + c - '0', c = getchar();
    x = (sgn == -1 ? -ret : ret);
}

std::mt19937 engine(std::chrono::steady_clock::now().time_since_epoch().count());

template<class T, class = std::enable_if_t<std::is_integral_v<T>>>
// 要求 T 必须为整型
T rand(T l, T r) {
    return std::uniform_int_distribution(l, r)(engine);
}

const int N = 101;

ll n;
vector<int> g[N];
ll a[N];
ll Max = (1ll << 60) - 1;
VI vis;
int jup;

bool check(ll x) {
    for (int &i: vis) {
        if (i == jup) continue;
        if ((a[i] | x) == Max) return false;
    }
    return true;
}

void dfs(int u) {
//    cout << u << "\n";
    for (int &i: g[u]) {
        if (a[i] == -1) {
            jup = u;
            while (1) {
                a[i] = rand(a[u] ^ Max, Max);
                if ((a[i] | a[u]) != Max) continue;
                if (check(a[i])) break;
            }
            vis.eb(i);
            if (vis.size() == n) return;
            dfs(i);
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    rd(n);
    rep(i, 0, n + 1) a[i] = -1;
    rep(i, 0, n - 1) {
        int u, v;
        rd(u);
        rd(v);
        g[u].eb(v);
        g[v].eb(u);
    }
    a[1] = rand(0ll, Max);
    vis.push_back(1);
    dfs(1);
    rep(i, 1, n) printf("%lld ", a[i]);
    printf("%lld", a[n]);
    return 0;
}
// 小心左移运算符导致的int溢出
// dp记得处理非法状态
// resize并不会初始化数组
// 全局函数一定要记得inline
// 带空格字符串不能直接cin,要用getline
// 最好用"\n"代替endl

