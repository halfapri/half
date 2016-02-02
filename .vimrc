syntax on
filetype indent plugin on
set nu
set tabstop=4
set shiftwidth=4
colo morning
set cin

map <F4> :!g++ -std=c++11 -O2 % -o %<<cr>
"map <F5> :!%<<cr> //windows上
map <F5> :!./%<<cr>
"linux上

map <F3> :!javac %<cr>
map <F2> :!java %<<cr>

map <F6> :!python %<cr>

map <F8> :!ghc -o %< %<cr>
map <F2> :call SetTitle()<CR>
func SetTitle()
	let l = 0
	let l = l + 1 | call setline(l, '#include <bits/stdc++.h>')
	let l = l + 1 | call setline(l, 'using namespace std ;')
	let l = l + 1 | call setline(l, 'typedef long long ll ;')
	let l = l + 1 | call setline(l, 'typedef long double ld ;')
	let l = l + 1 | call setline(l, '#ifdef _WIN32')
	let l = l + 1 | call setline(l, '#define LLD "%I64d"')
	let l = l + 1 | call setline(l, '#else')
	let l = l + 1 | call setline(l, '#define LLD "%lld"')
	let l = l + 1 | call setline(l, '#endif')
	let l = l + 1 | call setline(l, '#define pi (acos(-1.0))')
	let l = l + 1 | call setline(l, '#define F first')
	let l = l + 1 | call setline(l, '#define S second')
	let l = l + 1 | call setline(l, '#define lson (o<<1),l,mid')
	let l = l + 1 | call setline(l, '#define rson (o<<1|1),mid+1,r')
	let l = l + 1 | call setline(l, '#define MP make_pair')
	let l = l + 1 | call setline(l, 'const double eps = 1e-9 ;')
	let l = l + 1 | call setline(l, 'const int inf = 0x3f3f3f3f ;')
	let l = l + 1 | call setline(l, 'const ll INF = (ll)1e18 ;')
endfunc
