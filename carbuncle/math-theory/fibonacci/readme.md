#Fibonacciの规律
>笔记摘录自：[从蓝桥杯来谈Fibonacci数列](http://blog.csdn.net/acdreamers/article/details/21822165)<br>

##1.&nbsp;<img src="http://latex.codecogs.com/gif.latex? f(n) mod f(m)" />
<img src="http://latex.codecogs.com/gif.latex? f(n+m)=f(n+1)f(m)+f(n)f(m-1)      ----(1)" /> <br>
<img src="http://latex.codecogs.com/gif.latex? f(n)^{2}=(-1)^{n+1}+f(n-1)f(n+1)----(2)" /> <br>
通过(1)易得：<br>
<img src="http://latex.codecogs.com/gif.latex? f(n) mod  f(m) =f(m-1)^{\frac{n}{m}}f(n \% m) mod  f(m)----(3) " /> <br>
由(2)可以看出：<br>
<img src="http://latex.codecogs.com/gif.latex? f(m-1)^{2}mod \ f(m)=(-1)^{m}" /><br>
从而可以进一步简化(3),讨论:<br>
<img src="http://latex.codecogs.com/gif.latex?\textcircled{1}" />当m为偶数 , <img src="http://latex.codecogs.com/gif.latex?\frac{n}{m}" />为偶数时：<br>
<img src="http://latex.codecogs.com/gif.latex?\ f(n) mod \ f(m)=f(n \% m)" /><br>
<img src="http://latex.codecogs.com/gif.latex?\textcircled{2}" />当m为偶数 , <img src="http://latex.codecogs.com/gif.latex?\frac{n}{m}" />为奇数时：<br>
<img src="http://latex.codecogs.com/gif.latex?\ f(n) mod \ f(m)=f(m-1)f(n \% m)mod \ f(m)" /><br>
<img src="http://latex.codecogs.com/gif.latex?\textcircled{3}" />当m为奇数 , 
<img src="http://latex.codecogs.com/gif.latex?\frac{n}{m}" />为偶数，
<img src="http://latex.codecogs.com/gif.latex?\frac{n}{2m}" />为偶数时：<br>
<img src="http://latex.codecogs.com/gif.latex?\ f(n) mod \ f(m)=f(n \% m)" /><br>
<img src="http://latex.codecogs.com/gif.latex?\textcircled{4}" />当m为奇数 , 
<img src="http://latex.codecogs.com/gif.latex?\frac{n}{m}" />为偶数，
<img src="http://latex.codecogs.com/gif.latex?\frac{n}{2m}" />为奇数时：<br>
<img src="http://latex.codecogs.com/gif.latex?\ f(n) mod \ f(m)=f(m)-f(n \% m)" /><br>
<img src="http://latex.codecogs.com/gif.latex?\textcircled{5}" />当m为奇数 , 
<img src="http://latex.codecogs.com/gif.latex?\frac{n}{m}" />为奇数，
<img src="http://latex.codecogs.com/gif.latex?\frac{n}{2m}" />为偶数时：<br>
<img src="http://latex.codecogs.com/gif.latex?\ f(n) mod \ f(m)=f(m-1)f(n \% m) mod \ f(m)" /><br>
<img src="http://latex.codecogs.com/gif.latex?\textcircled{6}" />当m为奇数 , 
<img src="http://latex.codecogs.com/gif.latex?\frac{n}{m}" />为奇数，
<img src="http://latex.codecogs.com/gif.latex?\frac{n}{2m}" />为奇数时：<br>
<img src="http://latex.codecogs.com/gif.latex?\ f(n) mod \ f(m)=f(m)-f(m-1)f(n \% m) mod \ f(m)" /><br>
<br>
到这里后，必须要简化的只剩下<br>
<img src="http://latex.codecogs.com/gif.latex?\ f(m-1)f(n \% m) mod \ f(m)" />：<br>
因此我们还要再引入一个性质：<br>
若<img src="http://latex.codecogs.com/gif.latex?n\geq&space;1,r\geq&space;2" />,那么有<br>
<img src="http://latex.codecogs.com/gif.latex?f(a)f(a&plus;r-1)-f(a&plus;1)f(a&plus;r-2)=(-1)^{a&plus;1}f(r-2)" /><br>
我们令<img src="http://latex.codecogs.com/gif.latex?k=n\%m" />,再令<br>
<img src="http://latex.codecogs.com/gif.latex?k=a&plus;1,m-1=a&plus;r-2," />得到：<br>
<img src="http://latex.codecogs.com/gif.latex?f(m-1)f(k)-f(m)f(k-1)=(-1)^{k&plus;1}f(m-k)" /><br>
显然进一步化简后：<br>
<img src="http://latex.codecogs.com/gif.latex?f(m-1)f(n\%m)mod \ f(m)&space;=&space;(-1)^{n \% m&plus;1}f(m-n \% m)" /> ：<br>
所以当<img src="http://latex.codecogs.com/gif.latex?n \% m" />为偶数时,
<img src="http://latex.codecogs.com/gif.latex?f(m-1)f(n\%m)mod \ f(m)&space;=&space;f(m)-f(m-n \% m)" />;<br>
为奇数时，<img src="http://latex.codecogs.com/gif.latex?f(m-1)f(n\%m)mod \ f(m)&space;=&space;f(m-n \% m) " />。<br>
<br>
##2.<img src="http://latex.codecogs.com/gif.latex?\sum_{i=1}^{n}f(i)=f(n&plus;2)-1" />
把每一项展开成<img src="http://latex.codecogs.com/gif.latex?f(i)=f(i&plus;1)-f(i-1)" />即可得到<br>
<img src="http://latex.codecogs.com/gif.latex?\frac{\partial J}{\partial \theta_k^{(j)}}=\sum_{i:r(i,j)=1}{\big((\theta^{(j)})^Tx^{(i)}-y^{(i,j)}\big)x_k^{(i)}}+\lambda \theta_k^{(j)}" />
<img src="http://latex.codecogs.com/gif.latex?\[\sum_{i}^{n}\]" />






