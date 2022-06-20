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

// region 01trie
template<int SZ>
struct Trie {
    int mxb;
    int ne[32 * SZ + 10][2], cnt[32 * SZ + 10], mem;

    Trie() {}

    void init(int _mxb) {
        mxb = _mxb;
        ne[0][0] = ne[0][1] = 0;
        cnt[0] = 0;
        mem = 0;
    }

    int new_node() {
        int id = ++mem;
        ne[id][0] = ne[id][1] = 0;
        cnt[id] = 0;
        return id;
    }

    void add(int x) {
        int u = 0;
        for (int i = mxb; i >= 0; i--) {
            int bit = x >> i & 1;
            int &v = ne[u][bit];
            if (!v) v = new_node();
            u = v;
        }

        cnt[u]++;
    }

    int qr_mx(int x) {
        int u = 0, res = 0;
        for (int i = mxb; i >= 0; i--) {
            int bit = x >> i & 1;
            if (ne[u][!bit]) {
                res += 1 << i;
                u = ne[u][!bit];
            } else {
                u = ne[u][bit];
            }
        }

        return res;
    }

    int qr_mi(int x) {
        int u = 0, res = 0;
        for (int i = mxb; i >= 0; i--) {
            int bit = x >> i & 1;
            if (ne[u][bit]) {
                u = ne[u][bit];
            } else {
                res += 1 << i;
                u = ne[u][!bit];
            }
        }

        return res;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1 << 18;

int L, R;
int a[N];
Trie<N> trie;

void solve() {
    trie.init(17);
    for (int i = L; i <= R; i++) trie.add(a[i]);

    for (int i = L; i <= R; i++) {
        int x = a[i] ^ L;

        if (trie.qr_mx(x) == R && trie.qr_mi(x) == L) {
            cout << x << "\n";
            return;
        }
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
        cin >> L >> R;
        for (int i = L; i <= R; i++) cin >> a[i];
        solve();
    }

    return 0;
}