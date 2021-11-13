#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 20010 * 2;

int x, y;
int va[N];
int idx[N];
int ans[N];

bool cmp(int a, int b) {
    return va[a] > va[b];
}

void solve() {
    if (x == y) {
        for (int i = 0; i < x; i++) printf("A");
        for (int i = 0; i < y; i++) printf("B");
        return;
    }

    for (int i = 0; i < x + y; i++) idx[i] = i;
    sort(idx, idx + x + y, cmp);
    memset(ans, 0, sizeof ans);
    if (x > y) {
        for (int i = 0; i < y; i++) ans[idx[i]] = 1;
        for (int i = 0; i < x + y; i++) {
            if (ans[i]) printf("B");
            else printf("A");
        }
    } else {
        for (int i = 0; i < x; i++) ans[idx[i]] = 1;
        for (int i = 0; i < x + y; i++) {
            if (ans[i]) printf("A");
            else printf("B");
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> x >> y;
    for (int i = 0; i < x + y; i++) {
        scanf("%d", &va[i]);
    }
    solve();

    return 0;
}