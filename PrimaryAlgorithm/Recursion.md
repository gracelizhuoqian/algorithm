# 递归

### 数值的整数次方

**_（剑指 offer 16）/（LeetCode 50）_**
实现  pow(x, n) ，即计算 x 的 n 次幂函数（即，xn）。不得使用库函数，同时不需要考虑大数问题。

示例 1：

输入：x = 2.00000, n = 10
输出：1024.00000

#### 注意点

1. 输入的合法性和全面性，底数是否为 0，指数的正负
2. 效率，x 的 n 次方，n 为偶数时，相当于 x 的 n/2 次方相乘
3. 位运算，除 2 和取余均可以用右移和与 1 来实现
4. 注意负数的右移操作容易导致死循环

#### 实现

```js
var myPow = function (x, n) {
  // invalid input
  if (x === 0 && n <= 0) {
    return null;
  }
  if (x === 0) {
    return 0;
  }
  if (n === 0) {
    return 1;
  }
  if (n === 1) {
    return x;
  }
  // 如果不在这里处理，-1>>1 还是-1，会导致死循环！！！
  if (n === -1) {
    return 1.0 / x;
  }
  let halfPow = myPow(x, n >> 1);
  let powValue = halfPow * halfPow;
  if (n & 0x1) {
    powValue *= x;
  }
  return powValue;
};
```

### 求 1+2+…+n

**_ 剑指 Offer 64. _**
求 1+2+...+n ，要求不能使用乘除法、for、while、if、else、switch、case 等关键字及条件判断语句（A?B:C）。

示例 1：

输入: n = 3
输出: 6
示例 2：

输入: n = 9
输出: 45

限制：

1 <= n <= 10000

#### 思路

1. 递归代替循环
2. 逻辑运算代替条件判断的终止

#### 代码

```js
var sumNums = function (n) {
  return n && (n += sumNums(n - 1));
};
```
