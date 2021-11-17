// POJ 2311 Cutting Game
/*
	Ë¼Â·£º
	GrundyÊı
*/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <set>

using namespace std;

const int max_HW = 210;

int w, h;
int status[max_HW][max_HW];

int Grundy(int w, int h) {
	if(status[w][h] != -1) return status[w][h];

	set<int> s;
	for(int i = 2; i <= w-2; i++) s.insert(Grundy(i, h) ^ Grundy(w-i, h));
	for(int i = 2; i <= h-2; i++) s.insert(Grundy(w, i) ^ Grundy(w, h-i));

	int res = 0;
	while(s.count(res)) res++;
	return status[w][h] = res;
}

int main() {
	memset(status, -1, sizeof(status));
	while(~scanf("%d%d", &w, &h)) {
		if(Grundy(w, h)) puts("WIN");
		else puts("LOSE");
	}

	return 0;
}
