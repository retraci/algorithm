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
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

const int MOD = 998244353;


int ksm(int a, int b) {
    a %= MOD;
    int res = 1;
    while (b) {
        if (b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }

    return res;
}

int inv(int a) {
    return ksm(a, MOD - 2);
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 2e5 + 10;
const int M = 2e5 + 10;

int n;
ai3 e[M * 2];
int ne[M * 2], h[N], edm;
vector<pii> fac[N];
int c[N], mi[N];
int ans;

void add(int u, int v, int x, int y) {
    e[edm] = {v, x, y}, ne[edm] = h[u], h[u] = edm++;
}

void dfs1(int u, int fno) {
    for (int i = h[u]; ~i; i = ne[i]) {
        auto [v, x, y] = e[i];
        if (v == fno) continue;

        for (auto [p, cnt] : fac[y]) c[p] += cnt;
        for (auto [p, cnt] : fac[x]) {
            c[p] -= cnt;
            mi[p] = min(mi[p], c[p]);
        }

        dfs1(v, u);

        for (auto [p, cnt] : fac[y]) c[p] -= cnt;
        for (auto [p, cnt] : fac[x]) c[p] += cnt;
    }
}

void dfs2(int u, int fno, int cur) {
    ans += cur;
    ans %= MOD;

    for (int i = h[u]; ~i; i = ne[i]) {
        auto [v, x, y] = e[i];
        if (v == fno) continue;

        int ns = cur;
        for (auto [p, cnt] : fac[y]) ns = 1LL * ns * ksm(p, cnt) % MOD;
        for (auto [p, cnt] : fac[x]) ns = 1LL * ns * inv(ksm(p, cnt)) % MOD;

        dfs2(v, u, ns);
    }
}

void solve() {
    fill(mi, mi + n + 1, 0);
    dfs1(1, -1);

    int cur = 1;
    for (int i = 2; i <= n; i++) {
        cur = 1LL * cur * ksm(i, -mi[i]) % MOD;
    }

    ans = 0;
    dfs2(1, -1, cur);

    cout << ans << "\n";
}

void prework() {
    for (int i = 2; i <= 2e5; i++) {
        int x = i;
        for (int j = 2; j <= i / j; j++) {
            if (i % j) continue;

            int cnt = 0;
            while (x % j == 0) cnt++, x /= j;
            fac[i].push_back({j, cnt});
        }

        if (x > 1) fac[i].push_back({x, 1});
    }
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
        cin >> n;
        fill(h, h + n + 1, -1), edm = 0;

        for (int i = 1; i <= n - 1; i++) {
            int u, v, x, y;
            cin >> u >> v >> x >> y;
            int gcd = __gcd(x, y);
            x /= gcd, y /= gcd;
            add(u, v, x, y), add(v, u, y, x);
        }

        solve();
    }

    return 0;
}