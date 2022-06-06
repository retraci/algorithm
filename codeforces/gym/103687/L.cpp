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

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e6 + 10;

int n;
int a[N];
ll s[N];

bool check(int md, int i) {
    ld avg = 1.0 * s[md] / md;
    return avg < a[i + 1];
}

void solve() {
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];

    int ans = 0;
    for (int i = 1; i <= n - 1; i++) {
        int left = i, right = n;
        while (left < right) {
            int md = left + right + 1 >> 1;
            if (check(md, i)) left = md;
            else right = md - 1;
        }
        ans = max(ans, left - i);
    }

    cout << ans << "\n";
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