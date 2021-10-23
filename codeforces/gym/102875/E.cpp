#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pii;

const int N = 16;

int n, m, K, lim;
vector<int> g[N];
int nex[1 << N];
int vis[1 << N];
pii path[1 << N];

inline void add(int u, int v) {
    g[u].push_back(v);
}

void init() {
    int lim = 1 << n;
    for (int mask = 1; mask < lim; mask++) {
        int ns = 0;
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) {
                for (int v: g[i]) {
                    ns |= 1 << v;
                }
            }
        }
        nex[mask] = ns;
    }
}

inline void pt(int s) {
    for (int i = 0; i < n; i++) {
        if (s >> i & 1) {
            char ch = i + 'a';
            cout << ch;
        }
    }
    cout << endl;
}

void back(int s) {
    if (s == lim - 1) return;
    auto &[ns, sub] = path[s];
    back(ns);
    pt(sub);
}

inline void print() {
    back(0);
}

void solve() {
    init();

    lim = 1 << n;
    queue<int> que;
    que.push(lim - 1);
    vis[lim - 1] = 1;
    int layer = 0;
    while (!que.empty()) {
        int len = que.size();
        if (++layer > 100) break;
        while (len--) {
            auto s = que.front();
            que.pop();

            int sum = __builtin_popcount(s);
            if (sum <= K) {
                cout << layer << endl;
                path[0] = {s, s};
                print();
                return;
            }

            for (int sub = s; sub > 0; sub = (sub - 1) & s) {
                if (__builtin_popcount(sub) > K) continue;
                int ns = s ^ sub;
                if (vis[nex[ns]]) continue;
                vis[nex[ns]] = 1;
                path[nex[ns]] = {s, sub};
                que.push(nex[ns]);
            }
        }
    }

    cout << -1 << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> m >> K;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        add(a, b), add(b, a);
    }
    solve();

    return 0;
}