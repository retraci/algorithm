#include <bits/stdc++.h>

using namespace std;

const int N = 20;

int n, w;
int va[N];
int ans;
int cab[N];

void dfs(int x, int cur) {
    if (cur > ans) return;
    if (x == n) {
        ans = min(ans, cur);
        return;
    }

    for (int i = 1; i <= cur; i++) {
        if (cab[i] + va[x] <= w) {
            cab[i] += va[x];
            dfs(x + 1, cur);
            cab[i] -= va[x];
        }
    }

    cab[cur + 1] = va[x];
    dfs(x + 1, cur + 1);
    cab[cur + 1] = 0;
}

void solve() {
    sort(va, va + n, greater<int>());
    ans = n;
    dfs(0, 0);

    cout << ans << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);
    std::ios::sync_with_stdio(false);

    cin >> n >> w;
    for (int i = 0; i < n; i++) cin >> va[i];
    solve();

    return 0;
}