// region 主席树
namespace {
#define mid (left + right >> 1)

    const int N = 2e5 + 10;

    struct Node {
        int left, right, ls, rs, sum;
    };

    int n, m;
    int va[N];
    int root[N];
    Node tr[N * 32];
    int tt;
    vector<int> lsh;

    int get_id(int x) {
        return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin() + 1;
    }

    int build(int left, int right) {
        int now = ++tt;
        tr[now].sum = 0;
        tr[now].left = left, tr[now].right = right;

        if (left == right) return now;
        tr[now].ls = build(left, mid);
        tr[now].rs = build(mid + 1, right);

        return now;
    }

    int update(int pre, int left, int right, int val) {
        int now = ++tt;
        tr[now] = tr[pre];

        tr[now].sum++;

        if (left == right) return now;
        if (val <= mid) tr[now].ls = update(tr[pre].ls, left, mid, val);
        else tr[now].rs = update(tr[pre].rs, mid + 1, right, val);

        return now;
    }

    int query(int pre, int now, int left, int right, int k) {
        if (left == right) return left;

        int tmp = tr[tr[now].ls].sum - tr[tr[pre].ls].sum;
        if (k <= tmp) return query(tr[pre].ls, tr[now].ls, left, mid, k);
        else return query(tr[pre].rs, tr[now].rs, mid + 1, right, k - tmp);
    }
}
// endregion

void solve() {
    for (int i = 1; i <= n; i++) lsh.push_back(va[i]);
    sort(lsh.begin(), lsh.end());
    lsh.erase(unique(lsh.begin(), lsh.end()), lsh.end());
    int sz = lsh.size();

    root[0] = build(1, sz);
    for (int i = 1; i <= n; i++) {
        int id = get_id(va[i]);
        root[i] = update(root[i - 1], 1, sz, id);
    }

    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        cout << lsh[query(root[a - 1], root[b], 1, sz, c) - 1] << endl;
    }
}