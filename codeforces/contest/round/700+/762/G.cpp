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

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 2e5 + 10;

struct Mine {
    int x, y, t, id;
};

int n, m;
Mine va[N];

int fa[N];
int mit[N];
vector<int> vb;

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool check(int mid) {
    int id = upper_bound(vb.begin(), vb.end(), mid) - vb.begin();
    int rem = vb.size() - id;
    return rem <= mid + 1;
}

void solve() {
    for (int i = 1; i <= n; i++) fa[i] = i, mit[i] = va[i].t;

    sort(va + 1, va + n + 1, [&](const auto &a, const auto &b) {
        if (a.x == b.x) return a.y < b.y;
        return a.x < b.x;
    });
    for (int i = 1; i <= n; i++) {
        int x = va[i].x;
        int j = i;
        while (j <= n && va[j].x == x) j++;

        for (int k = i + 1; k < j; k++) {
            if (va[k].y - va[k - 1].y > m) continue;

//            cout << va[k].x << " " << va[k].y << " " << va[k - 1].x << " " << va[k - 1].y << "\n";

            int tx = find(va[k].id), ty = find(va[k - 1].id);
            if (tx == ty) continue;
            fa[ty] = tx;
            mit[tx] = min(mit[tx], mit[ty]);
        }

        i = j - 1;
    }

    sort(va + 1, va + n + 1, [&](const auto &a, const auto &b) {
        if (a.y == b.y) return a.x < b.x;
        return a.y < b.y;
    });
    for (int i = 1; i <= n; i++) {
        int y = va[i].y;
        int j = i;
        while (j <= n && va[j].y == y) j++;

        for (int k = i + 1; k < j; k++) {
            if (va[k].x - va[k - 1].x > m) continue;

//            cout << va[k].x << " " << va[k].y << " " << va[k - 1].x << " " << va[k - 1].y << "\n";

            int tx = find(va[k].id), ty = find(va[k - 1].id);
            if (tx == ty) continue;
            fa[ty] = tx;
            mit[tx] = min(mit[tx], mit[ty]);
        }

        i = j - 1;
    }

    vb = {};
    for (int i = 1; i <= n; i++) {
        int id = va[i].id;
        int tx = find(id);
        if (tx == id) vb.push_back(mit[tx]);
    }

    sort(vb.begin(), vb.end());
    int left = 0, right = 1e9;
    while (left < right) {
        int mid = left + right >> 1;
        if (check(mid)) right = mid;
        else left = mid + 1;
    }
    cout << left << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T; cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            int x, y, t;
            cin >> x >> y >> t;
            va[i] = {x, y, t, i};
        }
        solve();
    }

    return 0;
}