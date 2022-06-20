#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 1e5 + 10;
const int M = 5e6 + 10;

int n;
int va[N];
ll cnt[M];
ll f[M];

void solve() {
    int lim = *max_element(va + 1, va + n + 1);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j * j <= va[i]; j++) {
            if (va[i] % j) continue;
            cnt[j]++; cnt[va[i] / j]++;
            if (j * j == va[i]) cnt[j]--;
        }
    }

    for (int i = lim; i >= 1; i--) {
        f[i] = i * cnt[i];
        for (int j = 2 * i; j <= lim; j += i) {
            f[i] = max(f[i], f[j] + (cnt[i] - cnt[j]) * i);
        }
    }

    cout << f[1] << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> va[i];
    solve();

    return 0;
}