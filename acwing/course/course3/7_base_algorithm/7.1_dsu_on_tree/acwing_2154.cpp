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

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 100010;
const int M = 1e6 + 10;

int n, q;
int a[N];
int mp[M];
int cur;
vector<int> b[M];

void merge(int &x, int &y) {
    if (x == y) return;
    if (b[x].size() > b[y].size()) swap(x, y);

    for (int z : b[x]) {
        cur -= a[z - 1] == y;
        cur -= a[z + 1] == y;
    }

    for (int z : b[x]) {
        a[z] = y;
        b[y].push_back(z);
    }
    b[x].clear();
}

void solve() {
    for (int i = 1; i <= n; i++) b[a[i]].push_back(i);
    iota(mp, mp + (int) 1e6 + 1, 0);
    cur = 1;
    for (int i = 2; i <= n; i++) {
        cur += a[i] != a[i - 1];
    }

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int x, y;
            cin >> x >> y;

            merge(mp[x], mp[y]);
        } else {
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