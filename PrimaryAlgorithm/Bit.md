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
  let res = 0
  while (num) {
    res += num % 2
    num = Math.floor(num / 2)
  }
  return res
}
```

#### 优化

位运算比乘除法效率高得多！！！

1. 除法相当于右移操作
2. 取模 2 余数相当于和 1 相与，看看最后一位是否是 1

```js
const transToBinary = (num) => {
  let res = 0
  while (num) {
    res += num & 1
    num = num >> 1
  }
  return res
}
```

缺点： 如果输入一个负数，由于右移操作会连着符号一同复制，所以最终会形成 OxFFFF 死循环。

#### 巧妙

一个数 n-1，会把二进制最右边的 1 变为 0，1 右边的 0 变成 1；n 和 n-1 相与会消除掉 n 的二进制表示中最右边的 1

```js
const countOne = (num) => {
  let count = 0
  while (num) {
    count++
    num = num & (num - 1)
  }
  return count
}
```
