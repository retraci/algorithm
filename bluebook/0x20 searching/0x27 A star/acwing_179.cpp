#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, string> pis;
typedef pair<string, char> psc;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const char op[4] = {'u', 'r', 'd', 'l'};
const string t = "12345678x";

string s;
unordered_map<string, int> dist;
unordered_map<string, int> vis;
unordered_map<string, psc> pre;

int get(string &str) {
    int res = 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == 'x') continue;
        int tar = str[i] - '1';
        int cx = abs(tar / 3 - i / 3), cy = abs(tar % 3 - i % 3);
        res += cx + cy;
    }

    return res;
}

string A_star() {
    dist = {}; vis = {}; pre = {};

    priority_queue<pis> que;
    dist[s] = 0;
    que.push({0, s});
    while (!que.empty()) {
        auto [w, u] = que.top(); que.pop();
        if (vis.count(u)) continue;
        if (u == t) break;
        vis[u] = 1;

        int x, y;
        for (int i = 0; i < u.size(); i++) {
            if (u[i] == 'x') x = i / 3, y = i % 3;
        }
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
                string v = u;
                swap(v[x * 3 + y], v[nx * 3 + ny]);

                if (!dist.count(v) || dist[v] > dist[u] + 1) {
                    dist[v] = dist[u] + 1;
                    pre[v] = {u, op[k]};

                    int f = dist[v] + get(v);
                    que.push({-f, v});
                }
            }
        }
    }

    string res = "";
    string ed = t;
    while (ed != s) {
        auto [p, o] = pre[ed];
        res += o;
        ed = p;
    }
    reverse(res.begin(), res.end());
    return res;
}

void solve() {
    int cnt = 0;
    for (int i = 0; i < s.size(); i++) {
        for (int j = i + 1; j < s.size(); j++) {
            if (s[i] == 'x' || s[j] == 'x') continue;
            if (s[i] > s[j]) cnt++;
        }
    }

    if (cnt & 1) {
        cout << "unsolvable" << "\n";
        return;
    }

    cout << A_star() << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    for (int i = 1; i <= 9; i++) {
        string inp;
        cin >> inp;
        s += inp;
    }
    solve();

    return 0;
}