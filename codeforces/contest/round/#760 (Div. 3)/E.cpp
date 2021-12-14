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

const int N = 4e4 + 10;

ll n;
ll va[N];
ll ans[N];

void solve() {
    ll sum = 0;
    for (int i = 1; i <= n; i++) sum += va[i];
    if (sum % ((n + 1) * n / 2) != 0) {
        cout << "NO" << "\n";
        return;
    }
    sum /= (n + 1) * n / 2;

    ll tmp = sum - (va[1] - va[n]);
    if (tmp <= 0 || tmp % n != 0) {
        cout << "NO" << "\n";
        return;
    }
    ans[1] = tmp / n;
    for (int i = 2; i <= n; i++) {
        tmp = sum - (va[i] - va[i - 1]);
        if (tmp <= 0 || tmp % n != 0) {
            cout << "NO" << "\n";
            return;
        }
        ans[i] = tmp / n;
    }

    cout << "YES" << "\n";
    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << endl;
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}