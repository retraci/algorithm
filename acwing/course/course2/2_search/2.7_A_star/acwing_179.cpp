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

typedef pair<string, char> psc;
typedef pair<int, string> pis;

const string op = "urdl";

string st;
unordered_map<string, int> dist;
unordered_map<string, int> vis;
unordered_map<string, psc> pre;

int get(string &str) {
    int res = 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == 'x') continue;
        int tar = str[i] - '1';
        int dx = abs(tar / 3 - i / 3), dy = abs(tar % 3 - i % 3);
        res += dx + dy;
    }

    return res;
}

string a_star() {
    string ed = "12345678x";

    priority_queue<pis> que;
    dist[st] = 0;
    que.push({0, st});
    while (!que.empty()) {
        auto [f, u] = que.top(); que.pop();
        if (vis.count(u)) continue;
        vis[u] = 1;
        if (u == ed) break;

        int x, y;
        for (int i = 0; i < u.size(); i++) {
            if (u[i] == 'x') x = i / 3, y = i % 3;
        }
        for (int k = 0; k < 4; k++) {
            int nx = x + dir[k][0], ny = y + dir[k][1];
            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
                string v = u;
                swap(v[x * 3 + y], v[nx * 3 + ny]);

                if (!dist.count(v) || dist[v] > dist[u] + 1) {
                    dist[v] = dist[u] + 1;
                    pre[v] = {u, op[k]};

                    int nf = dist[v] + get(v);
                    que.push({-nf, v});
                }
            }
        }
    }

    string res = "";
    while (ed != st) {
        auto &[p, o] = pre[ed];
        res += o;
        ed = p;
    }
    reverse(res.begin(), res.end());
    return res;
}

void solve() {
    int cnt = 0;
    for (int i = 0; i < st.size(); i++) {
        for (int j = i + 1; j < st.size(); j++) {
            if (st[i] == 'x' || st[j] == 'x') continue;
            if (st[i] > st[j]) cnt++;
        }
    }

    if (cnt & 1) {
        cout << "unsolvable" << "\n";
        return;
    }

    cout << a_star() << "\n";
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
        for (int i = 1; i <= 9; i++) {
            string str;
            cin >> str;
            st += str;
        }
        solve();
    }

    return 0;
}