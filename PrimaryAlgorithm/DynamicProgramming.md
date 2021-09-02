# 动态规划

## 思路

1. 求最值
2. 大问题分解成子问题
3. 子问题结论推大问题结论

### 剪绳子

**_(剑指 offer 14)_**

给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n 都是整数，n>1 并且 m>1），每段绳子的长度记为 k[0],k[1]...k[m-1] 。请问 k[0]_k[1]_...\*k[m-1] 可能的最大乘积是多少？例如，当绳子的长度是 8 时，我们把它剪成长度分别为 2、3、3 的三段，此时得到的最大乘积是 18。

示例 1：

输入: 2
输出: 1
解释: 2 = 1 + 1, 1 × 1 = 1
示例  2:

输入: 10
输出: 36
解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36
提示：

2 <= n <= 58

#### 分析

1. m 是个变量，当 m>n 时，不够剪，有的段长度为 0，乘积为 0
2. m==n 时，乘积最大为 1，每段绳子长度都为 1
3. m< n 才可能产生最大乘积。第一剪和后面的是同子问题，第一剪可能有 n 种可能，剪的长度分别是 i=0 到 n-1,产生的结果是 f(i)\*f(n-i);而 f(i)和 f(n-i)可以继续剪下去；

```js
var cuttingRope = function (n) {
  if (n < 2) {
    return 0
  }
  if (n === 2) {
    return 1
  }
  if (n === 3) {
    return 2
  }
  // 注意这里的值，和单独的结果是不一样的，当n=2时候，如果作为绳子全长，其结果为1；如果作为一段，其值应该为2
  const dp = [0, 1, 2, 3]
  for (let i = 4; i <= n; i++) {
    dp[i] = 0
    for (let j = 1; j <= i / 2; j++) {
      let temp = dp[j] * dp[i - j]
      if (temp > dp[i]) {
        dp[i] = temp
      }
    }
  }
  return dp[n]
}
```

### 正则表达式匹配

**_（剑指 offer 19）/（LeetCode 10）_**
请实现一个函数用来匹配包含'. '和'_'的正则表达式。模式中的字符'.'表示任意一个字符，而'_'表示它前面的字符可以出现任意次（含 0 次）。在本题中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，但与"aa.a"和"ab\*a"均不匹配。

示例 1:

输入:
s = "aa"
p = "a"
输出: false
解释: "a" 无法匹配 "aa" 整个字符串。

#### 思路

两个指针分别指向字符串和模式，当两个对应位置无法以任何形式匹配，失败；当模式结束字符串没有结束，失败；当模式没有结束字符串结束，看剩下的模式是否可以和空匹配；

```js
/**
 * @param {string} s
 * @param {string} p
 * @return {boolean}
 */
const equalEmpty = (pattern, start) => {
  // 任意一个字符后面都有至少一个*
  for (let i = start; i < pattern.length; i++) {
    if (pattern[i] !== '*') {
      if (i === pattern.length - 1 || pattern[i + 1] !== '*') {
        return false
      }
    }
  }
  return true
}
const subMatch = (str, pattern, p1, p2) => {
  const sLength = str.length
  const pLength = pattern.length
  if (p1 === sLength && p2 === pLength) {
    return true
  }
  if (p1 === sLength && p2 < pLength) {
    return equalEmpty(pattern, p2)
  }
  if (p1 < sLength && p2 === pLength) {
    return false
  }
  // 都妹到结尾
  if (str[p1] === pattern[p2]) {
    // 字符相匹配，分两种，后面是不是*
    if (p2 < pLength - 1 && pattern[p2 + 1] === '*') {
      // 可以匹配往下走，也可以不走，也可以不匹配当前
      return (
        subMatch(str, pattern, p1 + 1, p2) ||
        subMatch(str, pattern, p1 + 1, p2 + 2) ||
        // 务必注意字符串可以不继续走的情况
        subMatch(str, pattern, p1, p2 + 2)
      )
    } else {
      return subMatch(str, pattern, p1 + 1, p2 + 1)
    }
  } else {
    // 字符不匹配，当前不是.后面是*
    if (pattern[p2] !== '.' && p2 < pLength - 1 && pattern[p2 + 1] === '*') {
      return subMatch(str, pattern, p1, p2 + 2)
    }
    // 字符不匹配，当前不是.后面不是*
    if (pattern[p2] !== '.' && (p2 >= pLength - 1 || pattern[p2 + 1] !== '*')) {
      return false
    }
    // 字符匹配，当前是.后面是*，.*可以匹配任意，也可以不走
    if (pattern[p2] === '.' && p2 < pLength - 1 && pattern[p2 + 1] === '*') {
      return (
        subMatch(str, pattern, p1 + 1, p2) ||
        subMatch(str, pattern, p1 + 1, p2 + 2) ||
        // 务必注意字符串可以不继续走的情况
        subMatch(str, pattern, p1, p2 + 2)
      )
    }
    // 字符匹配，当前是.后面不是*
    if (pattern[p2] === '.' && (p2 >= pLength - 1 || pattern[p2 + 1] !== '*')) {
      return subMatch(str, pattern, p1 + 1, p2 + 1)
    }
  }
}
const isMatch = (str, pattern) => {
  return subMatch(str, pattern, 0, 0)
}
```


### 最大子数组的和

***(Offer 42)***

#### 思路
以【i】结尾的子数组的和的最大值为`s[i]`，则`s[i+1]=Max(n[i+1],s[i]+n[i+1])`，如果`s[i]`是负值，则 `s[i+1]=n[i+1]`，否则为前者。最终结果为`max(s[i])`。

#### 代码
```js
/**
 * @param {number[]} nums
 * @return {number}
 */
var maxSubArray = function(nums) {
  const s=[];
  s[0]=nums[0];
  let sum=s[0];
  for(let i=1;i<nums.length;i++){
    s[i]=Math.max(s[i-1]+nums[i],nums[i]);
  }
  return Math.max(...s);
};

// 内存优化
var maxSubArray = function(nums) {
  const s=[];
  s[0]=nums[0];
  let sum=s[0];
  let pre=sum;
  for(let i=1;i<nums.length;i++){
    if(pre<0){
      pre=nums[i];
    }else{
      pre=pre+nums[i];
    }
    sum=Math.max(sum,pre);
  }
  return sum;
};
```
