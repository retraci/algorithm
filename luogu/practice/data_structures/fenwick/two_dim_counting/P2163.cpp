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

const int N = 5e5 + 10;

int n, m;
pii a[N];
ti4 b[N];

vector<int> lsh;
int nl;
int tr[6 * N];

vector<ti3> qs[4 * N];
int ans[N];

void add(int id, int x) {
    for (int i = id; i <= nl; i += i & -i) tr[i] += x;
}

int qr(int id) {
    int res = 0;
    for (int i = id; i; i -= i & -i) res += tr[i];
    return res;
}

int get(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

void init() {
    for (int i = 1; i <= n; i++) {
        auto [x, y] = a[i];
        lsh.push_back(x), lsh.push_back(y);
    }
    for (int i = 1; i <= m; i++) {
        auto [x1, y1, x2, y2] = b[i];
        lsh.push_back(x1), lsh.push_back(y1);
        lsh.push_back(x2), lsh.push_back(y2);
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nl = lsh.size();

    for (int i = 1; i <= n; i++) {
        auto &[x, y] = a[i];
        x = get(x) + 1, y = get(y) + 1;
    }
    for (int i = 1; i <= m; i++) {
        auto &[x1, y1, x2, y2] = b[i];

        x1 = get(x1) + 1, y1 = get(y1) + 1;
        x2 = get(x2) + 1, y2 = get(y2) + 1;
    }
}

void solve() {
    init();

    sort(a + 1, a + n + 1);
    for (int i = 1; i <= m; i++) {
        auto [x1, y1, x2, y2] = b[i];

        qs[x2].push_back({y2, 1, i});
        qs[x1 - 1].push_back({y2, -1, i});
        qs[x2].push_back({y1 - 1, -1, i});
        qs[x1 - 1].push_back({y1 - 1, 1, i});
    }

    int pos = 1;
    for (int i = 0; i <= nl; i++) {
        while (pos <= n) {
            auto [x, y] = a[pos];
            if (x > i) break;

            add(y, 1);
            pos++;
        }

        for (auto [y, sign, qid] : qs[i]) {
            int tmp = sign * qr(y);
            ans[qid] += tmp;
        }
    }

    for (int i = 1; i <= m; i++) cout << ans[i] << "\n";
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
            int x, y;
            cin >> x >> y;
            a[i] = {x, y};
        }
        for (int i = 1; i <= m; i++) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            b[i] = {x1, y1, x2, y2};
        }

        solve();
    }

    return 0;
}