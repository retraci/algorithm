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

    const int SZ = 1e5;

    struct Node {
        int left, right;
        ll a, b, c, ab, bc, abc;
    };

    Node tree[SZ * 4];
    vector<ll> lsh;

    inline int get_id(ll x) {
        return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin() + 1;
    }

    inline void push_up(int node) {
        tree[node].a = tree[lson].a + tree[rson].a;
        tree[node].b = tree[lson].b + tree[rson].b;
        tree[node].c = tree[lson].c + tree[rson].c;

        tree[node].ab = min(tree[lson].a + tree[rson].ab, tree[lson].ab + tree[rson].b);
        tree[node].bc = min(tree[lson].b + tree[rson].bc, tree[lson].bc + tree[rson].c);
        tree[node].abc = min({tree[lson].a + tree[rson].abc,
                              tree[lson].ab + tree[rson].bc,
                              tree[lson].abc + tree[rson].c});
    }


    inline void push_down(int node) {

    }

    void build(int node, int left, int right) {
        tree[node].left = left, tree[node].right = right;
        tree[node].a = tree[node].b = tree[node].c = 0;
        tree[node].ab = tree[node].bc = tree[node].abc = 0;

        if (left == right) return;
        build(lson, left, mid);
        build(rson, mid + 1, right);
    }

    void update(int node, int L, int R, char ch) {
        int left = tree[node].left, right = tree[node].right;

        if (right < L || left > R) return;
        if (L <= left && right <= R) {
            tree[node].a = tree[node].b = tree[node].c = 0;
            tree[node].ab = tree[node].bc = tree[node].abc = 0;
            if (ch == 'a') tree[node].a = 1;
            else if (ch == 'b') tree[node].b = 1;
            else tree[node].c = 1;
            return;
        }

        push_down(node);
        update(lson, L, R, ch);
        update(rson, L, R, ch);
        push_up(node);
    }
}
using namespace Seg;

const int N = 1e5 + 10;

int n, q;
string str;

void solve() {
    build(1, 1, n);
    for (int i = 1; i <= n; i++) {
        update(1, i, i, str[i]);
    }

    while (q--) {
        int id;
        char ch;
        cin >> id >> ch;

        update(1, id, id, ch);
        cout << tree[1].abc << "\n";
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> q;
    cin >> str;
    str = ' ' + str;
    solve();

    return 0;
}