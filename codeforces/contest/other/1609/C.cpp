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

int n, e;
int va[N];
int vis[N];

void primes(int n) {
    memset(vis, 0, sizeof vis);
    vis[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (vis[i]) continue;
        for (int j = i; j <= n / i; j++) vis[i * j] = 1;
    }
}

void init() {
    primes(1e6);
}

void solve() {
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[va[i]]) {
            ll c1, c2;

            {
                int j = i - e;
                while (j >= 1 && va[j] == 1) j -= e;
                c1 = (i - j) / e - 1;
            }

            {
                int j = i + e;
                while (j <= n && va[j] == 1) j += e;
                c2 = (j - i) / e - 1;
            }

//            cout << i << endl;
//            cout << c1 << " " << c2 << endl;

            ans += c1 + c2;
            ans += c1 * c2;
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
    init();
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> e;
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}