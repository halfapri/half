#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, p;
bool vis[1000];
vector<int> ss;

void fun (int x,int y,int &gcd,int &c)
{
    c=0;
    while (y) {
        c ++;
        int t = x%y;
        x = y;
        y = t;
    }
    gcd = x;
}

int main ()
{
	//freopen ("read.txt", "r", stdin);
	//freopen ("write.txt", "w", stdout);
    int CASE;
    scanf ("%d", &CASE);
    while (CASE --) {
        scanf ("%d%d%d", &n,&m,&p);
        int ans=0;
        for (int i=1, gcd, c, num; i<=m; i++) {
            for (int j=1; j<=i; j++) {
				if (j>n) continue;
                fun (j,i,gcd,c);
				//printf ("(%d,%d):gcd=%d,c=%d\n",j,i,gcd,c);
                num = (n-j)/i + 1;
                ll a0 = (j/gcd)*(i/gcd), dif = (i/gcd)*(i/gcd);
                memset (vis, 0 , sizeof(vis[0])*c);
                int x=a0%c;
                vis[x] = 1;
                ss.clear();
                ss.emplace_back (x);
                while (true) {
                    x = (x+dif)%c;
                    if (vis[x]) break;
                    ss.emplace_back (x);
                    vis[x] = 1;
                }
                int sz = (int)ss.size();
                ll tot = 1ll*a0*num + 1ll*num*(num-1)/2*dif;
				//cout << tot << endl;
				//cout << "now sz=" << sz << endl;
                for (int z=0; z<sz; z++) {
                    int cnt = num/sz + (z<num%sz);
					//cout << cnt << " " << ss[z] << endl;
                    tot -= 1ll*cnt*ss[z];
                }
                tot = tot/c;
				//cout << tot << endl;
                ans = (ans+tot)%p;
            }
        }
        printf ("%d\n", ans);
    }
    return 0;
}
