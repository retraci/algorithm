#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;

const LL N = 20 , P = 1e9 + 7;

struct F{
    LL s0 , s1 , s2;
}f[N][10][7][7];

LL power7[N] , power9[N];//10^i%7,10^i%P

LL mod(LL x , LL y)//避免得到负数
{
    return (x % y + y) % y;
}

void init()
{
    //初始化长度是1的情况
    for(int i = 0 ; i < 10 ; i++)
        if(i != 7)
        {
            auto &v = f[1][i][i % 7][i % 7];
            v.s0++;
            v.s1 += i;
            v.s2 += i * i;
        }

    LL p = 10;
    for(int i = 2 ; i < N ; i++ , p *= 10)
        for(int j = 0 ; j < 10 ; j++)
        {
            if(j == 7) continue;
            for(int a = 0 ; a < 7 ; a++)
                for(int b = 0 ; b < 7 ; b++)
                    for(int k = 0 ; k < 10 ; k++)
                    {
                        if(k == 7) continue;
                        auto &v1 = f[i][j][a][b] , &v2 = f[i - 1][k][mod(a - j * mod(p , 7) , 7)][mod(b - j , 7)];
                        //开启痛苦面具，对照上面的公式，时刻提醒记得及时取模！！！！！！
                        v1.s0 = mod(v1.s0 + v2.s0 , P);
                        v1.s1 = mod(v1.s1 + j * (p % P) % P * v2.s0 % P + v2.s1  , P);
                        v1.s2 = mod(v1.s2 +
                                    v2.s0 * j % P * (p % P) % P * j % P * (p % P) % P +
                                    2 * j % P * (p % P) % P * v2.s1 % P +
                                    v2.s2 , P);
                        cout << v1.s0 << " " << v1.s1 << " " << v1.s2 << "\n";
                    }
        }


    power7[0] = power9[0] = 1;
    for(int i = 1 ; i < N ; i++)
    {
        power7[i] = power7[i - 1] * 10 % 7;
        power9[i] = power9[i - 1] * 10 % P;
    }
}

//求出i位，且最高位是j，且本身模7不等于a，且各位数之和模7不等b的集合
//因为预处理的f[i][j][a][b]是本身模7等于a，且各位数之和模7等于b的集合，因此需要两趟for循环来实现
F get(int i , int j , int a , int b)
{
//    cout << i << " " << j << " " << a << " " << b << "\n";
    LL s0 = 0 , s1 = 0 , s2 = 0;
    for(int x = 0 ; x < 7 ; x++)
        for(int y = 0 ; y < 7 ; y++)
        {
            if(x == a || y == b) continue;
            auto v = f[i][j][x][y];
            s0 = mod(s0 + v.s0 , P);
            s1 = mod(s1 + v.s1 , P);
            s2 = mod(s2 + v.s2 , P);
        }

//    cout << s0 << " " << s1 << " " << s2 << "\n";
    return {s0 , s1 , s2};
}

LL dp(LL n)
{
    if(!n) return 0;

    LL backup_n = n % P;//备份一个n
    vector<int> nums;
    while(n) nums.push_back(n % 10) , n /= 10;

    LL res = 0;
    LL last_a = 0 , last_b = 0;//last_a表示前缀本身的值，last_b表示前缀各位数之和
    for(int i = nums.size() - 1 ; i >= 0 ; i--)
    {
        int x = nums[i];
        for(int j = 0 ; j < x ; j++)
        {
            if(j == 7) continue;
            int a = mod(-last_a * power7[i + 1] , 7) , b = mod(-last_b , 7);

            auto v = get(i + 1 , j , a , b);//求得本身模7不等于a，并且各位数之和模7不等b的集合，此时就可以使用预处理出来的结构体
            //根据公式求s2，时刻提醒记得及时取模！！！！！！
            res = mod(res +
                      (last_a % P) * (last_a % P) % P * (power9[i + 1] % P) % P * (power9[i + 1] % P) % P * v.s0 % P +
                      2 * (last_a % P) * (power9[i + 1] % P) % P * v.s1 % P +
                      v.s2 ,
                      P);
        }

        if(x == 7) break;
        last_a = last_a * 10 + x;
        last_b += x;

        //记得特判n本身
        if(!i && last_a % 7 && last_b % 7) res = mod(res + backup_n * backup_n , P);
    }

    return res;
}

int main()
{
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    init();

    int T;
    cin >> T;
    while(T--)
    {
        LL l , r;
        cin >> l >> r;
        cout << mod(dp(r) - dp(l - 1) , P) << endl;
    }
}