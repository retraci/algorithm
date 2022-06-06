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

void solve() {
}

void prework() {
    int n = 6;
    int lim = 1 << n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n / 2; i++) a[i] = -1;
    for (int i = n / 2; i < n; i++) a[i] = 1;

    do {
        cout << "$" << "\n";
        for (int x: a) cout << x << " ";
        cout << "\n";
        cout << "#" << "\n";

        iota(b.begin(), b.end(), 1);
        do {
            vector<int> t(n);
            for (int i = 0; i < n; i++) {
                int id = b[i] - 1;
                t[i] = a[id];
            }
            for (int i = 1; i < n; i++) t[i] += t[i - 1];

            int ok = 0;
            for (int i = 0; i < n; i++) ok |= t[i] < 0;

            if (!ok) {
                for (int x: b) cout << x << " ";
                cout << "\n";
            }
        } while (next_permutation(b.begin(), b.end()));
    } while (next_permutation(a.begin(), a.end()));
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
        solve();
    }

    return 0;
}