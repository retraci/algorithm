#include <bits/stdc++.h>

using namespace std;

struct Node {
    int sum, sz, p;
    double avg;
};

const int N = 1010;

int n, rt;
Node tr[N];

int find() {
    double mx = -1;
    int res = 0;
    for (int i = 1; i <= n; i++) {
        if (i == rt) continue;
        if (tr[i].avg > mx) {
            mx = tr[i].avg;
            res = i;
        }
    }
    return res;
}

void solve() {
    int ans = 0;
    for (int i = 1; i <= n; i++) ans += tr[i].sum;

    for (int k = 0; k < n - 1; k++) {
        int idx = find();
        int fa = tr[idx].p;

        ans += tr[idx].sum * tr[fa].sz;

        tr[fa].sum += tr[idx].sum;
        tr[fa].sz += tr[idx].sz;
        tr[fa].avg = 1.0*tr[fa].sum / tr[fa].sz;
        tr[idx].avg = -1;

        for (int i = 1; i <= n; i++) {
            if (tr[i].p == idx) tr[i].p = fa;
        }
    }

    cout << ans << endl;
}

int main() {
    cin >> n >> rt;
    for (int i = 1; i <= n; i++) {
        cin >> tr[i].sum;
        tr[i].sz = 1;
        tr[i].avg = tr[i].sum;
    }
    for (int i = 0, a, b; i < n - 1; i++) {
        cin >> a >> b;
        tr[b].p = a;
    }
    solve();

    return 0;
}