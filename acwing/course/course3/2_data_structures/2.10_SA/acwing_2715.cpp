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

int n;
string s;

// region 后缀数组
int sa[N], rk[N], tp[N], c[N], h[N];

bool cmp(int i, int k) {
    return tp[sa[i - 1]] == tp[sa[i]] && tp[sa[i - 1] + k] == tp[sa[i] + k];
}

void tsort(int ta[], int fir[], int sed[], int sz) {
    for (int i = 1; i <= sz; i++) c[i] = 0;
    for (int i = 1; i <= n; i++) c[fir[i]]++;
    for (int i = 1; i <= sz; i++) c[i] += c[i - 1];
    for (int i = n; i >= 1; i--) ta[c[fir[sed[i]]]--] = sed[i];
}

void get_sa() {
    int sz = 122;
    for (int i = 1; i <= n; i++) rk[i] = s[i], tp[i] = i;
    tsort(sa, rk, tp, sz);
    for (int k = 1; k <= n; k *= 2) {
        int num = 0;
        for (int i = n - k + 1; i <= n; i++) tp[++num] = i;
        for (int i = 1; i <= n; i++) {
            if (sa[i] - k >= 1) tp[++num] = sa[i] - k;
        }

        tsort(sa, rk, tp, sz), swap(rk, tp);
        rk[sa[1]] = 1, num = 1;
        for (int i = 2; i <= n; i++) {
            rk[sa[i]] = cmp(i, k) ? num : ++num;
        }
        if (num == n) break;
        sz = num;
    }
}

void get_h() {
    for (int i = 1, k = 0; i <= n; i++) {
        if (rk[i] == 1) continue;
        int j = sa[rk[i] - 1];
        if (k) k--;
        while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k++;
        h[rk[i]] = k;
    }
}
// endregion

void solve() {
    n = s.size() - 1;
    get_sa();
    get_h();

    for (int i = 1; i <= n; i++) cout << sa[i] << " ";
    cout << "\n";
    for (int i = 1; i <= n; i++) cout << h[i] << " ";
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
        cin >> s;
        s = ' ' + s;
        solve();
    }

    return 0;
}