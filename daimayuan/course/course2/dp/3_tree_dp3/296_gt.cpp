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
const int N = 2e3 + 10;
const ll INF = 1e18;

int n;
int a[N];
int fa[N];
int sz[N];
ll f[N][N][2];

void solve() {
    for (int u = 1; u <= n; u++) {
        sz[u] = 1;
        f[u][0][0] = a[u];
        f[u][1][1] = 0;
        f[u][1][0] = f[u][0][1] = INF;
    }

    static ll tmp[N][2];
    for (int v = n; v >= 2; v--) {
        int u = fa[v];

        for (int j = 0; j <= sz[u] + sz[v]; j++) tmp[j][0] = tmp[j][1] = INF;
        for (int j = 0; j <= sz[u]; j++) {
            for (int k = 0; k <= sz[v]; k++) {
                tmp[j + k][0] = min({tmp[j + k][0], f[u][j][0] + f[v][k][0] + a[v], f[u][j][0] + f[v][k][1]});
                tmp[j + k][1] = min({tmp[j + k][1], f[u][j][1] + f[v][k][0], f[u][j][1] + f[v][k][1]});
            }
        }

        for (int j = 0; j <= sz[u] + sz[v]; j++) f[u][j][0] = tmp[j][0], f[u][j][1] = tmp[j][1];
        sz[u] += sz[v];
    }

    for (int j = 0; j <= n; j++) {
        cout << min(f[1][j][0], f[1][j][1]) << " \n"[j == n];
    }
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
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}