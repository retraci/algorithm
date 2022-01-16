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

const int N = 110;

int n;
int path[N];
int vis[N];

bool dfs(int u, int dep) {
    if (u > dep) return path[u - 1] == n;

    for (int i = u - 1; i >= 1; i--) {
        for (int j = i; j >= 1; j--) {
            int s = path[i] + path[j];
            if (s >= path[u - 1] && s <= n && !vis[s]) {
                vis[s] = 1;
                path[u] = s;
                if (dfs(u + 1, dep)) return true;
                vis[s] = 0;
            }
        }
    }

    return false;
}

void solve() {
    memset(vis, 0, sizeof vis);

    int dep = 1;
    path[1] = 1;
    while (!dfs(2, dep)) dep++;

    for (int i = 1; i <= dep; i++) cout << path[i] << " ";
    cout << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    while (cin >> n, n) {
        solve();
    }

    return 0;
}