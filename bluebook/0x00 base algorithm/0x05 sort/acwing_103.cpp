#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 200010 * 3;

int n, m;
int va[maxn], vb1[maxn], vb2[maxn];
int cnt[maxn];
int lang[maxn], tot;
int mov[maxn];

int bs(int x) {
    return lower_bound(lang, lang+tot, x) - lang;
}

void solve() {
    for (int i = 0; i < n; i++) lang[tot++] = va[i];
    for (int i = 0; i < m; i++) {
        lang[tot++] = vb1[i];
        lang[tot++] = vb2[i];
    }
    sort(lang, lang + tot);
    tot = unique(lang, lang + tot) - lang;

    for (int i = 0; i < n; i++) cnt[bs(va[i])]++;

    int max1 = 0, max2 = 0;
    int ans = -1;
    for (int i = 0; i < m; i++) {
        int i1 = vb1[i], i2 = vb2[i];
        int cnt1 = cnt[bs(i1)], cnt2 = cnt[bs(i2)];

        if (cnt1 > max1) {
            ans = i;
            max1 = cnt1, max2 = cnt2;
        } else if (cnt1 == max1 && cnt2 > max2) {
            ans = i;
            max1 = cnt1, max2 = cnt2;
        }
    }

    cout << ans + 1 << endl;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) scanf("%d", &va[i]);
    cin >> m;
    for (int i = 0; i < m; i++) scanf("%d", &vb1[i]);
    for (int i = 0; i < m; i++) scanf("%d", &vb2[i]);

    solve();

    return 0;
}

