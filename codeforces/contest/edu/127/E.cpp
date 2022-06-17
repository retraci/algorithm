#include <bits/stdc++.h>

void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}

using namespace std;

#define fi first
#define se second
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1 << 18;
const int MOD = 998244353;

int n;
string s;
int f[N];

string dfs(int u) {
    f[u] = 1;
    if (u * 2 + 1 > n) return string(1, s[u]);

    string ret1 = dfs(u * 2);
    string ret2 = dfs(u * 2 + 1);

    f[u] = 1LL * f[u * 2] * f[u * 2 + 1] % MOD;
    if (ret1 != ret2) f[u] = 1LL * 2 * f[u] % MOD;
    if (ret1 > ret2) swap(ret1, ret2);

    return string(1, s[u]) + ret1 + ret2;
}

void solve() {
    n = (1 << n) - 1;
    dfs(1);
    cout << f[1] << "\n";
}

void prework() {
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    prework();
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
//    cin >> _;
    while (_--) {
        cin >> n;
        cin >> s;
        s = ' ' + s;
        solve();
    }

    return 0;

}