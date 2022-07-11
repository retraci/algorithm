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
#include <random>

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

int n;
int id[N];

int ask(int op, int x) {
    if (op == 1) cout << "> ";
    else cout << "? ";
    cout << x << "\n";
    cout.flush();

    int res;
    cin >> res;
    return res;
}

void solve() {
    iota(id, id + n + 1, 0);
    mt19937 rng(time(0));
    shuffle(id + 1, id + n + 1, rng);
    int rem = 60;

    int left = 0, right = 1e9;
    while (left < right) {
        int md = left + right >> 1;
        if (ask(1, md)) left = md + 1;
        else right = md;
        rem--;
    }
    int mx = left;

    vector<int> b;
    int cur = 1;
    while (rem > 0 && cur <= n) {
        int idx = id[cur];
        b.push_back(ask(2, idx));
        rem--, cur++;
    }

    int d = 0;
    b.push_back(mx);
    sort(b.begin(), b.end());
    for (int i = 1; i < b.size(); i++) {
        d = __gcd(d, b[i] - b[i - 1]);
    }

    int mi = mx - (n - 1) * d;
    cout << "! " << mi << " " << d << "\n";
}

void prework() {
}

int main() {
//#ifdef LOCAL
//    freopen("../in.txt", "r", stdin);
//    freopen("../out.txt", "w", stdout);
//#endif

    prework();
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1;
//    cin >> T;
    while (T--) {
        cin >> n;
        solve();
    }

    return 0;
}