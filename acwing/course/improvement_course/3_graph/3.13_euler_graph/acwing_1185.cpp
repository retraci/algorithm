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

const int N = 1e5 + 10;

int n;
string a[N];
int din[26], dout[26];
int fa[26];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    fa[x] = y;
    return true;
}

void solve() {
    iota(fa, fa + 26, 0);
    memset(din, 0, sizeof din), memset(dout, 0, sizeof dout);
    for (int i = 1; i <= n; i++) {
        string s = a[i];
        int u = s[0] - 'a', v = s.back() - 'a';
        dout[u]++, din[v]++;
        unite(u, v);
    }

    int c1 = 0, c2 = 0, flag = 0;
    for (int i = 0; i < 26; i++) {
        int del = din[i] - dout[i];
        if (del == 0) continue;

        if (del == 1) c2++;
        else if (del == -1) c1++;
        else flag = 1;
    }
    if (flag || !(c1 == 0 && c2 == 0 || c1 == 1 && c2 == 1)) flag = 1;

    int cnt = 0;
    for (int i = 0; i < 26; i++) {
        if (din[i] + dout[i] == 0) continue;
        cnt += i == find(i);
    }
    if (cnt > 1) flag = 1;

    if (flag) cout << "The door cannot be opened." << "\n";
    else cout << "Ordering is possible." << "\n";
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
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}