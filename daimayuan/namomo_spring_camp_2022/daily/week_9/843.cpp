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

const int N = 5010;

int n;
int a[N];

void solve() {
    sort(a + 1, a + n + 1);

    int f[n + 1][n + 1];
    memset(f, 0, sizeof f);
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            f[i][j] = 2;
        }
    }
    for (int i = 1; i <= n; i++) {
        int L = i - 1, R = i + 1;
        while (L >= 1 && R <= n) {
            if (a[L] + a[R] == 2 * a[i]) {
                f[i][R] = max(f[i][R], f[L][i] + 1);
                L--;
            } else if (a[L] + a[R] < 2 * a[i]) {
                R++;
            } else {
                L--;
            }
        }
    }

    int ans = *max_element(&f[1][1], &f[n][n]);
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}