// region 线性基
vector<ll> bas;

void insert(ll x) {
    for (auto b: bas) x = min(x, b ^ x);
    for (auto &b: bas) b = min(b, b ^ x);
    if (x) bas.push_back(x);
}

ll query(ll k) {
    ll res = 0;
    if (bas.size() < n) k--;
    for (auto b: bas) {
        if (k & 1) res ^= b;
        k >>= 1;
    }

    if (k == 0) return res;
    else return -1;
}

void init_lbas() {
    bas = {};
    for (int i = 1; i <= n; i++) insert(va[i]);
    // 排序
    sort(bas.begin(), bas.end());

}
// endregion