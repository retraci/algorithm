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
#include <cassert>
#include <random>
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
using ai3 = array<int, 3>;
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 110;

int n, m;
int a[N][N];
int sx[N], sy[N];

void solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            sx[i] += a[i][j], sy[j] += a[i][j];
        }
    }

    vector<int> x(n + 1), y(m + 1);
    while (1) {
        int flag = 0;
        for (int i = 1; i <= n; i++) {
            if (sx[i] < 0) {
                flag = 1, x[i] ^= 1;
                sx[i] = -sx[i];

                for (int j = 1; j <= m; j++) {
                    a[i][j] = -a[i][j];
                    sy[j] += 2 * a[i][j];
                }
            }
        }

        for (int j = 1; j <= m; j++) {
            if (sy[j] < 0) {
                flag = 1, y[j] ^= 1;
                sy[j] = -sy[j];

                for (int i = 1; i <= n; i++) {
                    a[i][j] = -a[i][j];
                    sx[i] += 2 * a[i][j];
                }
            }
        }

        if (!flag) break;
    }

    int cx = accumulate(x.begin() + 1, x.end(), 0);
    cout << cx << " ";
    for (int i = 1; i <= n; i++) {
        if (x[i]) cout << i << " ";
    }
    cout << "\n";

    int cy = accumulate(y.begin() + 1, y.end(), 0);
    cout << cy << " ";
    for (int j = 1; j <= m; j++) {
        if (y[j]) cout << j << " ";
    }
    cout << "\n";
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
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> a[i][j];
            }
        }
        solve();
    }

    return 0;
}