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
#include <numeric>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 5e5 + 10;

int fa[2 * N];
int mp[2 * N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void solve() {
    for (int i = 0; i < 2 * N; i++) fa[i] = i;

    int q;
    cin >> q;
    int idx = 0;
    while (q--) {
        int op, a, b;
        cin >> op;
        if (op == 1) {
            cin >> a;
            int id = N + idx++;

            int tx = find(a), ty = find(id);
            fa[tx] = ty;
        } else {
            cin >> a >> b;
            if (a == b) continue;

            int tx = find(a), ty = find(b);
            if (a == tx) continue;
            fa[ty] = tx;
            fa[a] = a;
        }
    }

    for (int i = 1; i < N; i++) mp[find(i)] = i;
    for (int i = 0; i < idx; i++) {
        cout << mp[find(i + N)] << " ";
    }
    cout << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();

    return 0;
}