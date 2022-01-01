#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <bitset>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 1e5 + 10;

int n;
vector<int> g[N];
ll c1, c2;

void dfs(int u, int fno, int dep) {
    if (dep & 1) c1++;
    else c2++;

    for (int v : g[u]) {
        if (v == fno) continue;
        dfs(v, u, dep + 1);
    }
}

void add(int u, int v) {
    g[u].push_back(v);
}

void solve() {
    dfs(1, 0, 1);
    cout << c1 * c2 - (n - 1) << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v), add(v, u);
    }
    solve();

    return 0;
}