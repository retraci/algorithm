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

const int N = 22;

int n;
int va[N];

int get() {
    int res = 0;
    for (int i = 2; i <= n; i++) {
        res += va[i] - va[i - 1] != 1;
    }

    return (res + 2) / 3;
}

bool check() {
    for (int i = 1; i <= n; i++) {
        if (va[i] != i) return false;
    }
    return true;
}

bool dfs(int dep, int mx) {
    if (dep + get() > mx) return false;
    if (check()) return true;

    int bak[N];
    memcpy(bak, va, sizeof va);
    for (int len = 1; len <= n - 1; len++) {
        for (int R = len; R <= n; R++) {
            int L = R - len + 1;
            for (int i = R + 1; i <= n; i++) {
                int pos = 1;
                for (int k = 1; k <= L - 1; k++) va[pos++] = bak[k];
                for (int k = R + 1; k <= i; k++) va[pos++] = bak[k];
                for (int k = L; k <= R; k++) va[pos++] = bak[k];
                for (int k = i + 1; k <= n; k++) va[pos++] = bak[k];
                if (dfs(dep + 1, mx)) return true;
            }
        }
    }
    memcpy(va, bak, sizeof va);

    return false;
}

void solve() {
    int dep = 0;
    while (dep < 5 && !dfs(0, dep)) dep++;
    if (dep >= 5) cout << "5 or more" << "\n";
    else cout << dep << "\n";
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}