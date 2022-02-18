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
    const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}, {0, 0}};
}
// endregion

using namespace std;
using namespace grid_delta;

char g[2][4];
string st, ed;
unordered_map<string, int> dist;
unordered_map<string, pair<string, char>> pre;

void set_g(string u) {
    for (int i = 0; i < 4; i++) g[0][i] = u[i];
    for (int i = 7, j = 0; j < 4; i--, j++) g[1][j] = u[i];
}

string get_g() {
    string res;
    for (int i = 0; i < 4; i++) res += g[0][i];
    for (int i = 3; i >= 0; i--) res += g[1][i];
    return res;
}

string work1(string u) {
    set_g(u);
    for (int i = 0; i < 4; i++) swap(g[0][i], g[1][i]);
    return get_g();
}

string work2(string u) {
    set_g(u);
    char v0 = g[0][3], v1 = g[1][3];
    for (int i = 3; i >= 0; i--) {
        g[0][i] = g[0][i - 1];
        g[1][i] = g[1][i - 1];
    }
    g[0][0] = v0, g[1][0] = v1;
    return get_g();
}

string work3(string u) {
    set_g(u);
    int v = g[0][1];
    g[0][1] = g[1][1];
    g[1][1] = g[1][2];
    g[1][2] = g[0][2];
    g[0][2] = v;
    return get_g();
}

int bfs() {
    if (st == ed) return 0;

    queue<string> que;
    que.push(st);
    dist[st] = 0;
    while (!que.empty()) {
        auto u = que.front(); que.pop();

        string vs[3];
        vs[0] = work1(u);
        vs[1] = work2(u);
        vs[2] = work3(u);

        for (int i = 0; i < 3; i++) {
            string v = vs[i];
            if (!dist.count(v)) {
                dist[v] = dist[u] + 1;
                pre[v] = {u, 'A' + i};
                que.push(v);
                if (v == ed) return dist[v];
            }
        }
    }

    return -1;
}

void solve() {
    int step = bfs();

    cout << step << "\n";
    string path = "";
    while (ed != st) {
        path += pre[ed].se;
        ed = pre[ed].fi;
    }
    reverse(path.begin(), path.end());
    if (!path.empty()) cout << path << "\n";
}

void prework() {
    st = "12345678";
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
        for (int i = 1; i <= 8; i++) {
            int x;
            cin >> x;
            ed += (char) ('0' + x);
        }
        solve();
    }

    return 0;
}