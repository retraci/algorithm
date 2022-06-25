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

const int MOD = 1e9 + 7;

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 50010;
const int M = 210;

int n, a, b;
int f[N][M];
int C[M][M];

void solve() {
    int ans = 1LL * f[n - 1][a + b - 2] * C[a + b - 2][a - 1] % MOD;
    cout << ans << "\n";
}

void prework() {
    f[0][0] = 1;
    for (int i = 1; i <= 50000; i++) {
        for (int j = 1; j <= 200; j++) {
            f[i][j] = f[i - 1][j - 1] + 1LL * (i - 1) * f[i - 1][j] % MOD;
            f[i][j] %= MOD;
        }
    }

    for (int i = 0; i <= 200; i++) C[i][0] = 1;
    for (int i = 1; i <= 200; i++) {
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
            C[i][j] %= MOD;
        }
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
        cin >> n >> a >> b;
        solve();
    }

    return 0;
}