#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

typedef pair<int, int> PII;

const int N = 33, M = 5010;

int n, m;
PII vv[N];
int f[N][M];
int s[N];
int ans[N];

void solve() {
    sort(vv + 1, vv + 1 + n, greater<PII>());

    for (int i = 1; i <= n; i++) {
        s[i] = s[i - 1] + vv[i].first;
    }

    memset(f, 0x3f, sizeof f);
    f[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= m; j++) {
            f[i][j] = f[i][j - i];
            for (int k = 1; k <= i; k++) {
                f[i][j] = min(f[i][j], f[i - k][j - k] + (s[i] - s[i - k]) * (i - k));
            }
        }
    }

    cout << f[n][m] << endl;

    int i = n, j = m, h = 0;
    while (i) {
        if (j - i >= 0 && f[i][j] == f[i][j - i]) {
            j -= i, h++;
        } else {
            for (int k = 1; k <= i && j >= k; k++) {
                if (f[i][j] == f[i - k][j - k] + (s[i] - s[i - k]) * (i - k)) {
                    int num = k;
                    while (num--) {
                        ans[vv[i].second] = 1 + h;
                        i--, j--;
                    }
                    break;
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> vv[i].first;
        vv[i].second = i;
    }
    solve();

    return 0;
}