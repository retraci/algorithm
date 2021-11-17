#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

/*----------------------------------------*/

// 线性基
#define ll long long

vector<ll> B;

void insert(ll x) {
    for (auto b: B) x = min(x, b ^ x);
    for (auto &b: B) b = min(b, b ^ x);
    if (x) B.push_back(x);
}

ll query(ll k) {
    ll res = 0;
    if (B.size() < n) k--;
    for (auto b: B) {
        if (k & 1) res ^= b;
        k >>= 1;
    }

    if (k == 0) return res;
    else return -1;
}

void solve() {
    B = {};
    for (int i = 1; i <= n; i++) insert(va[i]);
    // 排序
    sort(B.begin(), B.end());
}