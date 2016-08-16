syntax on
filetype indent plugin on
set nu
set tabstop=4
set shiftwidth=4
colo slate
set cin
set mouse=a

map <F4> :!g++ -std=c++11 -w -O2 % -o %<<cr>
"map <F5> :!%<<cr> //windows上
map <F5> :!./%<<cr>
"linux上

map <F6> :!javac %<cr>
map <F7> :!java %<<cr>

map <F2> :call SetTitle()<CR>
func SetTitle()
	let l = 0
	let l = l + 1 | call setline(l, '#include <stdio.h>')
	let l = l + 1 | call setline(l, '#include <bitset>')
	let l = l + 1 | call setline(l, '#include <string.h>')
	let l = l + 1 | call setline(l, '#include <stack>')
	let l = l + 1 | call setline(l, '#include <algorithm>')
	let l = l + 1 | call setline(l, '#include <iostream>')
	let l = l + 1 | call setline(l, '#include <set>')
	let l = l + 1 | call setline(l, '#include <map>')
	let l = l + 1 | call setline(l, '#include <math.h>')
	let l = l + 1 | call setline(l, '#include <queue>')
	let l = l + 1 | call setline(l, '#include <complex>')
	let l = l + 1 | call setline(l, '#include <functional>')
	let l = l + 1 | call setline(l, 'using namespace std ;')
	let l = l + 1 | call setline(l, 'typedef long long ll ;')
	let l = l + 1 | call setline(l, 'typedef long double ld ;')
	let l = l + 1 | call setline(l, 'typedef unsigned long long ull ;')
	let l = l + 1 | call setline(l, '#ifdef _WIN32')
	let l = l + 1 | call setline(l, '#define LLD "%I64d"')
	let l = l + 1 | call setline(l, '#else')
	let l = l + 1 | call setline(l, '#define LLD "%lld"')
	let l = l + 1 | call setline(l, '#endif')
	let l = l + 1 | call setline(l, '#define pi (acos(-1.0))')
	let l = l + 1 | call setline(l, '#define fi first')
	let l = l + 1 | call setline(l, '#define se second')
	let l = l + 1 | call setline(l, '#define lson (o<<1),l,mid')
	let l = l + 1 | call setline(l, '#define rson (o<<1|1),mid+1,r')
	let l = l + 1 | call setline(l, '#define MP make_pair')
	let l = l + 1 | call setline(l, '#define sqr(x) ((x)*(x))')
	let l = l + 1 | call setline(l, '#define ALL(v) (v).begin(),(v).end()')
	let l = l + 1 | call setline(l, '#define showtime fprintf(stderr,"time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)')
	let l = l + 1 | call setline(l, 'const double eps = 1e-9 ;')
	let l = l + 1 | call setline(l, 'const int inf = 0x3f3f3f3f ;')
	let l = l + 1 | call setline(l, 'const ll INF = (ll)4e18 ;')
	let l = l + 1 | call setline(l, 'const int MOD=(int)1e9+7,BAS=257,invBAS=70038911;')
	let l = l + 1 | call setline(l, 'inline int sign(double x){return x<-eps?-1:x>eps;}')
	let l = l + 1 | call setline(l, 'inline int clz(int x){return __builtin_clz(x);}')
	let l = l + 1 | call setline(l, 'inline int clz(ll x){return __builtin_clzll(x);}')
	let l = l + 1 | call setline(l, 'inline int lg2(int x){return !x ? -1 : 31-clz(x);}')
	let l = l + 1 | call setline(l, 'inline int lg2(ll x){return !x ? -1 : 63-clz(x);}')
endfunc

