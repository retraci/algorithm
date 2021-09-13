#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

template<typename T> inline void rd(T& x){
    T ret = 0, sgn = 1;
    char c = getchar();
    while(!isdigit(c)) sgn = (c == '-' ? -1 : 1), c = getchar();
    while(isdigit(c)) ret = (ret << 3) + (ret << 1) + c - '0', c = getchar();
    x = (sgn == -1 ? -ret : ret);
}
