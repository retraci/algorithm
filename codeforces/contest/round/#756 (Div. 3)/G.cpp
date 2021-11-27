#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 1e6 + 10;

int n, m;
string str[N];
int f[N];

int get_id(int x, int y) {
    return (x - 1) * m + y - 1;
}

void solve() {
    if (n == 1) {
        int ans = 0;
        for (int j = 1; j <= m; j++) ans += str[1][j - 1] == '1';
        cout << ans << endl;
        return;
    }

    for (int j = 1; j <= m; j++) {
        for (int i = 1; i <= n; i++) {
            int id = get_id(i, j);
            int x = str[i][j - 1] == '1';

            f[id] = x;
            if (j - 2 >= 1) {
                int from = get_id(i, j - 2);
                f[id] += max(f[id], f[from] + x);
            }
            if (j - 1 >= 1 && i - 1 >= 1) {
                int from = get_id(i - 1, j - 1);
                f[id] = max(f[id], f[from]);
            }
            if (j - 1 >= 1 && i + 1 <= n) {
                int from = get_id(i + 1, j - 1);
                f[id] = max(f[id], f[from]);
            }
        }
    }

    int mx0 = 0, mx1 = 0;
    for (int i = 1; i <= n; i++) {
        if ((i + m) & 1) mx1 = max(mx1, f[get_id(i, m)]);
        else mx0 = max(mx0, f[get_id(i, m)]);
    }
    cout << mx0 + mx1 << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T; cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> str[i];
        solve();
    }

    return 0;
}