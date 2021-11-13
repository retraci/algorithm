#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

const int N = 5e5 + 10;

int n;
int va[N];
ll f[N][3][3];

void solve() {
    for (int i = 1; i <= n; i++) {
        f[i][0][va[i]]++;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                int nj = (j + k * va[i + 1]) % 3;
                int nk = (k + va[i + 1]) % 3;
                f[i + 1][nj][nk] += f[i][j][k];
            }
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int k = 0; k < 3; k++) {
            ans += f[i][0][k];
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
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        va[i] = a % 3;
    }
    solve();

    return 0;
}