#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 1010;

int n, m;
char g[N][N];
int s[N][N];
int lb[N], rb[N];

int work(int r) {
    int *va = s[r];

    {
        va[0] = -1;
        stack<int> stk;
        stk.push(0);
        for (int j = 1; j <= m; j++) {
            while (va[j] <= va[stk.top()]) stk.pop();
            lb[j] = stk.top() + 1;
            stk.push(j);
        }
    }

    {
        va[m + 1] = -1;
        stack<int> stk;
        stk.push(m + 1);
        for (int j = m; j >= 1; j--) {
            while (va[j] <= va[stk.top()]) stk.pop();
            rb[j] = stk.top() - 1;
            stk.push(j);
        }
    }

    int res = 0;
    for (int j = 1; j <= m; j++) res = max(res, va[j] * (rb[j] - lb[j] + 1));
    return res;
}

void solve() {
    for (int j = 1; j <= m; j++) {
        for (int i = 1; i <= n; i++) {
            if (g[i][j] == 'F') s[i][j] = s[i - 1][j] + 1;
            else s[i][j] = 0;
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) ans = max(ans, 3 * work(i));
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> g[i][j];
        }
    }
    solve();

    return 0;
}