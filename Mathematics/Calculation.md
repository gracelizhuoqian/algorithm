<!--
 * @Author: your name
 * @Date: 2021-09-03 11:50:05
 * @LastEditTime: 2021-09-03 12:47:15
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /algorithm/Mathematics/Calculation.md
-->
## 统计&运算

### 1~n 整数中 1 出现的次数

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
