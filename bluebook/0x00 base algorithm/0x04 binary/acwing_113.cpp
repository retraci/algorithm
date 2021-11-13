// Forward declaration of compare API.
// bool compare(int a, int b);
// return bool means whether a is less than b.

class Solution {
public:
    vector<int> specialSort(int N) {
        vector<int> res(N, -1);
        res[0] = 1;
        for (int i = 1; i < N; i++) {
            res[i] = i + 1;

            int left = 0, right = i;
            while (left < right) {
                int mid = left + right >> 1;
                if (compare(res[i], res[mid])) right = mid;
                else left = mid + 1;
            }

            for (int j = i; j > left; j--) swap(res[j], res[j - 1]);
        }

        return res;
    }
};

