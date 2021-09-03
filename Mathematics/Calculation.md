<!--
 * @Author: your name
 * @Date: 2021-09-03 11:50:05
 * @LastEditTime: 2021-09-03 17:39:28
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /algorithm/Mathematics/Calculation.md
-->
## 统计&运算

### 1~n 整数中 1 出现的次数

***(Offer 43)***

#### 思路

任意数字`n`，第`i`（从0开始）位的位置设为`n[i]`，则它的高位为`n/(10^(i+1))`，数字里面有`n/(10^(i+1))`个`10^(i+1)`，每个`10^(i+1)`里面有`10^i`个1出现在当前位置，比如10000里面有十个1000，千位的1出现了一千次，从1000-1999；如果`n[i]=0`，则余下的低位没有1出现了；如果`n[i]=1`，则余下的低位1出现`n%(10^(i+1))`次；如果`n[i]>1`，则余下的低位1出现`10^(i+1)`次。

#### 代码
```js
var countDigitOne = function(n) {
  let origin=n;
  let i=0;
  let count=0;
  let current=0;
  while(n){
    count+=Math.floor(origin/Math.pow(10,i+1))*Math.pow(10,i);
    current=n%10;
    if(current===0){
      count+=0;
    }else if(current===1){
      count+=origin%Math.pow(10,i);
    }else{
      count+=Math.pow(10,i)
    }
    n=Math.floor(n/10);
    i++;
    if(i===0&&origin%10>0){
      count++;
    }
  }
  return count;
};
```

###  数字序列中某一位的数字
***(Offer 44)***
数字以0123456789101112131415…的格式序列化到一个字符序列中。在这个序列中，第5位（从下标0开始计数）是5，第13位是1，第19位是4，等等。

请写一个函数，求任意第n位对应的数字。

#### 思路

相当于分段函数，0-9对应了0-9位，10-99对应每个两位，边计算边界边与n比较，从而确定要定位的数字所在的区间（位数），然后根据计算公式进行倒推。

#### 代码
```js
var findNthDigit = function(n) {
  let bitCount=1;
  let border=9;
  let preBorder=0;
  while(border<n){
    preBorder=border;
    bitCount++;
    border+=9*Math.pow(10,bitCount-1)*bitCount;
  }
  // 当前的数字
  let num=Math.ceil((n-preBorder)/bitCount)+Math.pow(10,bitCount-1)-1;
  // 数字的第几位，余0是个位，需要特殊处理，其他余1是最高位开始
  let mod=(n-preBorder)%bitCount;
  if(mod==0){
    mod=bitCount;
  }
  mod=bitCount-mod;
  while(mod){
    num=Math.floor(num/10);
    mod--;
  }
  return num%10;
};
```
