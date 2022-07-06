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

const int N = 3e5 + 10;

int n, m;
int a[N];
ti3 b[N];

int cnt;
pii c[2 * N];

int tr[N];

void add(int id, int x) {
    for (int i = id; i <= n; i += i & -i) tr[i] += x;
}

int qr(int id) {
    int res = 0;
    for (int i = id; i; i -= i & -i) res += tr[i];
    return res;
}

void init() {
    a[0] = -1e9, a[n + 1] = 2e9;
    vector<int> idx(n + 2);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](auto &lhs, auto &rhs) {
        return a[lhs] < a[rhs];
    });
    for (int i = 1; i <= n; i++) {
        int id1 = idx[i - 1], id = idx[i], id2 = idx[i + 1];
        int d1 = a[id] - a[id1], d2 = a[id2] - a[id];
        if (d1 <= d2) c[++cnt] = {min(id, id1), max(id, id1)};
        if (d2 <= d1) c[++cnt] = {min(id, id2), max(id, id2)};
    }
}

void solve() {
    if (n == 1) {
        cout << 0 << "\n";
        return;
    }

    init();

    sort(c + 1, c + cnt + 1, [](auto &a, auto &b) {
        return a.se < b.se;
    });
    sort(b + 1, b + m + 1, [](auto &a, auto &b) {
        return get<1>(a) < get<1>(b);
    });

    vector<int> ask(m + 1);
    int pos = 1;
    for (int i = 1; i <= m; i++) {
        auto [L, R, qid] = b[i];
        while (pos <= cnt && c[pos].se <= R) {
            add(c[pos].fi, 1);
            pos++;
        }

        ask[qid] = qr(R) - qr(L - 1);
    }

    ll ans = 0;
    for (int i = 1; i <= m; i++) ans += 1LL * ask[i] * i;
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
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= m; i++) {
            int L, R;
            cin >> L >> R;
            b[i] = {L, R, i};
        }
        solve();
    }

    return 0;
}