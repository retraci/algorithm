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
const ll MOD = 1e9 + 7;

int n, p;
int va[N];
ll f[N];
unordered_set<int> st;

bool check(int x) {
    while (x) {
        if (st.count(x)) return false;
        if (x & 1) x >>= 1;
        else if ((x & 3) == 0) x >>= 2;
        else break;
    }

    return true;
}

void solve() {
    sort(va + 1, va + n + 1);
    for (int i = 1; i <= n; i++) {
        int x = va[i];
        if (check(x)) f[__lg(x) + 1]++;
        st.insert(x);
    }

    for (int i = 1; i <= p; i++) {
        if (i - 1 >= 0) f[i] += f[i - 1];
        if (i - 2 >= 0) f[i] += f[i - 2];
        f[i] %= MOD;
    }

    ll ans = 0;
    for (int i = 1; i <= p; i++) {
        ans += f[i];
        ans %= MOD;
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
        cin >> n >> p;
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}