#hdu5598 GTW likes czf
>给定l , r , g , t (~1e18) ;<br>
>假设我们有一个set< ll >steins , 我们把[l , r]这个区间里的每个给数分别'亦或' g 和 t 后塞到steins里 ,请问steins.size()是多大。<br>

这道题是有故事的，当年zstu仓鼠意外参加了一场BC ,他碰到的一题 D(就是这题) 。好像当时碰巧铭神也来实验室玩 ,zstu仓鼠不会这题 ,然后铭神就把数位dp的模板传给了zstu仓鼠 ,然后仓鼠东搞搞西敲敲就把这类模板传了出来……然后时至今日我终于把这道祖宗题A掉了。
* 设cmp(a,b) 表示 a 和 b 的大小关系:<br>
* 如果a > b , cmp(a,b) = 2　;<br>
* 如果a == b , cmp(a,b) = 1 ;<br>
* 如果a < b , cmp(a,b) = 0 ; <br>
* 设当前枚举的数为 x ;<br>
* 思路就是去判断 tmp(0) = x^g , tmp(1) = x^t 后的数只要有一个落在区间[l , r]上，那么 x 就是一个解;<br>
* dp状态为　dp(pos , cmp(tmp(0) , l) , cmp(tmp(1) , l) , cmp(tmp(0) , r) , cmp(tmp(1) , r)) ;<br>