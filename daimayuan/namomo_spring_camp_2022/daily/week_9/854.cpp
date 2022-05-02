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

int a[4][4];

void solve() {
    int ans = 0;
    for (int x1 = 1; x1 <= 3; x1++) {
        for (int y1 = 1; y1 <= 3; y1++) {
            int cnt = 0;
            for (int x2 = 1; x2 <= 3; x2++) {
                for (int y2 = 1; y2 <= 3; y2++) {
                    if (x1 == x2 || y1 == y2) continue;

                    int s = 0;
                    for (int i = 1; i <= 3; i++) {
                        for (int j = 1; j <= 3; j++) {
                            if (i == x1 && j == y1 || i == x2 && j == y2) continue;

                            if (i == x1 || i == x2 || j == y1 || j == y2) s ^= (a[i][j] - 1);
                            else s ^= a[i][j];
                        }
                    }

                    cnt += s > 0;
                }
            }

            ans += cnt == 4;
        }
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
    cin >> _;
    while (_--) {
        for (int i = 1; i <= 3; i++) {
            for (int j = 1; j <= 3; j++) {
                cin >> a[i][j];
            }
        }
        solve();
    }

    return 0;
}