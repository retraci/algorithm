#include <bits/stdc++.h>

void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}

using namespace std;

#define fi first
#define se second
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 2e5 + 10;

int n;
int a[N];

void solve() {
    int L = 1, R = 0, mx = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] == 0) continue;
        int j = i;
        while (j <= n && a[j] != 0) j++;

        int sgn = 0, cur = 0;
        pii mi[2] = {{0, i - 1}, {n, -1}};
        for (int k = i; k < j; k++) {
            sgn ^= a[k] < 0;
            cur += abs(a[k]) == 2;
            if (mx < cur - mi[sgn].fi) {
                mx = cur - mi[sgn].fi;
                L = mi[sgn].se + 1, R = k;
            }
            mi[sgn] = min(mi[sgn], {cur, k});
        }

        i = j - 1;
    }

    cout << L - 1 << " " << n - R << "\n";
}

void prework() {
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    prework();
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
    cin >> _;
    while (_--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}