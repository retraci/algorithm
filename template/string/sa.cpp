// region 后缀数组
int sa[N], rk[N], tp[N], c[N], h[N];

bool cmp(int i, int k) {
    return tp[sa[i - 1]] == tp[sa[i]] && tp[sa[i - 1] + k] == tp[sa[i] + k];
}

void tsort(int ta[], int fir[], int sed[], int sz) {
    for (int i = 1; i <= sz; i++) c[i] = 0;
    for (int i = 1; i <= n; i++) c[fir[i]]++;
    for (int i = 1; i <= sz; i++) c[i] += c[i - 1];
    for (int i = n; i >= 1; i--) ta[c[fir[sed[i]]]--] = sed[i];
}

void get_sa() {
    int sz = 122;
    for (int i = 1; i <= n; i++) rk[i] = s[i], tp[i] = i;
    tsort(sa, rk, tp, sz);
    for (int k = 1; k <= n; k *= 2) {
        int num = 0;
        for (int i = n - k + 1; i <= n; i++) tp[++num] = i;
        for (int i = 1; i <= n; i++) {
            if (sa[i] - k >= 1) tp[++num] = sa[i] - k;
        }

        tsort(sa, rk, tp, sz), swap(rk, tp);
        rk[sa[1]] = 1, num = 1;
        for (int i = 2; i <= n; i++) {
            rk[sa[i]] = cmp(i, k) ? num : ++num;
        }
        if (num == n) break;
        sz = num;
    }
}

void get_h() {
    for (int i = 1, k = 0; i <= n; i++) {
        if (rk[i] == 1) continue;
        int j = sa[rk[i] - 1];
        if (k) k--;
        while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k++;
        h[rk[i]] = k;
    }
}
// endregion
