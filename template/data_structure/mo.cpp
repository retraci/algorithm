// region Mo-Algo
ai3 qs[M];
int cnt[N], bl, cur;

void add(int x) {
    cur -= cnt[x] / 2;
    cnt[x]++;
    cur += cnt[x] / 2;
}

void del(int x) {
    cur -= cnt[x] / 2;
    cnt[x]--;
    cur += cnt[x] / 2;
}

int get(int i) {
    return (i - 1) / bl + 1;
}

void solve() {
    bl = sqrt(n);
    sort(qs + 1, qs + m + 1, [](auto &a, auto &b) {
        int bid1 = get(a[1]), bid2 = get(b[1]);
        if (bid1 != bid2) return bid1 < bid2;
        return bid1 & 1 ? a[2] < b[2] : a[2] > b[2];
    });

    int cl = 1, cr = 0;
    vector<int> ans(m + 1);
    for (int i = 1; i <= m; i++) {
        auto [qid, L, R] = qs[i];

        while (cl < L) del(a[cl++]);
        while (cl > L) add(a[--cl]);
        while (cr > R) del(a[cr--]);
        while (cr < R) add(a[++cr]);

        ans[qid] = cur;
    }

    for (int i = 1; i <= m; i++) cout << ans[i] << "\n";
}
// endregion