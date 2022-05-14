// region 普通方程
template<int SZ>
struct Gauss {
    const ld eps = 1e-9;

    ld mat[SZ + 10][SZ + 10];

    Gauss() {
        memset(mat, 0, sizeof mat);
    }

    // r 为方程个数, c 为未知数个数; 无解返回 -1, 多解返回 自由元个数
    // mat[1 ~ c]: 增广矩阵, c + 1 位置为常数
    const pair<int, vector<ld>> work(int r, int c) {
        int row = 1;
        for (int col = 1; col <= c; col++) {
            for (int i = row; i <= r; i++) {
                if (fabs(mat[i][col]) > eps) {
                    for (int j = col; j <= c + 1; j++) swap(mat[i][j], mat[row][j]);
                    break;
                }
            }
            if (fabs(mat[row][col]) < eps) break;

            for (int i = 1; i <= r; i++) {
                if (i != row && fabs(mat[i][col]) > eps) {
                    ld rate = mat[i][col] / mat[row][col];
                    for (int j = c + 1; j >= col; j--) {
                        mat[i][j] -= mat[row][j] * rate;
                    }
                }
            }
            row++;
        }

        if (row <= r) {
            for (int i = row; i <= r; i++) {
                if (fabs(mat[i][c + 1]) > eps) return {-1, {}};
            }
            return {r - row + 1, {}};
        }

        vector<ld> res(c + 1);
        for (int i = 1; i <= c; i++) res[i] = mat[i][c + 1] /= mat[i][i];

        return {0, res};
    }
};
// endregion

// region 异或方程
template<int SZ>
struct Gauss {
    bitset<SZ + 10> mat[SZ + 10];

    // r 为方程个数, c 为未知数个数; 无解返回 -1, 多解返回 自由元个数
    // mat[1 ~ n]: 增广矩阵, c + 1 位置为常数
    const pair<int, bitset<SZ + 10>> gauss(int r, int c) {
        int row = 1;
        for (int col = 1; col <= c; col++) {
            for (int i = row; i <= r; i++) {
                if (mat[i][col] == 0) continue;
                swap(mat[row], mat[i]);
                break;
            }
            if (mat[row][col] == 0) continue;

            for (int i = 1; i <= r; i++) {
                if (i != row && mat[i][col]) mat[i] ^= mat[row];
            }
            row++;
        }

        if (row <= r) {
            for (int i = row; i <= r; i++) {
                if (mat[i][c + 1]) return {-1, {}};
            }
            return {r - row + 1, {}};
        }

        bitset<SZ + 10> res;
        for (int i = 1; i <= r; i++) res[i] = mat[i][c + 1];
        return {0, res};
    }
};
// endregion
