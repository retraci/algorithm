#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_set>

using namespace std;

struct Edge {
    int u, v, w;

    bool operator<(const Edge &that) const {
        return w < that.w;
    }
};

const int N = 2e5 + 10;

#define ull unsigned long long

int n, L, R, a[N];
ull seed;
vector<Edge> es;
int fa[N];

ull xor64() {
    ull x = seed;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return seed = x;
}

int gen() {
    return xor64() % (R - L + 1) + L;
}

void add(int u, int v, int w) {
    es.push_back({u, v, w});
}

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void work() {
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int w = __gcd(a[i], a[j]);
            add(i, j, w);
        }
    }

    for (int i = 1; i <= n; i++) fa[i] = i;
    sort(es.begin(), es.end());
    ull ans = 0;
    for (auto &[u, v, w]: es) {
        int tu = find(u), tv = find(v);
        if (tu == tv) continue;
        fa[tu] = tv;
        ans += w;
    }

    cout << ans << endl;
}

void solve() {
    if (n <= 1e3) {
        work();
    } else {
        if (L == R) cout << L * (n - 1);
        else cout << n - 1;
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n >> L >> R >> seed;
    unordered_set<int> st;
    for (int i = 1; i <= n; i++) {
        a[i] = gen();
        st.insert(a[i]);
    }
    cout << st.size() << endl;
    solve();

    return 0;
}