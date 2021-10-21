#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> PII;

const int N = 2e5 + 10;

int n;
int in[N];
vector<int> g[N];
int ts[N];
int tt, ans;

void add_edge(int a, int b) {
    g[a].push_back(b); in[b]++;
}

void solve() {
    for (int i = 1; i <= n; i++) ts[i] = 1;
    queue<PII> que;
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0) que.push({i, 1});
    }

    ans = 0, tt = 0;
    while (!que.empty()) {
        auto [idx, time] = que.front(); que.pop();
        tt++; ans = max(ans, time);

        for (auto &to: g[idx]) {
            if (to < idx) ts[to] = max(ts[to], time + 1);
            else ts[to] = max(ts[to], time);

            if (--in[to] <= 0) que.push({to, ts[to]});
        }
    }

    if (tt < n) {
        cout << -1 << endl;
        return;
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i <= n; i++) g[i].clear();
        for (int i = 0; i <= n; i++) in[i] = 0;

        for (int i = 1; i <= n; i++) {
            int k;
            cin >> k;
            while (k--) {
                int pre;
                cin >> pre;
                add_edge(pre, i);
            }
        }

        solve();
    }

    return 0;
}