#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int N = 2030;

int n;
int va[N], vb[N];
int idb[N];
int vis[N];
int ok, cnt;
vector<int> path, vc;
vector<vector<int>> cs;

void dfs(int u, int c) {
    vis[u] = 1;
    path.push_back(u);
    int x = va[u];
    int v = idb[x];
    if (v > u && va[v] > va[u] || v < u && va[v] < va[u]) {
        if (++c >= 2) ok = 0;
    }
    if (vis[v]) return;
    dfs(v, c);
}

void solve() {
    for (int i = 1; i <= n; i++) idb[vb[i]] = i;
    for (int i = 1; i <= n; i++) vis[i] = 0;
    cs = {};
    ok = 1, cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (!ok) break;
        if (!vis[i]) {
            path = {};
            dfs(i, 0);
            cs.push_back(path);
        }
    }

    vc = {};
    for(int i = 1; i <=n;i ++) vc.emplace_back(va[i]);

    if (!ok) {
        cout << -1 << endl;
    } else {
        int ans = 0;
        for (auto &vk : cs) ans += max(0, (int) vk.size() - 1);
        cout << ans << endl;

        for (auto &vk : cs) {
            int tt = 0, need = vk.size() - 1;

            vk.push_back(vk.front());
            for (int i = 0; i < vk.size() - 1; i++) {

                int j = i + 1;
                for (; j < vk.size(); j++) {
                    int id1 = vk[i], id2 = vk[j];
                    if (id1 > id2) swap(id1, id2);

                    int v1 = va[id1], v2 = va[id2];
                    if (id1 < id2 && v1 < v2 || id1 > id2 && v1 > v2) break;
                    if (++tt > need) break;
                    cout << id1 << " " << id2 << endl;
                    swap(vc[id1 - 1], vc[id2 - 1]);
                }
                i = j - 1;
            }
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> va[i];
        for (int i = 1; i <= n; i++) cin >> vb[i];
        solve();

        cout << '#';
        for(int v : vc)  cout << v << " ";
        cout << "\n";
    }

    return 0;
}