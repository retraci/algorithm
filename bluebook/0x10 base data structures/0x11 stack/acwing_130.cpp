#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

const int N = 120010;
const ll BASE = 1e9;

int n;
int st[N];
vector<int> ps;
int cnt[N];

void init() {
    memset(st, 0, sizeof st);
    for (int i = 2; i < N; i++) {
        if (st[i]) continue;
        ps.push_back(i);
        for (int j = 2 * i; j < N; j += i) st[j] = 1;
    }
}

int get(int a, int p) {
    int res = 0;
    while (a) {
        res += a / p;
        a /= p;
    }
    return res;
}

void multi(vector<ll> &a, int b) {
    ll t = 0;
    for (int i = 0; i < a.size(); i++) {
        ll tmp = a[i] * b + t;
        a[i] = tmp % BASE;
        t = tmp / BASE;
    }
    while (t) {
        a.push_back(t % BASE);
        t /= BASE;
    }
}

void out(vector<ll> &a) {
    printf("%lld", a.back());
    for (int i = a.size() - 2; i >= 0; i--) {
        printf("%09lld", a[i]);
    }
    cout << endl;
}

void solve() {
    init();

    memset(cnt, 0, sizeof cnt);
    for (int p : ps) {
        int tmp = get(2 * n, p) - get(n, p) * 2;
        cnt[p] = tmp;
    }
    int t = n + 1;
    for (int p : ps) {
        while (t % p == 0) {
            cnt[p]--;
            t /= p;
        }
    }

    vector<ll> sum(1, 1);
    for (int p : ps) {
        while (cnt[p]) {
            multi(sum, p);
            cnt[p]--;
        }
    }

    out(sum);
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> n;
    solve();

    return 0;
}