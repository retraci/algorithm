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

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 210;

int n, mod;
int C[N][N];
int g[N], pwn[N];

void init() {
    for (int i = 0; i <= n; i++) C[i][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            C[i][j] += C[i - 1][j] + C[i - 1][j - 1];
            C[i][j] %= mod;
        }
    }

    g[1] = 1, g[2] = 0, g[3] = 1;
    for (int i = 4; i <= n; i++) {
        g[i] = 1LL * g[i - 1] * (i - 1) % mod;
    }

    pwn[0] = 1;
    for (int i = 1; i <= n; i++) pwn[i] = 1LL * pwn[i - 1] * n % mod;
}

void solve() {
    init();

    int f[n + 1][n + 1];
    memset(f, 0, sizeof f);
    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            for (int k = 1; k <= i; k++) {
                f[i][j] += 1LL * f[i - k][j - 1] * C[i - 1][k - 1] % mod * g[k] % mod * k % mod;
                f[i][j] %= mod;
            }
        }
    }

    int ans = g[n];
    for (int j = 2; j <= n; j++) {
        ans += 1LL * f[n][j] * pwn[j - 2] % mod;
        ans %= mod;
    }
    cout << ans << "\n";
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
        cin >> n >> mod;
        solve();
    }

    return 0;
}