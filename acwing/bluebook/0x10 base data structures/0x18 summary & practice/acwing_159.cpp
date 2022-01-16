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

const int N = 10010;

int n, m;
string g[N];
int ne[N];

void get_next() {
    for (int i = 2, j = 0; i <= n; i++) {
        while (j && g[i] != g[j + 1]) j = ne[j];
        if (g[i] == g[j + 1]) j++;
        ne[i] = j;
    }
}

void solve() {
    int wid = m;
    for (int k = 1; k <= m; k++) {
        int flag = 0;
        for (int i = 1; i <= n; i++) {
            int id1 = 0, id2 = k;
            while (id2 < m) {
                if (g[i][id1] != g[i][id2]) flag = 1;
                id1++, id2++;
            }
        }

        if (!flag) {
            wid = k;
            break;
        }
    }

    for (int i = 1; i <= n; i++) g[i] = g[i].substr(0, wid);
    get_next();
    int hei = n - ne[n];
    cout << wid * hei << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> g[i];
    solve();

    return 0;
}