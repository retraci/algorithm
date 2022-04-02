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

typedef array<int, 5> ai5;

const int N = 2e5 + 10;

int n, m;
ti3 a[N];
int b[N];

int tt;
ai5 q[2 * N], q1[2 * N], q2[2 * N];
int ans[N];

int tr[N];

void add(int id, int x) {
    for (int i = id; i < N; i += i & -i) tr[i] += x;
}

int query(int id) {
    int res = 0;
    for (int i = id; i; i -= i & -i) res += tr[i];
    return res;
}

void init() {
    for (int i = 1; i <= m; i++) {
        q[++tt] = {b[i], b[i], 0, 0, i};
    }
    for (int i = 1; i <= n; i++) {
        auto [L, R, s] = a[i];
        q[++tt] = {L, R, s, 1, i};
    }
}

void work(int left, int right, int ql, int qr) {
    if (ql > qr) return;
    if (left == right) {
        for (int i = ql; i <= qr; i++) {
            auto [L, R, s, ty, id] = q[i];
            if (ty) ans[id] = left;
        }
        return;
    }

    int md = left + right >> 1, c1 = 0, c2 = 0;
    for (int i = ql; i <= qr; i++) {
        auto &[L, R, s, ty, id] = q[i];

        if (ty) {
            int sum = query(R) - query(L - 1);
            if (sum >= s) {
                q1[++c1] = q[i];
            } else {
                s -= sum;
                q2[++c2] = q[i];
            }
        } else {
            if (id <= md) {
                add(L, 1);
                q1[++c1] = q[i];
            } else {
                q2[++c2] = q[i];
            }
        }
    }

    for (int i = 1; i <= c1; i++) {
        auto [L, R, s, ty, id] = q1[i];
        if (!ty) add(L, -1);
    }
    for (int i = 1; i <= c1; i++) q[ql + i - 1] = q1[i];
    for (int i = 1; i <= c2; i++) q[ql + c1 + i - 1] = q2[i];
    work(left, md, ql, ql + c1 - 1), work(md + 1, right, ql + c1, qr);
}

void solve() {
    init();

    work(1, m + 1, 1, tt);
    vector<int> c(m + 1, 0);
    for (int i = 1; i <= n; i++) c[ans[i]]++;
    for (int i = 1; i <= m; i++) {
        cout << c[i] << "\n";
    }
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
        for (int i = 1; i <= n; i++) {
            int L, R, s;
            cin >> L >> R >> s;
            a[i] = {L, R, s};
        }
        for (int i = 1; i <= m; i++) cin >> b[i];

        solve();
    }

    return 0;
}