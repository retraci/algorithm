// region 普通莫队
ai3 qs[M];
int cnt[N], bl, cur;

int get(int i) {
    return (i - 1) / bl + 1;
}

void solve() {
    bl = sqrt(n);
    sort(qs + 1, qs + q + 1, [](auto &a, auto &b) {
        int bid1 = get(a[1]), bid2 = get(b[1]);
        if (bid1 != bid2) return bid1 < bid2;
        return bid1 & 1 ? a[2] < b[2] : a[2] > b[2];
    });

    int cl = 1, cr = 0;
    vector<int> ans(q + 1);
    for (int i = 1; i <= q; i++) {
        auto [qid, L, R] = qs[i];

        while (cl < L) del(a[cl++]);
        while (cl > L) add(a[--cl]);
        while (cr > R) del(a[cr--]);
        while (cr < R) add(a[++cr]);

        ans[qid] = cur;
    }
}
// endregion

// region 回滚莫队
ai3 qs[N];
int cnt[N], bl, cur;

int get(int i) {
    return (i - 1) / bl + 1;
}

void solve() {
    bl = sqrt(n);
    sort(qs + 1, qs + q + 1, [](auto &a, auto &b) {
        int bid1 = get(a[1]), bid2 = get(b[1]);
        if (bid1 != bid2) return bid1 < bid2;
        return a[2] < b[2];
    });

    vector<int> lbs(n + 1), rbs(n + 1);
    for (int i = 1; i <= get(n); i++) {
        lbs[i] = (i - 1) * bl + 1;
        rbs[i] = i * bl;
    }

    vector<int> tmp(n + 1, 0);
    fill(cnt, cnt + n + 1, 0), cur = 0;
    vector<int> ans(q + 1);
    int cl = 1, cr = 0, lst = -1;
    for (int i = 1; i <= q; i++) {
        auto [qid, L, R] = qs[i];

        // 块内暴力
        if (get(L) == get(R)) {
            int mx = 0;
            for (int j = L; j <= R; j++) {
                tmp[a[j]]++;
                mx = max(mx, tmp[a[j]] * a[j]]);
            }
            for (int j = L; j <= R; j++) tmp[a[j]]--;
            ans[qid] = mx;
            continue;
        }

        // 下一个块
        if (get(L) != lst) {
            for (int j = cl; j <= cr; j++) cnt[a[j]] = 0;
            int rb = rbs[get(L)];
            cl = rb + 1, cr = rb;
            cur = 0;
            lst = get(L);
        }

        // cr往后
        while (cr < R) add(a[++cr]);
        // 暴力搞 cl, 再回滚
        int bak = cur;
        for (int j = cl - 1; j >= L; j--) add(a[j]);
        ans[qid] = cur;
        for (int j = cl - 1; j >= L; j--) del(a[j]);
        cur = bak;
    }
}
// endregion
