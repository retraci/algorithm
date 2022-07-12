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
const int N = 3e5 + 10;

int n, q, mod;
int a[N], b[N];
int c[N], d[N];
int fib[N];
int cnt;

void upd(int arr[], int i, int x) {
    if (i >= 1 && i <= n) {
        cnt -= c[i] == d[i];

        arr[i] += x;
        arr[i] = (arr[i] % mod + mod) % mod;

        cnt += c[i] == d[i];
    }
}

void solve() {
    fib[1] = fib[2] = 1;
    for (int i = 3; i <= n + 1; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
        fib[i] %= mod;
    }

    c[1] = a[1], d[1] = b[1];
    for (int i = 2; i <= n; i++) {
        ll t1 = 1LL * a[i] - a[i - 1] - a[i - 2];
        c[i] = (t1 % mod + mod) % mod;
        ll t2 = 1LL * b[i] - b[i - 1] - b[i - 2];
        d[i] = (t2 % mod + mod) % mod;
    }

    for (int i = 1; i <= n; i++) cnt += c[i] == d[i];

    while (q--) {
        string op;
        int L, R;
        cin >> op >> L >> R;

        if (op[0] == 'A') {
            upd(c, L, 1);
            upd(c, R + 1, -fib[R - L + 2]);
            upd(c, R + 2, -fib[R - L + 1]);
        } else {
            upd(d, L, 1);
            upd(d, R + 1, -fib[R - L + 2]);
            upd(d, R + 2, -fib[R - L + 1]);
        }

        cout << (cnt == n ? "YES" : "NO") << "\n";
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
        cin >> n >> q >> mod;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        solve();
    }

    return 0;
}