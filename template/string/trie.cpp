// region trie
template<int SZ>
struct Trie {
    int ne[SZ + 10][26], cnt[SZ + 10], mem;

    Trie() {}

    void init() {
        fill(&ne[0][0], &ne[id][0], 0);
        cnt[0] = 0;
        mem = 0;
    }

    int new_node() {
        int id = ++mem;
        fill(&ne[id][0], &ne[id][26], 0);
        cnt[id] = 0;
        return id;
    }

    void add(const string &s) {
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
template<int SZ>
struct Trie {
    int mxb;
    int ne[32 * SZ + 10][2], cnt[32 * SZ + 10], mem;

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

    void add(int x) {
        int u = 0;
        for (int i = mxb; i >= 0; i--) {
            int bit = x >> i & 1;
            int &v = ne[u][bit];
            if (!v) v = new_node();
            u = v;
        }

        cnt[u]++;
    }

    int qr_mx(int x) {
        int u = 0, res = 0;
        for (int i = mxb; i >= 0; i--) {
            int bit = x >> i & 1;
            if (ne[u][!bit]) {
                res += 1 << i;
                u = ne[u][!bit];
            } else {
                u = ne[u][bit];
            }
        }

        return res;
    }

    int qr_mi(int x) {
        int u = 0, res = 0;
        for (int i = mxb; i >= 0; i--) {
            int bit = x >> i & 1;
            if (ne[u][bit]) {
                u = ne[u][bit];
            } else {
                res += 1 << i;
                u = ne[u][!bit];
            }
        }

        return res;
    }
};
// endregion
