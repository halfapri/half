#zstu4226: Problem D

dp[pos][1<<3][3]:<br>
第一维表示第几位，第二维表示三个鱼塘分别有没有大于limit,第三维表示进位;<br>
如果裸地写大概是O(10^3\*pos\*8\*3),<br>
但是为了能成功骗到仓鼠钱,稍微优化了一下O(300\*pos\*8\*3) (对枚举的部分进行优化)。
