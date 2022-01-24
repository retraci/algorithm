#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

ll n;
ll mx, ans;
int ps[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void dfs(int x, ll cur, ll cnt, int last) {
    if (mx < cnt || mx == cnt && ans > cur) {
        mx = cnt, ans = cur;
    }
    if (x >= 10) return;

    for (int i = 1; i <= last; i++) {
        cur *= ps[x];
        if (cur > n) return;
        dfs(x + 1, cur, cnt * (i + 1), i);
    }
}

void solve() {
    dfs(0, 1, 1, 31);

    cout << ans << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> n;
    solve();

    return 0;
}