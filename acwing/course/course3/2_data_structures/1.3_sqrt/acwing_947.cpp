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
#include <cassert>
#include <random>
#include <cmath>

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

// region 维护序列(fhq)
mt19937 rnd(random_device{}());
template<class Info, class Tag, int SZ>
struct Fhq {
#define ls(x) (info[x].lson)
#define rs(x) (info[x].rson)

    Info (*plus)(const Info &p, const Info &a, const Info &b);
    int n, rt, mem;
    Info info[SZ + 10];
    Tag tag[SZ + 10];

    Fhq() : plus(Info::plus) {}

    void init() {
        rt = 0, mem = 0;
        info[0] = Info();
        tag[0] = Tag();
    }

    int new_node() {
        int id = ++mem;
        assert(id < SZ + 10);
        info[id] = Info();
        tag[id] = Tag();
        return id;
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

    int build(int L, int R, char a[]) {
        if (L > R) return 0;
        if (L == R) {
            int t = new_node();
            info[t] = a[L];
            info[t].init();
            return t;
        }

        int mid = L + R >> 1, k = new_node();
        info[k] = a[mid];
        info[k].init();
        ls(k) = build(L, mid - 1, a);
        rs(k) = build(mid + 1, R, a);
        pull(k);
        return k;
    }

    void insarr(int p, int len, char a[]) {
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

        rt = merge(x, z);
    }

    void upd(int L, int R, const Tag &v) {
        int x, y, z;
        split(rt, L - 1, x, y);
        split(y, R - L + 1, y, z);

        apply(y, v);
        rt = merge(merge(x, y), z);
    }

    void qr(int L, int R) {
        int x, y, z;
        split(rt, L - 1, x, y);
        split(y, R - L + 1, y, z);

        print(y);
        rt = merge(merge(x, y), z);
    }

    void print(int k) {
        if (!k) return;

        push(k);
        print(ls(k));
        printf("%c", info[k].val);
        print(rs(k));
    }

    void dump(int k, vector<Info> &seq) {
        if (!k) return;

        push(k);
        dump(ls(k), seq);
        seq.push_back(info[k]);
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
    int x;

    Tag(int x = 0) : x(x) {}

    bool check() const {
        return x != 0;
    }

    void apply(const Tag &a) {
        if (!a.check()) return;
        x ^= a.x;
    }
};

struct Info {
    int lson, rson, key;
    char val;
    int sz;

    Info(char val = 0, int sz = 0) : lson(0), rson(0), val(val), sz(sz) {}

    void init() {
        key = rnd();
        sz = 1;
    }

    void apply(const Tag &a) {
        if (!a.check()) return;
        swap(lson, rson);
    }

    static Info plus(const Info &p, const Info &a, const Info &b) {
        return {0, a.sz + b.sz + 1};
    }

    void set(const Info &a) {
        sz = a.sz;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1024 * 1024 * 2 + 10;

int n;
Fhq<Info, Tag, N> fhq;
char buf[N];

void solve() {
    fhq.init();

    int pos = 0;
    while (n--) {
        string op;
        cin >> op;

        if (op[0] == 'M') cin >> pos;
        if (op[0] == 'P') pos--;
        if (op[0] == 'N') pos++;

        if (op[0] == 'I') {
            int sz;
            cin >> sz;

            int p = 1;
            while (p <= sz) {
                buf[p] = getchar();
                if (buf[p] >= 32 && buf[p] <= 126) p++;
            }
            fhq.insarr(pos, sz, buf);
        }
        if (op[0] == 'D') {
            int sz;
            cin >> sz;

            fhq.del(pos + 1, pos + sz);
        }
        if (op[0] == 'G') {
            int sz;
            cin >> sz;

            fhq.qr(pos + 1, pos + sz);
            printf("\n");
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
//    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
//    cin >> _;
    while (_--) {
        cin >> n;
        solve();
    }

    return 0;
}