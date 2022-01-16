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

/*
      0     1
      2     3
4  5  6  7  8  9  10
      11    12
13 14 15 16 17 18 19
      20    21
      22    23
*/

const int N = 33;
const int ops[8][7] = {
        {0, 2, 6, 11, 15, 20, 22},
        {1, 3, 8, 12, 17, 21, 23},
        {10, 9, 8, 7, 6, 5, 4},
        {19, 18, 17, 16, 15, 14, 13},
        {23, 21, 17, 12, 8, 3, 1},
        {22, 20, 15, 11, 6, 2, 0},
        {13, 14, 15, 16, 17, 18, 19},
        {4, 5, 6, 7, 8, 9, 10}
};
const int rops[8] = {5, 4, 7, 6, 1, 0, 3, 2};
const int center[8] = {6, 7, 8, 11, 12, 15, 16, 17};

int n;
int va[N];
vector<int> path;

int get() {
    static int cnt[4];
    memset(cnt, 0, sizeof cnt);
    for (int i = 0; i < 8; i++) {
        int id = center[i];
        cnt[va[id]]++;
    }
    int mx = *max_element(cnt, cnt + 4);
    return 8 - mx;
}

bool check() {
    int id0 = center[0];
    for (int i = 1; i < 8; i++) {
        int id = center[i];
        if (va[id] != va[id0]) return false;
    }
    return true;
}

void work(int op) {
    auto idx = ops[op];
    int tmp = va[idx[0]];
    for (int i = 1; i < 7; i++) {
        va[idx[i - 1]] = va[idx[i]];
    }
    va[idx[6]] = tmp;
}

bool dfs(int dep, int mx, int lst) {
    if (dep + get() > mx) return false;
    if (check()) return true;

    for (int k = 0; k < 8; k++) {
        if (k == rops[lst]) continue;
        work(k);
        path.push_back(k);
        if (dfs(dep + 1, mx, k)) return true;
        work(rops[k]);
        path.pop_back();
    }

    return false;
}

void solve() {
    path = {};
    int dep = 0;
    while (!dfs(0, dep, -1)) dep++;

    if (dep == 0) {
        cout << "No moves needed" << "\n";
        cout << va[center[0]] << "\n";
        return;
    }

    for (int op : path) cout << char(op + 'A');
    cout << "\n";
    cout << va[center[0]] << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    n = 24;
    while (cin >> va[0], va[0]) {
        for (int i = 1; i < n; i++) cin >> va[i];
        solve();
    }

    return 0;
}