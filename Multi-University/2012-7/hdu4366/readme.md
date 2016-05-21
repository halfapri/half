#hdu4366 Successor
>给出一棵树，0号节点为根，每个节点上保存了两个值：loyalty , ability ;<br>
>给出m次询问：每次询问给出一个节点号x , 求出以x为根的子树里节点y , 要保证y.ability > x.ability,并且y.loyalty要最大。<br>
>节点数，m ~ 50000 ； loyalty , ability ~ 1000000 ；所有根的节点号<其子树的节点号;<br>

* 按照ability的值，对所有节点排序，若ability相等，让节点号小的排在前面；<br>
* 然后按排序后的顺序，询问tin(x)~tout(x)这个范围内已经插入的值中loyalty最大的，然后把x节点插入倒tin(x)这个位置（或tout(x)) 即可；
* 其中tin(x) , tout(x)表示节点 x 的 dfs序；