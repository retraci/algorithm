// region odt
struct Odt {
    using odtt = int;

    int n;
    map<int, odtt> odt;

    Odt() {}

    void init(int _n) {
        n = _n;
        odt[0] = 0, odt[n + 1] = 0;
    }

    void split(int pos) {
        auto [L, v] = *prev(odt.upper_bound(pos));
        odt[pos] = v;
    }

    void assign(int L, int R, odtt v) {
        split(L), split(R + 1);

        auto it = odt.find(L);
        while (it->fi != R + 1) {
            auto [tl, tv] = *it;
            it = odt.erase(it);
        }
        odt[L] = v;
    }
};
// endregion