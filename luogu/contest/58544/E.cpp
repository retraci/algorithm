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

const int N = 1010;
const int K = 110;

int n, k;
ll va[K][N];
ll vs[K][N];

int calc(int x, int y1, int y2) {
    for (int i = 1; i <= y2; i++) vs[x][i] = vs[x][i - 1] + va[x][i];

    return vs[x][y2] - vs[x][y1 - 1];
}

void solve() {
    while (n--) {
        ll op, p;
        cin >> op;
        if (op == 1) {
            cin >> p;
            while (p--) {
                ll x, y;
                cin >> x >> y;
                va[x][y]++;
            }
        } else {
            ll x, y1, y2;
            cin >> x >> y1 >> y2;
            cout << calc(x, y1, y2) << "\n";
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> k;
    solve();

    return 0;
}