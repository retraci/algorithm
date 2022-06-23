#include <bits/stdc++.h>

void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}

using namespace std;

#define fi first
#define se second
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(std::random_device{}());

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e6 + 10;

int n;
int a[N];
int vis[N];
vector<int> path;
int ans[N];

void dfs(int u) {
    if (vis[u]) return;
    vis[u] = 1;
    path.push_back(u);
    dfs(a[u]);
}

void work(const vector<int> &p) {
    for (int i = 0; i < p.size(); i++) {
        ans[p[i]] = p[(i + 1) % p.size()];
    }
}

void solve() {
    map<int, vector<vector<int>>> mp;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        path.clear();
        dfs(i);
        mp[path.size()].push_back(path);
    }

    for (int i = 1; i <= n; i++) {
        if (mp[i].empty()) continue;

        if (~i & 1 && mp[i].size() & 1) {
            cout << -1 << "\n";
            return;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (mp[i].empty()) continue;

        if (i & 1) {
            for (auto p : mp[i]) {
                vector<int> np(p.size());
                int pos = 0;
                for (int v : p) {
                    np[pos] = v;
                    pos = (pos + 2) % p.size();
                }
                work(np);
            }
        } else {
            int sz = mp[i].size();
            for (int j = 0; j < sz; j += 2) {
                vector<int> np(2 * mp[i][j].size());
                int pos = 0;
                for (int k = 0; k < mp[i][j].size(); k++) {
                    np[k * 2] = mp[i][j][k];
                    np[k * 2 + 1] = mp[i][j + 1][k];
                }
                work(np);
            }
        }
    }

    for (int i = 1; i <= n; i++) cout << ans[i] << " \n"[i == n];
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
    int _ = 1;
//    cin >> _;
    while (_--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}