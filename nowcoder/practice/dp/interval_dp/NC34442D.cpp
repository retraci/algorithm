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
const int N = 5010;

int n;
int a[N], b[N];

void solve() {
    int g[n + 1][n + 1];
    memset(g, 0, sizeof g);
    for (int i = 1; i <= n; i++) g[i][i] = a[i] * b[i];
    for (int len = 2; len <= n; len++) {
        for (int L = 1; L + len - 1 <= n; L++) {
            int R = L + len - 1;

            g[L][R] = g[L + 1][R - 1] + a[L] * b[R] + a[R] * b[L];
        }
    }

    int f[n + 1];
    memset(f, 0, sizeof f);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            f[i] = max(f[i], f[j - 1] + g[j][i]);
        }
    }

    cout << f[n] << "\n";
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
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        solve();
    }

    return 0;
}