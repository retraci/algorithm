#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

typedef pair<int, int> PII;

const int N = 50010;
const int M = 20;

int a0, a1, b0, b1;
int st[N], ps[N], tt;

PII factor[M];
int cntf;

int divisor[N], cntd;

void init() {
    tt = 0;
    memset(st, 0, sizeof st);
    for (int i = 2; i < N; i++) {
        if (st[i]) continue;
        ps[tt++] = i;
        for (int j = 2 * i; j < N; j += i) {
            st[j] = 1;
        }
    }
}

void dfs(int x, int cur) {
    if (x >= cntf) {
        divisor[cntd++] = cur;
        return;
    }

    for (int i = 0; i <= factor[x].second; i++) {
        dfs(x + 1, cur);
        cur *= factor[x].first;
    }
}

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int lcm(int a, int b) {
    int num = gcd(a, b);
    return 1LL * a * b / num;
}

bool check(int x) {
    if (gcd(x, a0) != a1) return false;
    if (lcm(x, b0) != b1) return false;
    return true;
}

void solve() {
    cntf = 0;
    int d = b1;
    for (int i = 0; i < tt; i++) {
        int p = ps[i];
        int cnt = 0;
        while (d % p == 0) {
            cnt++;
            d /= p;
        }
        if (cnt) factor[cntf++] = PII(p, cnt);
    }
    if (d > 1) factor[cntf++] = PII(d, 1);

    cntd = 0;
    dfs(0, 1);

    int ans = 0;
    for (int i = 0; i < cntd; i++) {
        int x = divisor[i];
        if (check(x)) ans++;
    }

    cout << ans << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    int T;
    cin >> T;
    init();
    while (T--) {
        scanf("%d%d%d%d", &a0, &a1, &b0, &b1);
        solve();
    }

    return 0;
}