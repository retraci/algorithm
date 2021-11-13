// 完全二叉树的权值

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const int N = 100010;

int n;
int va[N];

void solve() {
    int dep = 1;
    int cnt = 1;
    int idx = 0;

    ll ans, mx = -0x3f3f3f3f;
    while (idx < n) {
        ll cur = 0;
        for (int i = 0; i < cnt && idx < n; i++, idx++) {
            cur += va[idx];
        }

        if (mx < cur) mx = cur, ans = dep;

        cnt *= 2;
        dep++;
    }

    cout << ans << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> n;
    for (int i = 0; i < n; i++) scanf("%d", &va[i]);
    solve();

    return 0;
}