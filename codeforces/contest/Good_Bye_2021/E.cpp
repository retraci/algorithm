#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <bitset>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 1e5 + 10;

int n;
string s, t;

// 普通线段树
namespace Seg {
#define mid (left + right >> 1)
#define lson (node << 1)
#define rson ((node << 1) + 1)

    const int SZ = 1e5;

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
        ll lsz = tree[lson].right - tree[lson].left + 1;
        ll rsz = tree[rson].right - tree[rson].left + 1;
        if (tree[node].lz) {
            tree[lson].sum = tree[lson].sum + lsz * tree[node].lz;
            tree[rson].sum = tree[rson].sum + rsz * tree[node].lz;
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
            tree[node].sum = tree[node].sum + (R - L + 1) * val;
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

void solve() {
    vector<int> va[26];
    for (int i = n; i >= 1; i--) va[s[i] - 'a'].push_back(i);
    build(1, 1, n);
    update(1, 1, n, 1);

    ll ans = 1e18, cur = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 'a'; j < t[i]; j++) {
            int x = j - 'a';
            if (va[x].empty()) continue;
            int id = va[x].back();
            ans = min(ans, cur + query(1, 1, id - 1));
        }

        int x = t[i] - 'a';
        if (va[x].empty()) break;
        int id = va[x].back();
        va[x].pop_back();
        cur += query(1, 1, id - 1);
        update(1, id, id, -1);
    }

    cout << (ans == 1e18 ? -1 : ans) << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> s >> t;
        s = ' ' + s, t = ' ' + t;
        solve();
    }

    return 0;
}