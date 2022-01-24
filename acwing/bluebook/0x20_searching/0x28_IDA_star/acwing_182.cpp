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

const int N = 77;

int n, m;
int va[N];

vector<int> vb[N];
int tt;
int vis[N];

void init() {
    tt = 0;
    int d = n + n + 1;
    for (int len = 1; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            for (int j = 1; j + len - 1 <= n; j++) {
                vb[++tt].clear();
                for (int k = 0; k < len; k++) {
                    vb[tt].push_back((i - 1) * d + j + k);
                    vb[tt].push_back((i - 1 + len) * d + j + k);
                    vb[tt].push_back((i - 1) * d + n + j + k * d);
                    vb[tt].push_back((i - 1) * d + n + j + k * d + len);
                }
            }
        }
    }

    memset(vis, 0, sizeof vis);
    for (int i = 1; i <= m; i++) vis[va[i]] = 1;
}

bool check(int x) {
    for (int a : vb[x]) {
        if (vis[a]) return true;
    }
    return false;
}

int get() {
    static int bak[N];
    memcpy(bak, vis, sizeof vis);

    int res = 0;
    for (int i = 1; i <= tt; i++) {
        if (!check(i)) {
            res++;
            for (int x : vb[i]) vis[x] = 1;
        }
    }

    memcpy(vis, bak, sizeof vis);

    return res;
}

bool dfs(int dep, int mx) {
    if (dep + get() > mx) return false;

    for (int i = 1; i <= tt; i++) {
        if (check(i)) continue;

        for (int x : vb[i]) {
            vis[x] = 1;
            if (dfs(dep + 1, mx)) return true;
            vis[x] = 0;
        }
        return false;
    }

    return true;
}

void solve() {
    init();

    int dep = 0;
    while (!dfs(0, dep)) dep++;

    cout << dep << "\n";
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
        cin >> n >> m;
        for (int i = 1; i <= m; i++) cin >> va[i];
        solve();
    }

    return 0;
}