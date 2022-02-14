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
    // 上, 右, 下, 左  |  左上, 右上, 左下, 右下
    const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
    const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};
}
// endregion

using namespace std;
using namespace grid_delta;

const int N = 15;

ll L, R;
ll f[N][10][10];

void init() {
    for (int i = 0; i <= 9; i++) f[1][i][i] = 1;

    ll cur = 10;
    for (int i = 2; i < N; i++, cur *= 10) {
        for (int j = 0; j <= 9; j++) {
            for (int k = 0; k <= 9; k++) {
                for (int q = 0; q <= 9; q++) f[i][j][k] += f[i - 1][q][k];
                if (j == k) f[i][j][k] += cur;
            }
        }
    }
}

vector<ll> work(ll n) {
    if (n == 0) return vector<ll>(10, 0);

    vector<int> va;
    while (n) va.push_back(n % 10), n /= 10;

    vector<ll> res(10, 0);
    for (int i = 1; i < va.size(); i++) {
        for (int j = 1; j <= 9; j++) {
            for (int k = 0; k <= 9; k++) {
                res[k] += f[i][j][k];
            }
        }
    }

    for (int i = va.size() - 1; i >= 0; i--) {
        int x = va[i];

        for (int j = 0; j < x; j++) {
            if (j == 0 && i == va.size() - 1) continue;
            for (int k = 0; k <= 9; k++) {
                res[k] += f[i + 1][j][k];
            }
        }

        if (i == 0) {
            ll sum = 0, pow = 1;
            for (int k = 0; k < va.size(); k++, pow *= 10) {
                res[va[k]] += sum + 1;
                sum += va[k] * pow;
            }
        }
    }
    
    return res;
}

void solve() {
    init();
    vector<ll> ret1 = work(R), ret2 = work(L - 1);

    for (int i = 0; i <= 9; i++) cout << ret1[i] - ret2[i] << " ";
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
        cin >> L >> R;
        solve();
    }

    return 0;
}