# 位运算

### 位 1 的个数

**_(LeetCode 191)/(剑指 Offer 15)_**
请实现一个函数，输入一个整数（以二进制串形式），输出该数二进制表示中 1 的个数。例如，把 9  表示成二进制是 1001，有 2 位是 1。因此，如果输入 9，则该函数输出 2。

示例 1：

输入：00000000000000000000000000001011
输出：3
解释：输入的二进制串 00000000000000000000000000001011  中，共有三位为 '1'。

#### 原版实现

不就是转换二进制的过程嘛

```js
const transToBinary = (num) => {
  let res = 0;
  while (num) {
    res += num % 2;
    num = Math.floor(num / 2);
  }
  return res;
};
```

#### 优化

位运算比乘除法效率高得多！！！

1. 除法相当于右移操作
2. 取模 2 余数相当于和 1 相与，看看最后一位是否是 1

```js
const transToBinary = (num) => {
  let res = 0;
  while (num) {
    res += num & 1;
    num = num >> 1;
  }
  return res;
};
```

缺点： 如果输入一个负数，由于右移操作会连着符号一同复制，所以最终会形成 OxFFFF 死循环。

#### 巧妙

一个数 n-1，会把二进制最右边的 1 变为 0，1 右边的 0 变成 1；n 和 n-1 相与会消除掉 n 的二进制表示中最右边的 1

```js
const countOne = (num) => {
  let count = 0;
  while (num) {
    count++;
    num = num & (num - 1);
  }
  return count;
};
```

### 数组中只出现过一次的数字

一个整型数组 nums 里除两个数字之外，其他数字都出现了两次。请写程序找出这两个只出现一次的数字。要求时间复杂度是 O(n)，空间复杂度是 O(1)。

示例 1：

输入：nums = [4,1,4,6]
输出：[1,6] 或 [6,1]
示例 2：

输入：nums = [1,2,10,4,1,4,3,3]
输出：[2,10] 或 [10,2]
限制：

#### 思路

想到这种重复出现的数字会用到异或，但是两个数字需要怎么解决。妙处在于分成两组：

1. 两个只出现一次的数字分别在两个组
2. 相同的数字在同一组

#### 代码

```js
var singleNumbers = function (nums) {
  // 假设两个数字分别是a，b，所有数字异或后得到a和b的异或xor
  const len = nums.length;
  let xor = 0;
  const xor0 = [];
  const xor1 = [];
  let res1 = 0,
    res2 = 0;
  for (let i = 0; i < len; i++) {
    xor ^= nums[i];
  }
  let bitTarget = 1;
  let p = xor;
  // 找到xor的二进制表达里面第一个为1的位置
  while (p) {
    let modValue = p % 2;
    if (modValue === 1) {
      break;
    } else {
      p = p / 2;
    }
    bitTarget <<= 1;
  }
  // 参与异或的值
  for (let i = 0; i < nums.length; i++) {
    // 这里注意符号优先级
    if ((nums[i] & bitTarget) === 0) {
      xor0.push(nums[i]);
    } else {
      xor1.push(nums[i]);
    }
  }
  for (let i = 0; i < xor1.length; i++) {
    res1 ^= xor1[i];
  }
  for (let i = 0; i < xor0.length; i++) {
    res2 ^= xor0[i];
  }
  return [res1, res2];
};
```

### 数组中数字出现的次数 II

在一个数组 nums 中只有一个数字只出现了一次，其他数字都出现了三次，找出只出现一次的数字。

#### 思路

所有数字都出现三次的话，他们的二进制展开后，任意一个位置的二进制表示的和一定是 3 的倍数。某位置上对 3 取模，如果结果是 0，说明该只出现一次的数字该位置是 0，否则是 1。

#### 代码

```js
var findSingleNumber = function (nums) {
  const len = nums.length;
  if (len === 0) {
    return null;
  }
  if (len === 1) {
    return nums[0];
  }
  const bitCache = [];
  for (let i = 0; i < len; i++) {
    let cur = nums[i];
    let index = 0;
    while (cur) {
      if (bitCache[index] === undefined) {
        bitCache[index] = 0;
      }
      bitCache[index] += cur % 2;
      cur = Math.floor(cur / 2);
      index++;
    }
  }
  const bitLen = bitCache.length;
  let singleNum = 0;
  for (let i = bitLen - 1; i >= 0; i--) {
    let mod = bitCache[i] % 3;
    singleNum = (singleNum << 1) + mod;
  }
  return singleNum;
};
```

### 不用加减乘除做加法\*

**_ 剑指 Offer 65. _**
写一个函数，求两个整数之和，要求在函数体内不得使用 “+”、“-”、“\*”、“/” 四则运算符号。

示例:

输入: a = 1, b = 1
输出: 2

提示：

a, b 均可能是负数或 0
结果不会溢出 32 位整数

#### 思路

二进制位运算，注意计算机中本来就是用补码来存储负数的！！！
`s=a+b=n+c`
用 a[i]和 b[i]表示二进制数的第 i 位置，
则当前位置的和为 `n[i]=a[i]^b[i]`，进位 `c[i+1]=a[i]&b[i]`。  
当 c 为 0 时，s=n。

#### 代码

```js
var add = function (a, b) {
  let c;
  while (b) {
    c = (a & b) << 1;
    a = a ^ b;
    b = c;
  }
  return a;
};
```
