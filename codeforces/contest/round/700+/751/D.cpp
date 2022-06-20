#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <set>

using namespace std;

typedef pair<int, int> pii;

const int N = 300010;

int n;
int va[N], vb[N];
int vis[N];
pii fa[N];

void pt(int u) {
    if (u == n) return;
    auto [f, _] = fa[u];
    pt(f);
    cout << _ << " ";
}

void print() {
    pt(0);
}

void solve() {
    set<int> st;
    for (int i = 0; i <= n; i++) st.insert(i);

    int layer = 0;
    memset(vis, 0, sizeof vis);
    queue<int> que;
    que.push(n);
    vis[n] = 1;
    st.erase(n);
    while (!que.empty()) {
        int sz = que.size();
        layer++;
        while (sz--) {
            int u = que.front(); que.pop();

            int mx = va[u];
            auto it = st.lower_bound(u - mx);
            while (it != st.end()) {
                int v = *it;
                it = st.erase(it);

                // 如果到了终点
                if (v <= 0) {
                    cout << layer << endl;
                    fa[0] = {u, v};
                    print();
                    return;
                }
                int nv = v + vb[v];

                if (!vis[nv]) {
                    vis[nv] = 1;
                    fa[nv] = {u, v};
                    que.push(nv);
                }
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
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> va[i];
    for (int i = 1; i <= n; i++) cin >> vb[i];
    solve();

    return 0;
}