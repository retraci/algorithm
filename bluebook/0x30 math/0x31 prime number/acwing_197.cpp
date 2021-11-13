#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

const int N = 1e6 + 10;

int n;
int st[N];
vector<int> ps;
int cnt[N];

void init() {
    memset(st, 0, sizeof st);
    for (int i = 2; i <= n; i++) {
        if (st[i]) continue;
        ps.push_back(i);
        for (int k = 2; k * i <= n; k++) st[k * i] = 1;
    }
}

void solve() {
    init();

    memset(cnt, 0, sizeof cnt);
    for (int i = 0; i < ps.size(); i++) {
        int p = ps[i];

        int sum = 0;
        ll cur = p;
        while (cur <= n) {
            sum += n / cur;
            cur *= p;
        }
        cnt[i] = sum;
    }

    for (int i = 0; i < ps.size(); i++) {
        if (cnt[i] != 0) printf("%d %d\n", ps[i], cnt[i]);
    }
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> n;
    solve();

    return 0;
}