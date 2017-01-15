#include<bits/stdc++.h>
using namespace std;
void exgcd (int a,int b,int &gcd,int &x,int &y) {
	if (b==0) {gcd=a;x=1;y=0; return;}
	exgcd (b,a%b,gcd,y,x);
	y-=a/b*x;
}

int main () {
	int n, mod;
	scanf("%d%d", &n,&mod); //求n关于mod的逆元
	int gcd,x,y;
	exgcd (n,mod,gcd,x,y);
	if (gcd!=1) puts ("no inv");
	else printf ("%d\n", (x+mod)%mod);
	return 0;
}
