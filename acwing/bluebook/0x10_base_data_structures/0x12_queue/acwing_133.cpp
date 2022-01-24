#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <limits.h>

using namespace std;

const int N = 1e5 + 10;
const int M = 1e7 + 10;

int m, q, u, v, t;
int que1[N], que2[M], que3[M], h1, h2, h3, tt1, tt2, tt3;
int delta;

int getMax() {
    int res = INT_MIN;
    if (h1 < tt1) res = max(res, que1[h1]);
    if (h2 < tt2) res = max(res, que2[h2]);
    if (h3 < tt3) res = max(res, que3[h3]);

    if (h1 < tt1 && res == que1[h1]) h1++;
    else if (h2 < tt2 && res == que2[h2]) h2++;
    else h3++;

    return res;
}

void solve() {
    sort(que1, que1 + tt1, greater<>());

    delta = h1 = h2 = h3 = tt2 = tt3 = 0;
    for (int i = 1; i <= m; i++) {
        int mx = getMax() + delta;
        int left = 1LL * mx * u / v;
        int right = mx - left;
        delta += q;
        que2[tt2++] = left - delta;
        que3[tt3++] = right - delta;

        if (i % t == 0) printf("%d ", mx);
    }
    cout << endl;

    int tt = 1;
    while (1) {
        if (h1 >= tt1 && h2 >= tt2 && h3 >= tt3) break;

        int mx = getMax() + delta;
        if (tt % t == 0) if (tt % t == 0) printf("%d ", mx);
        tt++;
    }
    cout << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> tt1 >> m >> q >> u >> v >> t;
    for (int i = 0; i < tt1; i++) {
        scanf("%d", &que1[i]);
    }
    solve();

    return 0;
}