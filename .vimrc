syntax on
filetype indent plugin on
set nu
set tabstop=4
set shiftwidth=4
colo evening
set cin

map <F4> :!g++ -std=c++11 -O2 % -o %<<cr>
"map <F5> :!%<<cr> //windows上
map <F5> :!./%<<cr>
"linux上

map <F3> :!javac %<cr>
map <F2> :!java %<<cr>

map <F6> :!python %<cr>

map <F8> :!ghc -o %< %<cr>

