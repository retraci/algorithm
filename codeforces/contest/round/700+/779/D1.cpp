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
const int N = 1 << 18;

int L, R;
int a[N];

void solve() {
    vector<int> c(21);
    for (int i = L; i <= R; i++) {
        for (int bit = 0; bit <= 18; bit++) {
            c[bit] += a[i] >> bit & 1;
        }
    }

    int ans = 0;
    for (int bit = 0; bit <= 18; bit++) {
        if (c[bit] > (R - L + 1) / 2) ans |= 1 << bit;
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
    cin >> _;
    while (_--) {
        cin >> L >> R;
        for (int i = L; i <= R; i++) cin >> a[i];
        solve();
    }

    return 0;
}