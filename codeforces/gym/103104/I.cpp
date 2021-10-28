#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>

using namespace std;

#define ll long long

const int N = 5010;

int n, m;
ll a[N][N];
ll hs[N][N], cnt[N];


void solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j]) hs[i][j] = 0;
            else hs[i][j] = hs[i - 1][j] + 1;
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        stack<int> stk;
        memset(cnt, 0, (n + 1) * sizeof *cnt);
        ll *h = hs[i];

        for (int j = 1; j <= n; j++) {
            while (!stk.empty() && h[j] <= h[stk.top()]) stk.pop();

            int lb = stk.empty() ? 0 : stk.top();
            cnt[j] = h[j] * (j - lb) + cnt[lb];
            ans += cnt[j];

            stk.push(j);
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
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        a[x][y] = 1;
    }
    solve();

    return 0;
}