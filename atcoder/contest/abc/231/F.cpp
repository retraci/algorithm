#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {0, 0, -1, 1, -1, -1, 1, 1, 0};
const int dy[9] = {-1, 1, 0, 0, -1, 1, -1, 1, 0};

namespace Seg {
#define mid (left + right >> 1)
#define lson (node << 1)
#define rson ((node << 1) + 1)

    const int SZ = 4e5;

    struct Node {
        int left, right;
        ll sum, lz;
    };

    Node tree[SZ * 4];
    vector<ll> lsh;

    inline int get_id(ll x) {
        return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin() + 1;
    }

    inline void push_up(int node) {
        tree[node].sum = tree[lson].sum + tree[rson].sum;
    }

    inline void push_down(int node) {
        if (tree[node].lz) {
            tree[lson].sum = tree[lson].sum + tree[node].lz;
            tree[rson].sum = tree[rson].sum + tree[node].lz;
            tree[lson].lz = tree[lson].lz + tree[node].lz;
            tree[rson].lz = tree[rson].lz + tree[node].lz;
            tree[node].lz = 0;
        }
    }

    void build(int node, int left, int right) {
        tree[node].left = left, tree[node].right = right;
        tree[node].sum = tree[node].lz = 0;

        if (left == right) return;
        build(lson, left, mid);
        build(rson, mid + 1, right);
    }

    void update(int node, int L, int R, ll val) {
        int left = tree[node].left, right = tree[node].right;

        if (right < L || left > R) return;
        if (L <= left && right <= R) {
            tree[node].sum = tree[node].sum + val;
            tree[node].lz = tree[node].lz + val;
            return;
        }

        push_down(node);
        update(lson, L, R, val);
        update(rson, L, R, val);
        push_up(node);
    }

    ll query(int node, int L, int R) {
        int left = tree[node].left, right = tree[node].right;

        if (right < L || left > R) return 0;
        if (L <= left && right <= R) return tree[node].sum;

        push_down(node);
        return query(lson, L, R) + query(rson, L, R);
    }
}
using namespace Seg;

const int N = 2e5 + 10;

ll n;
ll va[N], vb[N];
int idx1[N], idx2[N];

int tt;

void init() {
    for (int i = 1; i <= n; i++) lsh.push_back(va[i]), lsh.push_back(vb[i]);
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    tt = lsh.size();

    build(1, 1, tt);

    for (int i = 1; i <= n; i++) idx1[i] = idx2[i] = i;
    sort(idx1 + 1, idx1 + n + 1, [&](auto &a, auto &b) {
        return va[a] < va[b];
    });
    sort(idx2 + 1, idx2 + n + 1, [&](auto &a, auto &b) {
        return vb[a] < vb[b];
    });
}

void solve() {
    init();

    ll ans = n * n;
    for (int i = n; i >= 1; i--) {
        int j = i;
        int idi = idx1[i], idj = idx1[j];
        while (j >= 1 && va[idi] == va[idj]) {
            ans -= n - i;
            idj = idx1[--j];
        }
        i = j + 1;
    }
    for (int i = n; i >= 1; i--) {
        int j = i;
        int idi = idx2[i], idj = idx2[j];
        while (j >= 1 && vb[idi] == vb[idj]) {
            ans -= n - i;
            idj = idx2[--j];
        }
        i = j + 1;
    }

    for (int i = n; i >= 1; i--) {
        int j = i;
        int idi = idx1[i], idj = idx1[j];
        while (j >= 1 && va[idi] == va[idj]) {
            ans += query(1, 1, get_id(vb[idj]) - 1);
            idj = idx1[--j];
        }
        
        for (int k = j + 1; k <= i; k++) {
            int id = idx1[k], x = get_id(vb[id]);
            update(1, x, x, 1);
        }
        
        i = j + 1;
    }

    cout << ans << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> va[i];
    for (int i = 1; i <= n; i++) cin >> vb[i];
    solve();

    return 0;
}