#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> PII;

const int maxn = 1e5 + 10;

int n, m;
PII va[maxn];

int calc(int a, int bit) {
    int res = a;
    for (int i = 0; i < n; i++) {
        int op = va[i].first;
        int num = va[i].second >> bit & 1;
        if (op == 1) res = res & num;
        else if (op == 2) res = res | num;
        else if (op == 3) res = res ^ num;
    }

    return res;
}

void solve() {
    int cur = 0, ans = 0;
    for (int bit = 29; ~bit; bit--) {
        int res0 = calc(0, bit);
        int res1 = calc(1, bit);
        if (cur + (1 << bit) <= m && res1 > res0) {
            cur += 1 << bit;
            ans += res1 << bit;
        } else {
            ans += res0 << bit;
        }
    }
    cout << ans << endl;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int tmp1, tmp2;
        char tmp[5];
        scanf("%s%d", tmp, &tmp2);

        if (tmp[0] == 'A') tmp1 = 1;
        else if (tmp[0] == 'O') tmp1 = 2;
        else tmp1 = 3;

        va[i] = PII(tmp1, tmp2);
    }
    solve();

    return 0;
}
