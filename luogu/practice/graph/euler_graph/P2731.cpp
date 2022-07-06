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

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {0, 0, -1, 1, -1, -1, 1, 1, 0};
const int dy[9] = {-1, 1, 0, 0, -1, 1, -1, 1, 0};

const int N = 510;

int m;
set<int> g[N];
int du[N];
vector<int> ans;
map<pii, int> cnt;

void add(int u, int v) {
    g[u].insert(v);
    cnt[{u, v}]++;
    du[v]++;
}

void dfs(int u) {
    for (auto v : g[u]) {
        if (cnt[{u, v}]) {
            cnt[{u, v}]--, cnt[{v, u}]--;
            dfs(v);
        }
    }
    ans.push_back(u);
}

void solve() {
    int s = 0;
    for (int i = 1; i < N; i++) {
        if (du[i] & 1) {
            s = i;
            break;
        }
    }
    if (s == 0) s = 1;

    dfs(s);
    reverse(ans.begin(), ans.end());
    for (int x : ans) cout << x << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        add(u, v), add(v, u);
    }
    solve();

    return 0;
}