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
int va[N], vb[N];
int idx1[N], idx2[N];
int mp1[N], mp2[N];

void solve() {
    for (int i = 1; i <= n; i++) idx1[i] = idx2[i] = i;
    sort(idx1 + 1, idx1 + n + 1, [&](auto &a, auto &b) {
        return va[a] < va[b];
    });
    sort(idx2 + 1, idx2 + n + 1, [&](auto &a, auto &b) {
        return vb[a] < vb[b];
    });
    for (int i = 1; i <= n; i++) mp1[idx1[i]] = i, mp2[idx2[i]] = i;

    int q;
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;

        int nx = mp1[x], ny = mp2[y];
        if (nx + ny >= n + 1) cout << '#';
        else cout << '.';
    }
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