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

const int N = 8;

string st, ed;
string va[N], vb[N];
int tt;

int work(queue<string> &que, unordered_map<string, int> &d1, unordered_map<string, int> &d2, string *vu, string *vv) {
    int sz = que.size();
    while (sz--) {
        auto u = que.front(); que.pop();

        for (int i = 0; i < tt; i++) {
            int pos = 0;
            while (1) {
                int id = u.find(vu[i], pos);
                if (id == -1) break;

                string v = u.substr(0, id) + vv[i] + u.substr(id + vu[i].size());
                if (!d1.count(v)) {
                    d1[v] = d1[u] + 1;
                    que.push(v);
                    if (d2.count(v)) return d1[v] + d2[v];
                }

                pos = id + vu[i].size();
            }
        }
    }

    return -1;
}

int bfs() {
    if (st == ed) return 0;

    queue<string> q1, q2;
    unordered_map<string, int> d1, d2;
    d1[st] = 0, d2[ed] = 0;
    q1.push(st), q2.push(ed);
    int step = 0;
    while (!q1.empty() && !q2.empty()) {
        int ret = -1;
        if (q1.size() < q2.size()) ret = work(q1, d1, d2, va, vb);
        else ret = work(q2, d2, d1, vb, va);
        if (ret != -1) return ret;

        if (++step > 10) break;
    }

    return 11;
}

void solve() {
    int step = bfs();

    if (step > 10) cout << "NO ANSWER!" << "\n";
    else cout << step << "\n";
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
        cin >> st >> ed;
        while (cin >> va[tt] >> vb[tt]) tt++;
        solve();
    }

    return 0;
}