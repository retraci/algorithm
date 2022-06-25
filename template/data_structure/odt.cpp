// region odt
struct Odt {
    using odtt = int;

    map<int, odtt> tr;

    Odt() {}

    void init(int _n) {
        tr.clear();
        tr[0] = 0, tr[_n + 1] = 0;
    }

    void split(int pos) {
        auto [L, v] = *prev(tr.upper_bound(pos));
        tr[pos] = v;
    }

    void assign(int L, int R, odtt v) {
        split(L), split(R + 1);

        auto it = tr.find(L);
        while (it->fi != R + 1) {
            auto [tl, tv] = *it;
            it = tr.erase(it);
        }
        tr[L] = v;
    }

    odtt qr(int L, int R) {
        split(L), split(R + 1);

        odtt res = 0;
        auto it = tr.find(L);
        while (it->fi != R + 1) {
            auto [tl, tv] = *it;

            res += tv;
            it++;
        }

        return res;
    }
};
// endregion
