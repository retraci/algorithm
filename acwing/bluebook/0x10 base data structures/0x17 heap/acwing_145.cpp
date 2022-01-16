#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 10010;

int n;
int vp[N], vd[N], idx[N];
int fa[N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void solve() {
    for (int i = 1; i <= n; i++) idx[i] = i;
    sort(idx + 1, idx + n + 1, [&](auto &a, auto &b) {
        return vp[a] > vp[b];
    });

    int md = *max_element(vd + 1, vd + n + 1);
    for (int i = 0; i <= md; i++) fa[i] = i;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int id = idx[i];
        int tx = find(vd[id]);
        if (tx > 0) {
            ans += vp[id];

            fa[tx] = tx - 1;
        }
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    while (cin >> n) {
        for (int i = 1; i <= n; i++) cin >> vp[i] >> vd[i];
        solve();
    }

    return 0;
}