// 修改数组

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e5 + 10;
const int M = 1e6 + 10;

int n;
int va[N], vb[N];
int fa[M];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void solve() {
    for (int i = 1; i < M; i++) fa[i] = i;

    for (int i = 0; i < n; i++) {
        vb[i] = find(va[i]);
        fa[vb[i]] = vb[i] + 1;
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", vb[i]);
    }
    cout << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> n;
    for (int i = 0; i < n; i++) scanf("%d", &va[i]);
    solve();

    return 0;
}