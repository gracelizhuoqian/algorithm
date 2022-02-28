<!--
 * @Author: your name
 * @Date: 2021-09-03 11:50:05
 * @LastEditTime: 2022-02-28 11:08:24
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /algorithm/Mathematics/Calculation.md
-->

## 统计&运算

### 1~n 整数中 1 出现的次数

**_(Offer 43)_**

#### 思路

任意数字`n`，第`i`（从 0 开始）位的位置设为`n[i]`，则它的高位为`n/(10^(i+1))`，数字里面有`n/(10^(i+1))`个`10^(i+1)`，每个`10^(i+1)`里面有`10^i`个 1 出现在当前位置，比如 10000 里面有十个 1000，千位的 1 出现了一千次，从 1000-1999；如果`n[i]=0`，则余下的低位没有 1 出现了；如果`n[i]=1`，则余下的低位 1 出现`n%(10^(i+1))`次；如果`n[i]>1`，则余下的低位 1 出现`10^(i+1)`次。

#### 代码

```js
var countDigitOne = function (n) {
  let origin = n;
  let i = 0;
  let count = 0;
  let current = 0;
  while (n) {
    count += Math.floor(origin / Math.pow(10, i + 1)) * Math.pow(10, i);
    current = n % 10;
    if (current === 0) {
      count += 0;
    } else if (current === 1) {
      count += origin % Math.pow(10, i);
    } else {
      count += Math.pow(10, i);
    }
    n = Math.floor(n / 10);
    i++;
    if (i === 0 && origin % 10 > 0) {
      count++;
    }
  }
  return count;
};
```

### 数字序列中某一位的数字

**_(Offer 44)_**
数字以 0123456789101112131415…的格式序列化到一个字符序列中。在这个序列中，第 5 位（从下标 0 开始计数）是 5，第 13 位是 1，第 19 位是 4，等等。

请写一个函数，求任意第 n 位对应的数字。

#### 思路

相当于分段函数，0-9 对应了 0-9 位，10-99 对应每个两位，边计算边界边与 n 比较，从而确定要定位的数字所在的区间（位数），然后根据计算公式进行倒推。

#### 代码

```js
var findNthDigit = function (n) {
  let bitCount = 1;
  let border = 9;
  let preBorder = 0;
  while (border < n) {
    preBorder = border;
    bitCount++;
    border += 9 * Math.pow(10, bitCount - 1) * bitCount;
  }
  // 当前的数字
  let num =
    Math.ceil((n - preBorder) / bitCount) + Math.pow(10, bitCount - 1) - 1;
  // 数字的第几位，余0是个位，需要特殊处理，其他余1是最高位开始
  let mod = (n - preBorder) % bitCount;
  if (mod == 0) {
    mod = bitCount;
  }
  mod = bitCount - mod;
  while (mod) {
    num = Math.floor(num / 10);
    mod--;
  }
  return num % 10;
};
```

### 圆圈中最后剩下的数字

**_ 剑指 Offer 62 _**
0,1,···,n-1 这 n 个数字排成一个圆圈，从数字 0 开始，每次从这个圆圈里删除第 m 个数字（删除后从下一个数字开始计数）。求出这个圆圈里剩下的最后一个数字。

例如，0、1、2、3、4 这 5 个数字组成一个圆圈，从数字 0 开始每次删除第 3 个数字，则删除的前 4 个数字依次是 2、0、4、1，因此最后剩下的数字是 3。

示例 1：

输入: n = 5, m = 3
输出: 3
示例 2：

输入: n = 10, m = 17
输出: 2

#### 思路

约瑟夫环：
最后剩下的数字是 3。

然后我们从最后剩下的 3 倒着看，我们可以反向推出这个数字在之前每个轮次的位置。

最后剩下的 3 的下标是 0。

第四轮反推，补上 mm 个位置，然后模上当时的数组大小 22，位置是(0 + 3) % 2 = 1。

第三轮反推，补上 mm 个位置，然后模上当时的数组大小 33，位置是(1 + 3) % 3 = 1。

第二轮反推，补上 mm 个位置，然后模上当时的数组大小 44，位置是(1 + 3) % 4 = 0。

第一轮反推，补上 mm 个位置，然后模上当时的数组大小 55，位置是(0 + 3) % 5 = 3。

所以最终剩下的数字的下标就是 3。因为数组是从 0 开始的，所以最终的答案就是 3。

总结一下反推的过程，就是 (当前 index + m) % 上一轮剩余数字的个数。

#### 代码

```js
// 超时解法
var lastRemaining = function (n, m) {
  const nums = [];
  for (let i = 0; i < n; i++) {
    nums[i] = i;
  }
  let k = 1;
  let index = 0;
  let t = m % n;
  while (nums.length > 1) {
    if (k === t) {
      nums.splice(index, 1);
      k = 0;
      index--;
      if (m > nums.length) {
        t = m % nums.length;
      }
      // 注意这里
      if (index < 0) {
        index = nums.length - 1;
      }
    } else {
      k++;
      index++;
      if (index === nums.length) {
        index = 0;
      }
    }
  }
  return nums[0];
};
var lastRemaining = function (n, m) {
  const nums = [];
  for (let i = 0; i < n; i++) {
    nums[i] = i;
  }
  let index = -1;
  let t = m % n;
  for (let i = 0; i < n - 1; i++) {
    let deleteItem = (index + m) % nums.length;
    nums.splice(deleteItem, 1);
    index = deleteItem - 1;
    if (index < 0) {
      index = nums.length - 1;
    }
    if (m > nums.length) {
      t = m % nums.length;
    }
  }
  return nums[0];
};
var lastRemaining = function (n, m) {
  let position = 0;
  for (let i = 2; i <= n; i++) {
    position = (position + m) % i;
  }
  return position;
};
```

### 构建乘积数组

**_ 剑指 Offer 66. _**
给定一个数组 A[0,1,…,n-1]，请构建一个数组 B[0,1,…,n-1]，其中 B[i] 的值是数组 A 中除了下标 i 以外的元素的积, 即 B[i]=A[0]×A[1]×…×A[i-1]×A[i+1]×…×A[n-1]。不能使用除法。

示例:

输入: [1,2,3,4,5]
输出: [120,60,40,30,24]

#### 思路

类似杨辉三角，顺着乘一次，逆着乘一次。

#### 代码

```js
var constructArr = function (a) {
  const len = a.length;
  if (len === 1) {
    return [0];
  }
  if (len === 0) {
    return [];
  }
  const follow = [1];
  for (let i = 1; i < len; i++) {
    follow[i] = a[i - 1] * follow[i - 1];
  }
  const reverse = [];
  reverse[len - 1] = 1;
  for (let i = len - 2; i >= 0; i--) {
    reverse[i] = reverse[i + 1] * a[i + 1];
  }
  for (let i = 0; i < len; i++) {
    follow[i] = follow[i] * reverse[i];
  }
  return follow;
};
```
