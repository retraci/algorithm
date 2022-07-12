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
const int N = 1e6 + 10;

int n;
int fa[N];
int dep[N];
ll f[N][2];

void solve() {
    dep[1] = 0;
    for (int v = 2; v <= n; v++) {
        int u = fa[v];
        dep[v] = dep[u] + 1;
    }

    for (int u = 1; u <= n; u++) {
        f[u][0] = 0, f[u][1] = dep[u];
    }
    for (int v = n; v >= 2; v--) {
        int u = fa[v];

        f[u][1] = min({f[u][1] + f[v][0] + 2, f[u][0] + f[v][1], f[u][1] + f[v][1]});
        f[u][0] += f[v][0] + 2;
    }

    static char buf[111];
    static int tc = 0;
    sprintf(buf, "Case #%d: %lld", ++tc, f[1][1]);
    cout << string(buf) << "\n";
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
        cin >> n;
        for (int i = 2; i <= n; i++) cin >> fa[i];
        solve();
    }

    return 0;
}