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

ll L, R;
vector<int> ps;
int isp2[N];

// region 埃筛
int isp[N];

void prime(int lim) {
    fill(isp, isp + lim + 1, 1);

    isp[0] = isp[1] = 0;
    for (int i = 2; i <= lim; i++) {
        if (!isp[i]) continue;

        ps.push_back(i);
        for (int j = i * 2; j <= lim; j += i) isp[j] = 0;
    }
}
// endregion

void solve() {
    ll sz = R - L + 1;
    fill(isp2, isp2 + sz, 1);
    for (int p : ps) {
        ll k = max(2LL, 1LL * (L + p - 1) / p);
        for (ll j = k * p; j <= R; j += p) {
            isp2[j - L] = 0;
        }
    }

    vector<int> ps2;
    for (ll i = L; i <= R; i++) {
        if (isp2[i - L] && i >= 2) ps2.push_back(i);
    }
    if (ps2.size() < 2) {
        cout << "There are no adjacent primes." << "\n";
        return;
    }

    int mi = 1, mx = 1;
    for (int i = 1; i < ps2.size(); i++) {
        int d = ps2[i] - ps2[i - 1];
        if (d < ps2[mi] - ps2[mi - 1]) mi = i;
        if (d > ps2[mx] - ps2[mx - 1]) mx = i;
    }

    char out[100];
    snprintf(out, 100, "%d,%d are closest, %d,%d are most distant.", ps2[mi - 1], ps2[mi], ps2[mx - 1], ps2[mx]);
    cout << string(out) << "\n";
}

void prework() {
    prime(50000);
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
    while (cin >> L >> R) {
        solve();
    }

    return 0;
}