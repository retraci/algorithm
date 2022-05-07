#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <cmath>
#include <random>

void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}

using namespace std;

#define fi first
#define se second
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using pii = pair<int, int>;

// region 维护序列(fhq + gc)
mt19937 rnd(random_device{}());
template<class Info, class Tag, int SZ>
struct Fhq {
#define ls(x) (info[x].lson)
#define rs(x) (info[x].rson)

    Info (*plus)(const Info &p, const Info &a, const Info &b);
    int n, rt, mem[SZ + 10], tp;
    Info info[SZ + 10];
    Tag tag[SZ + 10];

    Fhq() : plus(Info::plus) {}

    void init() {
        rt = 0, tp = SZ;
        iota(mem, mem + SZ + 1, 0);
        info[0] = Info();
        info[0].mxl = -1e9;
        tag[0] = Tag();
    }

    int new_node() {
        int id = mem[tp--];
        info[id] = Info();
        tag[id] = Tag();
        return id;
    }

    void del_node(int k) {
        if (!k) return;
        mem[++tp] = k;
        if (ls(k)) del_node(ls(k));
        if (rs(k)) del_node(rs(k));
    }

    int size() {
        return info[rt].sz;
    }

    void pull(int k) {
        info[k].set(plus(info[k], info[ls(k)], info[rs(k)]));
    }

    void apply(int k, const Tag &v) {
        info[k].apply(v);
        tag[k].apply(v);
    }

    void push(int k) {
        if (tag[k].check()) {
            if (ls(k)) apply(ls(k), tag[k]);
            if (rs(k)) apply(rs(k), tag[k]);
            tag[k] = Tag();
        }
    }

    void split(int k, int sz, int &x, int &y) {
        if (!k) {
            x = y = 0;
            return;
        }

        push(k);
        if (info[ls(k)].sz < sz) {
            x = k;
            split(rs(k), sz - info[ls(k)].sz - 1, rs(k), y);
        } else {
            y = k;
            split(ls(k), sz, x, ls(k));
        }
        pull(k);
    }

    int merge(int x, int y) {
        if (!x || !y) return x | y;

        if (info[x].key > info[y].key) {
            push(x);
            rs(x) = merge(rs(x), y);
            pull(x);
            return x;
        } else {
            push(y);
            ls(y) = merge(x, ls(y));
            pull(y);
            return y;
        }
    }

    int build(int L, int R, Info a[]) {
        if (L > R) return 0;
        if (L == R) {
            int k = new_node();
            info[k] = a[L];
            info[k].init();
            return k;
        }

        int mid = L + R >> 1, p = new_node();
        info[p] = a[mid];
        info[p].init();
        ls(p) = build(L, mid - 1, a);
        rs(p) = build(mid + 1, R, a);
        pull(p);
        return p;
    }

    void insarr(int p, int len, Info a[]) {
        int x, y;
        split(rt, p, x, y);

        int nt = build(1, len, a);
        rt = merge(merge(x, nt), y);
    }

    void ins(int p, const Info &v) {
        int x, y;
        split(rt, p, x, y);

        int t = new_node();
        info[t] = v;
        info[t].init();
        rt = merge(merge(x, t), y);
    }

    void del(int L, int R) {
        int x, y, z;
        split(rt, L - 1, x, y);
        split(y, R - L + 1, y, z);

        del_node(y);
        rt = merge(x, z);
    }

    void upd(int L, int R, const Tag &v) {
        int x, y, z;
        split(rt, L - 1, x, y);
        split(y, R - L + 1, y, z);

        apply(y, v);
        rt = merge(merge(x, y), z);
    }

    Info qr(int L, int R) {
        int x, y, z;
        split(rt, L - 1, x, y);
        split(y, R - L + 1, y, z);

        Info res = info[y];
        rt = merge(merge(x, y), z);
        return res;
    }

    void dump(int k, vector<Info> &seq) {
        if (!k) return;

        push(k);
        dump(ls(k), seq);
        seq.push_back(info[k].val);
        dump(rs(k), seq);
    }

    vector<Info> dump() {
        vector<Info> res;
        dump(rt, res);
        return res;
    }
};
// endregion

// region 文艺平衡树(fhq)
struct Tag {
    int rev, cov;

    Tag(int rev = 0, int cov = 1e9) : rev(rev), cov(cov) {}

    bool check() const {
        return rev != 0 || cov != 1e9;
    }

    void apply(const Tag &a) {
        if (!a.check()) return;
        if (a.cov != 1e9) cov = a.cov;
        if (a.rev) rev ^= a.rev;
    }
};

struct Info {
    int lson, rson, key, val;
    int sz, sum, pre, suf, mxl;

    Info(int val = 0, int sz = 0, int sum = 0, int pre = 0, int suf = 0, int mxl = 0) : lson(0), rson(0), val(val), sz(sz),
                                                                                        sum(sum), pre(pre), suf(suf), mxl(mxl) {}

    void init() {
        key = rnd();
    }

    void apply(const Tag &a) {
        if (!a.check()) return;
        if (a.cov != 1e9) {
            val = a.cov, sum = sz * val;
            if (a.cov >= 0) pre = suf = mxl = sum;
            else mxl = val, pre = suf = 0;
        }
        if (a.rev) {
            swap(lson, rson);
            swap(pre, suf);
        }
    }

    static Info plus(const Info &p, const Info &a, const Info &b) {
        Info res = Info();
        res.sz = a.sz + b.sz + 1;
        res.sum = a.sum + b.sum + p.val;
        res.pre = max(a.pre, a.sum + p.val + b.pre);
        res.suf = max(b.suf, b.sum + p.val + a.suf);
        res.mxl = max({a.mxl, b.mxl, a.suf + p.val + b.pre});
        return res;
    }

    void set(const Info &a) {
        sz = a.sz, sum = a.sum, pre = a.pre, suf = a.suf, mxl = a.mxl;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 500010;

int n, m;
int a[N];
Info buf[N];
Fhq<Info, Tag, N> fhq;

void solve() {
    fhq.init();
    for (int i = 1; i <= n; i++) {
        Info v;
        v.val = v.sum = v.mxl = a[i];
        v.pre = v.suf = max(0, a[i]);
        v.sz = 1;
        buf[i] = v;
    }
    fhq.insarr(0, n, buf);

    while (m--) {
        string op;
        cin >> op;

        if (op[0] == 'I') {
            int p, k;
            cin >> p >> k;

            for (int i = 1; i <= k; i++) {
                int x;
                cin >> x;

                Info v;
                v.val = v.sum = v.mxl = x;
                v.pre = v.suf = max(0, x);
                v.sz = 1;
                buf[i] = v;
            }

            fhq.insarr(p, k, buf);
        }

        if (op[0] == 'D') {
            int L, len;
            cin >> L >> len;

            fhq.del(L, L + len - 1);
        }

        if (op[0] == 'M' && op[2] == 'K') {
            int L, len, x;
            cin >> L >> len >> x;

            fhq.upd(L, L + len - 1, {0, x});
        }

        if (op[0] == 'R') {
            int L, len;
            cin >> L >> len;

            fhq.upd(L, L + len - 1, {1, (int) 1e9});
        }

        if (op[0] == 'G') {
            int L, len;
            cin >> L >> len;

            cout << fhq.qr(L, L + len - 1).sum << "\n";
        }

        if (op[0] == 'M' && op[2] == 'X') {
            cout << fhq.qr(1, fhq.size()).mxl << "\n";
        }
    }
}

void prework() {
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    prework();
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
//    cin >> _;
    while (_--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}