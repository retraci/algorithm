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

const int N = 2e5 + 10;

int n;
int a[N];
vector<int> lsh;

int nl;
int bit[N];

void add(int id, int x) {
    for (int i = id; i <= nl; i += i & -i) bit[i] += x;
}

int query(int id) {
    int res = 0;
    for (int i = id; i; i -= i & -i) res += bit[i];
    return res;
}

int get(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

void init() {
    for (int i = 1; i <= n; i++) lsh.push_back(a[i]);
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
}

void solve() {
    init();
    nl = lsh.size();

    vector<ti3> qs[n + 1];
    for (int k = 1; k <= n - 1; k++) {
        for (int i = 1; i <= n; i++) {
            int L = k * (i - 1) + 2, R = min(n, k * i + 1);
            if (L > n) break;

            int x = get(a[i]) + 1;
            qs[L - 1].push_back({k, -1, x - 1});
            qs[R].push_back({k, 1, x - 1});
        }
    }

    vector<ll> ans(n, 0);
    for (int i = 1; i <= n; i++) {
        int x = get(a[i]) + 1;
        add(x, 1);

        for (auto [k, sign, y] : qs[i]) ans[k] += sign * query(y);
    }

    for (int k = 1; k <= n - 1; k++) cout << ans[k] << " ";
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}