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

const int N = 1e5 + 10;

int n, m;
int va[N], vb[N];

int du[N];
int fa[N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void solve() {
    for (int i = 1; i <= m; i++) {
        int u = va[i], v = vb[i];
        du[u]++, du[v]++;
    }

    int flag = 0;
    for (int i = 1; i <= n; i++) flag |= du[i] > 2;
    if (flag) {
        cout << "No" << "\n";
        return;
    }

    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1; i <= m; i++) {
        int u = va[i], v = vb[i];
        int tx = find(u), ty = find(v);
        if (tx == ty) flag = 1;
        fa[tx] = ty;
    }

    if (!flag) cout << "Yes" << "\n";
    else cout << "No" << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> va[i] >> vb[i];
    solve();

    return 0;
}