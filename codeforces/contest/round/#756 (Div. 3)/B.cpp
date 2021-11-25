#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int a, b;

void solve() {
    if (a > b) swap(a, b);

    int r1 = min(a / 2, b / 2);
    int ans = r1;
    a -= 2 * r1, b -= 2 * r1;
    if (a == 1 && b >= 3) {
        a--, b -= 3;
        ans++;
    }

    int r2 = min(r1, b / 4);
    ans += r2;
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> a >> b;
        solve();
    }

    return 0;
}