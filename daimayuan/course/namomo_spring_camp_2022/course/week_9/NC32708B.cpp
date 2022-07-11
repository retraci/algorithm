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
#include <cmath>

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
using ull = unsigned long long;
using pii = pair<int, int>;
using ai4 = array<int, 4>;

const int N = 11;
const int MOD = 998244353;

int n, w, h;
ai4 a[N];
int f[1 << N];
vector<int> lsh;

int ksm(int e, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1LL * res * e % MOD;
        e = 1LL * e * e % MOD;
        b >>= 1;
    }
    return res;
}

int inv(int x) {
    return ksm(x, MOD - 2);
}

int get(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

void init() {
    lsh = {};
    lsh.push_back(0);
    lsh.push_back(w), lsh.push_back(h);
    for (int i = 0; i < n; i++) {
        auto [x1, y1, x2, y2] = a[i];

        lsh.push_back(x1), lsh.push_back(y1);
        lsh.push_back(x2), lsh.push_back(y2);
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());

    w = get(w), h = get(h);
    for (int i = 0; i < n; i++) {
        auto &[x1, y1, x2, y2] = a[i];

        x1 = get(x1), y1 = get(y1);
        x2 = get(x2), y2 = get(y2);
    }
}

bool check(int mask) {
    int vis[w + 1][h + 1];
    memset(vis, 0, sizeof vis);
    for (int k = 0; k < n; k++) {
        if (mask >> k & 1) {
            auto [x1, y1, x2, y2] = a[k];

            for (int i = x1 + 1; i <= min(x2, w); i++) {
                for (int j = y1 + 1; j <= min(y2, h); j++) {
                    vis[i][j] = 1;
                }
            }
        }
    }

    int flag = 0;
    for (int i = 1; i <= w; i++) {
        for (int j = 1; j <= h; j++) {
            if (!vis[i][j]) flag = 1;
        }
    }

    return !flag;
}

int dfs(int u) {
    if (f[u] != -1) return f[u];
    if (check(u)) return f[u] = 0;

    int res = 0, cnt = 0;
    for (int i = 0; i < n; i++) {
        if (u >> i & 1) {
            cnt++;
            continue;
        }

        int v = u + (1 << i);
        res += 1LL * dfs(v) * inv(n) % MOD;
        res %= MOD;
    }
    res = 1LL * n * inv(n - cnt) % MOD * res % MOD;
    res += 1LL * n * inv(n - cnt) % MOD;
    res %= MOD;

    return f[u] = res;
}

void solve() {
    init();

    int lim = 1 << n;
    if (!check(lim - 1)) {
        cout << -1 << "\n";
        return;
    }

    fill(f, f + lim, -1);
    cout << dfs(0) << "\n";
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
    cin >> _;
    while (_--) {
        cin >> n >> w >> h;
        for (int i = 0; i < n; i++) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            a[i] = {x1, y1, x2, y2};
        }
        solve();
    }

    return 0;
}