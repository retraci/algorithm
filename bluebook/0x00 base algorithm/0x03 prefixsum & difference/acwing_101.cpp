#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>

using namespace std;

typedef pair<int, int> PII;

const int maxn = 1e4 + 10;

int n, p, h, m;
int va[maxn], vb[maxn];
int vd[maxn];
map<PII, int> vis;

void solve() {
    for (int i = 1; i <= m; i++) {
        int left = va[i], right = vb[i];
        if (vis[PII(left, right)]) continue;
        vis[PII(left, right)] = 1;
        vd[left + 1]--, vd[right]++;
    }

    for (int i = 1; i <= n; i++) vd[i] += vd[i - 1];

    int del = h - vd[p];
    for (int i = 1; i <= n; i++) printf("%d\n", del + vd[i]);
}

int main() {
    cin >> n >> p >> h >> m;
    int a, b;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &a, &b);
        if (a > b) swap(a, b);
        va[i] = a, vb[i] = b;
    }
    solve();

    return 0;
}