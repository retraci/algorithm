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

const int N = 55;
const int M = 1 << 23;

ll n, w;
ll va[N];
ll vw[M], tt;
ll ans;

ll get(ll x) {
    int left = 0, right = tt - 1;
    while (left < right) {
        int mid = left + right + 1 >> 1;
        if (vw[mid] <= x) left = mid;
        else right = mid - 1;
    }

    return vw[left];
}

void dfs2(int u, ll s) {
    if (u > n) {
        ans = max(ans, get(w - s) + s);
        return;
    }

    dfs2(u + 1, s);
    if (s + va[u] <= w) dfs2(u + 1, s + va[u]);
}

void dfs1(int u, ll s) {
    if (u >= n / 2) {
        vw[tt++] = s;
        return;
    }

    dfs1(u + 1, s);
    if (s + va[u] <= w) dfs1(u + 1, s + va[u]);
}

void solve() {
    sort(va, va + n, greater<>());

    dfs1(0, 0);
    sort(vw, vw + tt);
    tt = unique(vw, vw + tt) - vw;

    ans = 0;
    dfs2(n / 2, 0);
    cout << ans << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> w >> n;
    for (int i = 0; i < n; i++) cin >> va[i];
    solve();

    return 0;
}