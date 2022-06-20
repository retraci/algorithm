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
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e5 + 10;
const int S = 200;
const int B = S * 1e5;

int n;
int a[N];
int cnt[2 * S * N + N + 10];

void solve() {
    int ans = 1;
    for (int d = -S; d <= S; d++) {
        for (int i = 1; i <= n; i++) {
            int t = a[i] + i * d + B;
            ans = max(ans, ++cnt[t]);
        }
        for (int i = 1; i <= n; i++) {
            int t = a[i] + i * d + B;
            cnt[t] = 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        int lim = min(n, i + N / S - 1);
        for (int j = i + 1; j <= lim; j++) {
            int d = a[j] - a[i];
            if (d % (j - i)) continue;
            d = d / (j - i) + B;

            cnt[d]++;
            ans = max(ans, 1 + cnt[d]);
        }

        for (int j = i + 1; j <= lim; j++) {
            int d = a[j] - a[i];
            if (d % (j - i)) continue;
            d = d / (j - i) + B;

            cnt[d] = 0;
        }
    }

    cout << n - ans << "\n";
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
//    cin >> _;
    while (_--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}