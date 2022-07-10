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

// region dsu
template<int SZ>
struct Dsu {
    int fa[SZ + 10];

    Dsu() {}

    void init(int _n) {
        iota(fa, fa + _n + 1, 0);
    }

    int find(int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }

    bool unite(int x, int y) {
        if (same(x, y)) return false;
        int tx = find(x), ty = find(y);
        fa[tx] = ty;
        return true;
    }

    bool same(int x, int y) {
        int tx = find(x), ty = find(y);
        return tx == ty;
    }
};
// endregion

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 2010;

int n;
int a[N];
Dsu<33> dsu;

inline int lowbit(int x) {
    return x & -x;
}

bool check() {
    dsu.init(30);
    int OR = 0;
    for (int i = 1; i <= n; i++) OR |= a[i];
    for (int i = 1; i <= n; i++) {
        int lst = -1;
        for (int k = 0; k <= 30; k++) {
            if (a[i] >> k & 1) {
                if (lst == -1) {
                    lst = k;
                    continue;
                }

                dsu.unite(k, lst);
            }
        }
    }

    int cnt = 0;
    for (int i = 0; i <= 30; i++) {
        if (OR >> i & 1) {
            cnt += dsu.find(i) == i;
        }
    }
    return cnt == 1;
}

void solve() {
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] == 0) {
            ans++;
            a[i]++;
        }
    }

    if (check()) {
        cout << ans << "\n";
        for (int k = 1; k <= n; k++) cout << a[k] << " \n"[k == n];
        return;
    }

    int mx = 0;
    for (int i = 1; i <= n; i++) {
        mx = max(mx, lowbit(a[i]));
    }

    ans++;
    for (int i = 1; i <= n; i++) {
        if (a[i] == 1) continue;
        if (lowbit(a[i]) == mx) {
            a[i]--;
            if (check()) {
                cout << ans << "\n";
                for (int k = 1; k <= n; k++) cout << a[k] << " \n"[k == n];
                return;
            }
            a[i]++;
        }
    }
    for (int i = 1; i <= n; i++) {
        a[i]++;
        if (check()) {
            cout << ans << "\n";
            for (int k = 1; k <= n; k++) cout << a[k] << " \n"[k == n];
            return;
        }
        a[i]--;
    }

    ans++;
    for (int i = 1; i <= n; i++) {
        if (a[i] == 1) continue;
        if (lowbit(a[i]) == mx) {
            a[i]--;
            break;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (lowbit(a[i]) == mx) {
            a[i]++;
            break;
        }
    }
    if (check()) {
        cout << ans << "\n";
        for (int k = 1; k <= n; k++) cout << a[k] << " \n"[k == n];
        return;
    }

    assert(false);
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