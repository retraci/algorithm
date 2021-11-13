#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <queue>

using namespace std;

#define ull unsigned long long

const int n = 6;
const ull p = 1e9 + 17;

struct Node {
    int g[n][n];
    int step;
};

int s[n][n];
unordered_map<ull, bool> mp;

ull get(Node &cur) {
    ull res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res = res * p + cur.g[i][j];
        }
    }

    return res;
}

void print(Node &cur) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << cur.g[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void solve() {
    queue<Node> que;
    Node st;
    memcpy(st.g, s, sizeof s);
    st.step = 0;
    que.push(st);

    int len = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            len += s[i][j] == 1;

    int ans = 15;
    while (!que.empty()) {
        Node cur = que.front();
        que.pop();
        if (cur.g[2][5] == 1) {
            ans = cur.step + len;
//            print(cur);
            break;
        }
        mp[get(cur)] = 1;

        Node ns;
        ns.step = cur.step + 1;
        if (ns.step + len > 10) continue;
        int vis[11] = {0};
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                auto &[g, step] = cur;
                int cell = g[i][j];
                if (cell == 0 || vis[cell]) continue;
                vis[cell] = 1;

                int dir = -1;
                // 1: 竖着走
                if (i - 1 >= 0 && cell == g[i - 1][j]) dir = 1;
                if (i + 1 < n && cell == g[i + 1][j]) dir = 1;
                if (j - 1 >= 0 && cell == g[i][j - 1]) dir = 0;
                if (j + 1 < n && cell == g[i][j + 1]) dir = 0;

//                cout << '#' << " " << cell << " " << dir << endl;
//                print(cur);

                // 找车尾
                if (dir) {
                    int ni = i;
                    while (ni < n && g[ni][j] == cell) ni++;
                    ni--;

                    memcpy(ns.g, g, sizeof g);
                    // 向前走
                    int v1 = i, v2 = ni;
                    if (v1 - 1 >= 0 && g[v1 - 1][j] == 0) {
                        ns.g[v1 - 1][j] = cell, ns.g[v2][j] = 0;
                        if (!mp.count(get(ns))) {
//                                print(ns);
                            que.push(ns);
                        }
                    }

                    memcpy(ns.g, g, sizeof g);
                    // 向后走
                    v1 = i, v2 = ni;
                    if (v2 + 1 < n && g[v2 + 1][j] == 0) {
                        ns.g[v2 + 1][j] = cell, ns.g[v1][j] = 0;
                        if (!mp.count(get(ns))) {
//                                print(ns);
                            que.push(ns);
                        }
                    }
                } else {
                    int nj = j;
                    while (nj < n && g[i][nj] == cell) nj++;
                    nj--;

                    memcpy(ns.g, g, sizeof g);
                    // 向前走
                    int v1 = j, v2 = nj;
                    if (v1 - 1 >= 0 && g[i][v1 - 1] == 0) {
                        ns.g[i][v1 - 1] = cell, ns.g[i][v2] = 0;
                        if (!mp.count(get(ns))) {
//                                print(ns);
                            que.push(ns);
                        }
                    }

                    memcpy(ns.g, g, sizeof g);
                    // 向后走
                    v1 = j, v2 = nj;
                    if (v2 + 1 < n && g[i][v2 + 1] == 0) {
                        ns.g[i][v2 + 1] = cell, ns.g[i][v1] = 0;
                        if (!mp.count(get(ns))) {
//                                print(ns);
                            que.push(ns);
                        }
                    }
                }
            }
        }
    }

    cout << (ans == 15 ? -1 : ans) << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> s[i][j];
        }
    }
    solve();

    return 0;
}