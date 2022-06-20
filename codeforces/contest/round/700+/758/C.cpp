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
#include <ctime>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {0, 0, -1, 1, -1, -1, 1, 1, 0};
const int dy[9] = {-1, 1, 0, 0, -1, 1, -1, 1, 0};

const int N = 1e5 + 10;

int n;
int va[N], vb[N];
int idx1[N], idx2[N];
int ridx1[N], ridx2[N];

int fa[N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void init() {
    for (int i = 1; i <= n; i++) idx1[i] = idx2[i] = i;
    sort(idx1 + 1, idx1 + n + 1, [&](auto &a, auto &b) {
        return va[a] < va[b];
    });
    for (int i = 1; i <= n; i++) ridx1[idx1[i]] = i;
    sort(idx2 + 1, idx2 + n + 1, [&](auto &a, auto &b) {
        return vb[a] < vb[b];
    });
    for (int i = 1; i <= n; i++) ridx2[idx2[i]] = i;

    for (int i = 1; i <= n; i++) fa[i] = i;
}

void solve() {
    init();

    int mx1 = idx1[n], mx2 = idx2[n];
    queue<int> que;
    que.push(mx1), que.push(mx2);
    int p1 = n + 1, p2 = n + 1;
    while (!que.empty()) {
        auto u = que.front(); que.pop();

        int np1 = min(p1, ridx1[u]), np2 = min(p2, ridx2[u]);
        for (int i = np1; i < p1; i++) {
            int v = idx1[i];
            int fx = find(u), fy = find(v);
            fa[fy] = fx;

            que.push(v);
        }
        for (int i = np2; i < p2; i++) {
            int v = idx2[i];
            int fx = find(u), fy = find(v);
            fa[fy] = fx;

            que.push(v);
        }

        p1 = np1, p2 = np2;
    }

    string ans = string(n, '0');
    for (int i = 1; i <= n; i++) {
        int fx1 = find(mx1), fx2 = find(mx2);
        int fy = find(i);
        if (fy == fx1 || fy == fx2) ans[i - 1] = '1';
    }
    cout << ans << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    srand(time(0));
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> va[i];
        for (int i = 1; i <= n; i++) cin >> vb[i];
        solve();
    }

    return 0;
}