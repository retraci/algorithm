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

int n, m;
int a[N];
ti3 b[N];

vector<int> lsh;
int nl;
int bit[N * 2];

int lowbit(int x) {
    return x & -x;
}

void modify(int id, int x) {
    for (int i = id; i <= nl; i += lowbit(i)) bit[i] += x;
}

int query(int id) {
    int res = 0;
    for (int i = id; i; i -= lowbit(i)) res += bit[i];
    return res;
}


int get(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

void solve() {
    lsh.clear();
    for (int i = 1; i <= n; i++) lsh.push_back(a[i]);
    for (int i = 1; i <= m; i++) {
        auto [L, R, h] = b[i];
        lsh.push_back(h);
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());

    nl = lsh.size();
    fill(bit, bit + nl + 1, 0);
    vector<int> qs[n + 1];
    unordered_map<int, int> ask[n + 1];
    for (int i = 1; i <= m; i++) {
        auto [L, R, h] = b[i];
        h = get(h) + 1;

        qs[L - 1].push_back(h);
        qs[R].push_back(h);
    }

    for (int i = 1; i <= n; i++) {
        int x = get(a[i]) + 1;
        modify(x, 1);

        for (int h : qs[i]) {
            ask[i][h] = query(h);
        }
    }

    for (int i = 1; i <= m; i++) {
        auto [L, R, h] = b[i];
        h = get(h) + 1;

        cout << ask[R][h] - ask[L - 1][h] << " ";
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
    int T = 1;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= m; i++) {
            int L, R, h;
            cin >> L >> R >> h;
            b[i] = {L, R, h};
        }

        solve();
    }

    return 0;
}