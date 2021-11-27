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
    for (int i = 1; i <= n; i++) cnt[va[i]]++;

    int lim = *max_element(va + 1, va + n + 1);
    for (int i = 1; i <= lim; i++) {
        for (int j = 2 * i; j <= lim; j += i) {
            cnt[i] += cnt[j];
        }
    }

    f[1] = n;
    for (int i = 1; i <= lim; i++) {
        for (int j = 2 * i; j <= lim; j += i) {
            f[j] = max(f[j], f[i] + (j - i) * cnt[j]);
        }
    }
    cout << *max_element(f + 1, f + lim + 1) << endl;
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