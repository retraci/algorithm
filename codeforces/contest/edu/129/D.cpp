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
mt19937 mrnd(std::random_device{}());

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int n;
ll x;
map<ll, int> memo;

int dfs(ll u, ll lim) {
    if (u >= lim) return 0;
    if (memo.count(u)) return memo[u];

    int res = 1e9;
    string s = to_string(u);
    for (char ch : s) {
        int d = ch - '0';

        if (d >= 2) {
            res = min(res, dfs(u * d, lim) + 1);
        }
    }

    return memo[u] = res;
}

void solve() {
    ll lim = 1;
    for (int i = 1; i <= n - 1; i++) lim *= 10;
    int ans = dfs(x, lim);

    cout << (ans < 1e9 ? ans : -1) << "\n";
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
        cin >> n >> x;
        solve();
    }

    return 0;
}