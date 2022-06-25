// region trie
template<int SZ, int B = 26>
struct Trie {
    int ne[SZ + 10][B], cnt[SZ + 10], mem;

    Trie() {}

    void init() {
        fill(&ne[0][0], &ne[0][B], 0);
        cnt[0] = 0;
        mem = 0;
    }

    int new_node() {
        int id = ++mem;
        fill(&ne[id][0], &ne[id][B], 0);
        cnt[id] = 0;
        return id;
    }

    void ins(const string &s) {
        int u = 0;
        for (char ch : s) {
            int &v = ne[u][ch - 'a'];
            if (!v) v = new_node();
            u = v;
        }

        cnt[u]++;
    }

    int qr(const string &s) {
        int u = 0, res = 0;
        for (char ch : s) {
            int &v = ne[u][ch - 'a'];
            if (!v) break;
            u = v;
            res += cnt[u];
        }

        return res;
    }
};
// endregion

// region 01trie
template<int SZ, int B = 32>
struct Trie {
    using trt = int;

    int mxb;
    int ne[B * SZ + 10][2], cnt[B * SZ + 10], mem;

    Trie() {}

    void init(int _mxb) {
        mxb = _mxb;
        ne[0][0] = ne[0][1] = 0;
        cnt[0] = 0;
        mem = 0;
    }

    int new_node() {
        int id = ++mem;
        ne[id][0] = ne[id][1] = 0;
        cnt[id] = 0;
        return id;
    }

    void ins(trt x) {
        int u = 0;
        for (int i = mxb; i >= 0; i--) {
            int bit = x >> i & 1;
            int &v = ne[u][bit];
            if (!v) v = new_node();
            u = v;
        }

        cnt[u]++;
    }

    trt qr_mx(trt x) {
        int u = 0;
        trt res = 0;
        for (int i = mxb; i >= 0; i--) {
            int bit = x >> i & 1;
            if (ne[u][!bit]) {
                res += 1LL << i;
                u = ne[u][!bit];
            } else {
                u = ne[u][bit];
            }
        }

        return res;
    }

    trt qr_mi(trt x) {
        int u = 0;
        trt res = 0;
        for (int i = mxb; i >= 0; i--) {
            int bit = x >> i & 1;
            if (ne[u][bit]) {
                u = ne[u][bit];
            } else {
                res += 1LL << i;
                u = ne[u][!bit];
            }
        }

        return res;
    }
};
// endregion
