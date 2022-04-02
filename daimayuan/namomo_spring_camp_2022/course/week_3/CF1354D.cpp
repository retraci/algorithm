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

int n, Q;
int a[N];
int bit[N];

void add(int id, int v) {
    for (int i = id; i <= n; i += i & -i) bit[i] += v;
}

int query(int id) {
    int res = 0;
    for (int i = id; i; i -= i & -i) res += bit[i];
    return res;
}

int bs(int k) {
    int pos = 0;
    for (int i = 20; i >= 0; i--) {
        int np = pos + (1 << i);
        if (np <= n && bit[np] < k) k -= bit[np], pos = np;
    }
    return pos;
}

void solve() {
    vector<int> c(n + 1);
    for (int i = 1; i <= n; i++) {
        add(a[i], 1);
        c[a[i]]++;
    }

    while (Q--) {
        int x;
        cin >> x;
        if (x >= 1) {
            add(x, 1);
            c[x]++;
        } else {
            x = -x;
            int id = bs(x) + 1;
            add(id, -1);
            c[id]--;
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (c[i] == 0) continue;
        ans = i;
        break;
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
    int T = 1;
//    cin >> T;
    while (T--) {
        cin >> n >> Q;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}