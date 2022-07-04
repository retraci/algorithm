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
mt19937 mrnd(std::random_device{}());

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 2e5 + 10;

int n, q;
int a[N];

void solve() {
    ll cur = accumulate(a + 1, a + n + 1, 0LL);
    vector<int> lst(n + 1);

    for (int k = 1; k <= q; k++) {
        int op;
        cin >> op;

        if (op == 1) {
            int i, x;
            cin >> i >> x;

            int p = lst[0] > lst[i] ? a[0] : a[i];
            a[i] = x, cur += x - p;
            lst[i] = k;

            cout << cur << "\n";
        } else {
            int x;
            cin >> x;

            a[0] = x, cur = 1LL * x * n;
            lst[0] = k;

            cout << cur << "\n";
        }
    }
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
        cin >> n >> q;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}