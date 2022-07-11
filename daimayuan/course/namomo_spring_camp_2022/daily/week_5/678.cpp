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

int n;
string s;
set<string> st;
int ans;

void dfs1(int cur, int ed, string &a, string &b) {
    if (cur > ed) {
        string &mi = a.size() < b.size() ? a : b;
        string &mx = a.size() > b.size() ? a : b;

        for (int i = 0; i < mi.size(); i++) {
            if (mi[i] != mx[i]) return;
        }
        st.insert(mx.substr(mi.size()));
        return;
    }

    a.push_back(s[cur]);
    dfs1(cur + 1, ed, a, b);
    a.pop_back();

    b.push_back(s[cur]);
    dfs1(cur + 1, ed, a, b);
    b.pop_back();
}

bool check(string a, string b) {
    if (a.size() > b.size()) swap(a, b);
    reverse(a.begin(), a.end()), reverse(b.begin(), b.end());
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) return false;
    }

    string pre = b.substr(a.length());
    reverse(pre.begin(), pre.end());
    return st.count(pre);
}

void dfs2(int cur, int ed, string &a, string &b) {
    if (ans) return;
    if (cur > ed) {
        if (check(a, b)) ans = 1;
        return;
    }

    a.push_back(s[cur]);
    dfs2(cur + 1, ed, a, b);
    a.pop_back();

    b.push_back(s[cur]);
    dfs2(cur + 1, ed, a, b);
    b.pop_back();
}

void solve() {
    n = s.length(); s = " " + s;

    st = {}; ans = 0;
    string a = "", b = "";
    dfs1(1, n / 2, a, b);
    dfs2(n / 2 + 1, n, a, b);

    cout << (ans ? "possible" : "impossible") << "\n";
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
        cin >> s;
        solve();
    }

    return 0;
}