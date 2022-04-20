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

int n, k;
int a[N];
int ne[N][2];
int mp[N];
int sc;

int calc(int i, int j) {
    return min(abs(i - j), n - abs(i - j));
}

int mov(int i, int j) {
    return ((i - 1 + j) % n + n) % n + 1;
}

void init() {
    set<int> st;
    st.insert(n + 1);
    for (int i = k + 1; i <= n; i++) st.insert(a[i]);
    sc = *st.begin();

    for (int i = 1; i <= n; i++) {
        int lb = i, rb = mov(lb, k - 1);
        ne[a[lb]][0] = *st.lower_bound(a[lb]);
        ne[a[rb]][1] = *st.lower_bound(a[rb]);

        int nrb = mov(rb, 1);
        st.erase(a[nrb]), st.insert(a[lb]);
    }

    for (int i = 1; i <= n; i++) mp[a[i]] = i;
}

void solve() {
    init();

    if (sc == n + 1) {
        cout << 0 << "\n";
        return;
    }

    ll ans = 1e18;
    ll f[n + 1][2];
    memset(f, 0x3f, sizeof f);
    f[sc][0] = calc(mp[sc], 1), f[sc][1] = calc(mp[sc], k);
    for (int i = sc; i <= n; i++) {
        {
            int v = ne[i][0];
            if (v == n + 1) {
                ans = min(ans, f[i][0]);
            } else {
                int id1 = mp[i], id2 = mp[v];
                f[v][0] = min(f[v][0], f[i][0] + calc(id2, id1));
                f[v][1] = min(f[v][1], f[i][0] + calc(id2, mov(id1, k - 1)));
            }
        }
        {
            int v = ne[i][1];
            if (v == n + 1) {
                ans = min(ans, f[i][1]);
            } else {
                int id1 = mp[i], id2 = mp[v];
                f[v][1] = min(f[v][1], f[i][1] + calc(id2, id1));
                f[v][0] = min(f[v][0], f[i][1] + calc(id2, mov(id1, -(k - 1))));
            }
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
    int T = 1;
    cin >> T;
    while (T--) {
        cin >> n >> k;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}