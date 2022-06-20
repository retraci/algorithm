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

int n;
string s;

void solve() {
    int f[n / 2 + 1][2];
    memset(f, 0x3f, sizeof f);

    int ans = 0;
    f[0][0] = f[0][1] = 1;
    for (int i = 1; i <= n / 2; i++) {
        int x = (s[i * 2 - 1] - '0') + (s[i * 2] - '0');

        if (x == 0) f[i][0] = min(f[i - 1][0], f[i - 1][1] + 1);
        if (x == 2) f[i][1] = min(f[i - 1][0] + 1, f[i - 1][1]);
        if (x == 1) {
            ans++;
            f[i][0] = min(f[i - 1][0], f[i - 1][1] + 1);
            f[i][1] = min(f[i - 1][0] + 1, f[i - 1][1]);
        }
    }
    cout << ans << " " << min(f[n / 2][0], f[n / 2][1]) << "\n";
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
        cin >> s;
        s = ' ' + s;
        solve();
    }

    return 0;
}