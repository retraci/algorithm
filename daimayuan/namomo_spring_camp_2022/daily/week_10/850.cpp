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
#include <random>

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
const int N = 2010;
const int MOD = 1e9 + 7;

int n;
int f[N][N];

void solve() {
    int ans = 0;
    for (int h = 1; h <= 20; h++) {
        ans += f[n][h];
        ans %= MOD;
    }
    cout << ans << "\n";
}

void prework() {
    f[0][0] = f[1][1] = 1;
    for (int i = 2; i <= 2000; i++) {
        for (int h = 1; h <= 20; h++) {
            for (int ls = 0; ls <= i - 1; ls++) {
                int rs = i - ls - 1;
                f[i][h] += 1LL * f[ls][h - 1] * f[rs][h - 1] % MOD;
                f[i][h] %= MOD;
                f[i][h] += 1LL * f[ls][h - 1] * f[rs][h - 2] % MOD;
                f[i][h] %= MOD;
                f[i][h] += 1LL * f[ls][h - 2] * f[rs][h - 1] % MOD;
                f[i][h] %= MOD;
            }
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
        cin >> n;
        solve();
    }

    return 0;
}