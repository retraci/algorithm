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

// region general
#define ll long long
#define ld long double
#define ull unsigned long long
#define fi first
#define se second

typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
typedef std::tuple<int, int, int> ti3;
typedef std::tuple<ll, ll, ll> tl3;
typedef std::tuple<int, int, int, int> ti4;
typedef std::tuple<ll, ll, ll, ll> tl4;

inline void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
inline void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}
// endregion
// region grid_delta
namespace grid_delta {
    // 上, 右, 下, 左  |  左上, 右上, 右下, 左下
    const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
}
// endregion

using namespace std;
using namespace grid_delta;

const int N = 1e6 + 10;

int n;
string s;

int sa[N], x[N], y[N], c[N], rk[N];

void get_sa() {
    int sz = 122;

    for (int i = 1; i <= n; i++) c[x[i] = s[i]]++;
    for (int i = 1; i <= sz; i++) c[i] += c[i - 1];
    for (int i = n; i >= 1; i--) sa[c[x[i]]--] = i;

    for (int k = 1; k <= n; k *= 2) {
        int num = 0;
        for (int i = n - k + 1; i <= n; i++) y[++num] = i;
        for (int i = 1; i <= n; i++) {
            if (sa[i] - k >= 1) y[++num] = sa[i] - k;
        }

        for (int i = 1; i <= sz; i++) c[i] = 0;
        for (int i = 1; i <= n; i++) c[x[i]]++;
        for (int i = 1; i <= sz; i++) c[i] += c[i - 1];
        for (int i = n; i >= 1; i--) sa[c[x[y[i]]]--] = y[i], y[i] = 0;

        swap(x, y);
        x[sa[1]] = 1, num = 1;
        for (int i = 2; i <= n; i++) {
            x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++num;
        }
        if (num == n) break;
        sz = num;
    }
}

void solve() {
    n = s.size() - 1;
    get_sa();
    for (int i = 1; i <= n; i++) cout << sa[i] << " ";
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
    int T = 1;
//    cin >> T;
    while (T--) {
        cin >> s;
        s = ' ' + s;
        solve();
    }

    return 0;
}