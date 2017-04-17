#include<bits/stdc++.h>
using namespace std;

int main () {
	srand(time(0));
	int CASE = 5;
	char s[4] = {'A', 'C', 'G', 'T'};
	for (int i=0; i<CASE; i++) {
		int n = rand()%10 + 1;
		printf ("%d\n", n);
		for (int j=0; j<n; j++) {
			int mn = rand()%10+1;
			for (int z=0; z<mn; z++) printf ("%c", s[rand()%4]);
			puts ("");
		}
		int mn = rand()%20+1;
		for (int i=0; i<mn; i++) printf ("%c", s[rand()%4]);
		puts ("");
	}
	return 0;
}
