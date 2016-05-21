#百度之星RoundA2 1005 BD String
> S(1)=B<br>
S(2)=BBD<br>
S(3)=BBDBBDD<br>
…<br>
S(n)=S(n−1)+B+reverse(flip(S(n−1))<br>
其中，reverse(s)指将字符串翻转，比如reverse(BBD)=DBB，flip(s)指将字符串中的B替换为D，D替换为B，比如flip(BBD)=DDB。<br>
目前度度熊已经算出了S(2^1000)的内容，但度度熊毕竟只是只熊，一次读不完这么长的字符串。它现在想知道，这个字符串的第L位（从1开始）到第R位，含有的B的个数是多少？<br>
L , R ~ 1e18 <br>

* 观察S(i)，我们很容易发现它的长度是以指数倍增的，然后这个串具有很强的对称性；<br>
* 所以我们只要预处理出所有的在 1e18 范围内的S(i)串的长度；<br>
* 然后利用对称性搜一下就好了，总的复杂度 O(log(1e18) \* log(1e18)) ;<br>


