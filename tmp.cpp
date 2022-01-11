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
#include <valarray>
#include <iomanip>

#define IOS ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define endl '\n'
#define clean(x) memset(x, 0, sizeof(x))
#define clean(x, n) memset(x, 0, (n) * sizeof *x)

using namespace std;
const int N = 1e3 + 5;
struct node {
    int x, y, z;
} g[5000000];
int f[N], f1[N];

void write(int m, int k) {
    if (m == 0) {
        cout << k << endl;
        return;
    }
    if (g[f1[m]].x == 2) {
        write(m - 2, k + 1);
        cout << g[f1[m]].z << ' ' << g[f1[m]].z + 1 << ' ' << g[f1[m]].y << endl;
    } else {
        write(m - 3, k + 1);
        cout << g[f1[m]].z << ' ' << g[f1[m]].z + 2 << ' ' << g[f1[m]].y << endl;
    }
}

int n, m;
string s;

void slove() {
    cin >> n >> m;
    int cnt = 0;
    unordered_map<string, int> f;
    for (int i = 1; i <= n; ++i) {
        cin >> s;
        for (int j = 1; j < m; ++j) {
            string now;
            now += s[i - 1];
            now += s[i];
            if (!f[now]) g[++cnt] = {2, i, j}, f[now] = cnt;
            if (j >= 2) {
                now = s[j - 2] + now;
                if (!f[now]) g[++cnt] = {3, i, j - 1}, f[now] = cnt;
            }
        }
    }
    cin >> s;
    s = "0" + s;
    clean(f1, (m + 1));
    f1[0] = -1;
    for (int i = 2; i <= m; ++i) {
        string now;
        now += s[i - 1];
        now += s[i];
        cout << now;
        if (f.count(now) && f1[i - 2])
            f1[i] = f[now];
        now = s[i - 2] + now;
        if (i >= 3 && f.count(now) && f1[i - 3]) f1[i] = f[now];
    }
    if (f1[m] == 0) cout << "-1\n";
    else write(m, 0);
}

signed main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) slove();
}
