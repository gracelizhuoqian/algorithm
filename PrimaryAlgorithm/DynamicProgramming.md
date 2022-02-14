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

#### 1. 动归解法（只能处理 n<=58 的数）

1. m 是个变量，当 m>n 时，不够剪，有的段长度为 0，乘积为 0
2. m==n 时，乘积最大为 1，每段绳子长度都为 1
3. m< n 才可能产生最大乘积。第一剪和后面的是同子问题，第一剪可能有 n 种可能，剪的长度分别是 i=0 到 n-1,产生的结果是 f(i)\*f(n-i);而 f(i)和 f(n-i)可以继续剪下去；

```js
var cuttingRope = function (n) {
  if (n < 2) {
    return 0;
  }
  if (n === 2) {
    return 1;
  }
  if (n === 3) {
    return 2;
  }
  // 注意这里的值，和单独的结果是不一样的，当n=2时候，如果作为绳子全长，其结果为1；如果作为一段，其值应该为2
  const dp = [0, 1, 2, 3];
  for (let i = 4; i <= n; i++) {
    dp[i] = 0;
    for (let j = 1; j <= i / 2; j++) {
      let temp = dp[j] * dp[i - j];
      if (temp > dp[i]) {
        dp[i] = temp;
      }
    }
  }
  return dp[n];
};
```

#### 2. 贪心算法

n>4 时候，尽可能多割 3，n=4 时候，分成 2\*2，具体原理可用数学归纳法证明。

```js
var integerBreak = function (s) {
  if (s <= 1) {
    return 0;
  }
  if (s === 2) {
    return 1;
  }
  if (s === 3) {
    return 2;
  }
  let temp = 1;
  while (s > 4) {
    temp = (temp * 3) % 1000000007;
    s -= 3;
  }
  if (s === 4) {
    temp *= 4;
  } else {
    temp *= s;
  }
  temp = temp % 1000000007;
  return temp;
};
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
    if (pattern[i] !== "*") {
      if (i === pattern.length - 1 || pattern[i + 1] !== "*") {
        return false;
      }
    }
  }
  return true;
};
const subMatch = (str, pattern, p1, p2) => {
  const sLength = str.length;
  const pLength = pattern.length;
  if (p1 === sLength && p2 === pLength) {
    return true;
  }
  if (p1 === sLength && p2 < pLength) {
    return equalEmpty(pattern, p2);
  }
  if (p1 < sLength && p2 === pLength) {
    return false;
  }
  // 都妹到结尾
  if (str[p1] === pattern[p2]) {
    // 字符相匹配，分两种，后面是不是*
    if (p2 < pLength - 1 && pattern[p2 + 1] === "*") {
      // 可以匹配往下走，也可以不走，也可以不匹配当前
      return (
        subMatch(str, pattern, p1 + 1, p2) ||
        subMatch(str, pattern, p1 + 1, p2 + 2) ||
        // 务必注意字符串可以不继续走的情况
        subMatch(str, pattern, p1, p2 + 2)
      );
    } else {
      return subMatch(str, pattern, p1 + 1, p2 + 1);
    }
  } else {
    // 字符不匹配，当前不是.后面是*
    if (pattern[p2] !== "." && p2 < pLength - 1 && pattern[p2 + 1] === "*") {
      return subMatch(str, pattern, p1, p2 + 2);
    }
    // 字符不匹配，当前不是.后面不是*
    if (pattern[p2] !== "." && (p2 >= pLength - 1 || pattern[p2 + 1] !== "*")) {
      return false;
    }
    // 字符匹配，当前是.后面是*，.*可以匹配任意，也可以不走
    if (pattern[p2] === "." && p2 < pLength - 1 && pattern[p2 + 1] === "*") {
      return (
        subMatch(str, pattern, p1 + 1, p2) ||
        subMatch(str, pattern, p1 + 1, p2 + 2) ||
        // 务必注意字符串可以不继续走的情况
        subMatch(str, pattern, p1, p2 + 2)
      );
    }
    // 字符匹配，当前是.后面不是*
    if (pattern[p2] === "." && (p2 >= pLength - 1 || pattern[p2 + 1] !== "*")) {
      return subMatch(str, pattern, p1 + 1, p2 + 1);
    }
  }
};
const isMatch = (str, pattern) => {
  return subMatch(str, pattern, 0, 0);
};
```

### 最大子数组的和

**_(Offer 42)_**

#### 思路

以【i】结尾的子数组的和的最大值为`s[i]`，则`s[i+1]=Max(n[i+1],s[i]+n[i+1])`，如果`s[i]`是负值，则 `s[i+1]=n[i+1]`，否则为前者。最终结果为`max(s[i])`。

#### 代码

```js
/**
 * @param {number[]} nums
 * @return {number}
 */
var maxSubArray = function (nums) {
  const s = [];
  s[0] = nums[0];
  let sum = s[0];
  for (let i = 1; i < nums.length; i++) {
    s[i] = Math.max(s[i - 1] + nums[i], nums[i]);
  }
  return Math.max(...s);
};

// 内存优化
var maxSubArray = function (nums) {
  const s = [];
  s[0] = nums[0];
  let sum = s[0];
  let pre = sum;
  for (let i = 1; i < nums.length; i++) {
    if (pre < 0) {
      pre = nums[i];
    } else {
      pre = pre + nums[i];
    }
    sum = Math.max(sum, pre);
  }
  return sum;
};
```

### 把数组排成最小的数

输入一个非负整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。

示例 1:
输入: [10,2]
输出: "102"

示例  2:
输入: [3,30,34,5,9]
输出: "3033459"

提示:
0 < nums.length <= 100
说明:
输出结果可能非常大，所以你需要返回一个字符串而不是整数
拼接起来的数字可能会有前导 0，最后结果不需要去掉前导 0

#### 思路

1. 位数相同的情况下，31 和 23，可以组成 3123 或者 2331，第一位小的应该放在前面，从高位到低位逐位比较，较小的放在前面。
2. 位数不同的情况下，分别按照补位的大小判断

#### 代码

```js
var minNumber = function (nums) {
  nums.sort((a, b) => {
    let changeFlag = 1;
    // 固定aa是小字符串
    let aa = String(a);
    let bb = String(b);
    if (aa.length > bb.length) {
      let temp = aa;
      aa = bb;
      bb = temp;
      changeFlag = -1;
    }
    for (let i = 0; i < aa.length; i++) {
      if (aa[i] !== bb[i]) {
        return (aa[i] - bb[i]) * changeFlag;
      }
    }
    // 补位比较
    for (let i = aa.length; i < bb.length + aa.length; i++) {
      // 短在前
      let shortFront = bb[i - aa.length];
      // 长在前
      let longFront;
      if (i >= bb.length) {
        longFront = aa[i - bb.length];
      } else {
        longFront = bb[i];
      }
      if (shortFront !== longFront) {
        return (shortFront - longFront) * changeFlag;
      }
    }
    return changeFlag;
  });
  let result = "";
  nums.forEach((n) => {
    result += n;
  });
  return result;
};
```

### 把数字翻译成字符串

#### 思路

当前数字可翻译的字符串数量是`N[s[L]]`，以首个数字为栗，可以两个一组，也可以分别翻译，取决于能不能小于 26。  
`N[s[L]]=N[s[L-1]]+M[s[0-1]]*N[s[L-2]]`

#### 代码

```js
var translateNum = function (num) {
  if (num < 0) {
    return 0;
  }
  if (num < 10) {
    return 1;
  }
  if (num >= 10 && num < 26) {
    return 2;
  }
  if (num >= 26 && num < 100) {
    return 1;
  }
  let numStr = String(num);
  let frontTwo = parseInt(numStr.substring(0, 2));
  let restNum1 = parseInt(numStr.substring(1));
  let restNum2 = parseInt(numStr.substring(2));
  if (frontTwo < 26) {
    return translateNum(restNum1) + translateNum(restNum2);
  } else {
    return translateNum(restNum1);
  }
};
```

### 礼物的最大价值

```js
// cache[x][y]表示P(x,y)到终点的礼物最大价值
const cache = [];
var maxValue = function (grid) {
  const rows = grid.length;
  if (rows === 0) {
    return 0;
  }
  for (let i = 0; i < rows; i++) {
    cache[i] = [];
    for (let j = 0; j < grid[0].length; j++) {
      cache[i][j] = 0;
    }
  }
  return maxPointValue(grid, 0, 0);
};

const maxPointValue = (grid, x, y) => {
  if (cache[x][y] !== 0) {
    return cache[x][y];
  }
  const rows = grid.length;
  const columns = grid[0].length;
  if (x >= rows || y >= columns) {
    return 0;
  }
  let sum = 0;
  if (x === rows - 1) {
    for (let i = y; i < columns; i++) {
      sum += grid[x][i];
    }
    return sum;
  }
  if (y === columns - 1) {
    for (let i = x; i < rows; i++) {
      sum += grid[i][y];
    }
    return sum;
  }
  sum += grid[x][y];
  // 向右走
  let sum1 = maxPointValue(grid, x + 1, y);
  let sum2 = maxPointValue(grid, x, y + 1);
  cache[x][y] = sum + Math.max(sum1, sum2);
  return cache[x][y];
};
```

### 最长不含重复字符的子字符串

#### 思路

`T(i)=T(i-1)+M(i)`  
`T(i)`表示长度 0 ～ i 的字符串的目标子字符串长度，`M(i)`为 0 或者 1。当字符串`s(0~i-1)`中的末尾的长度为`T(i-1)`的字符串是不包含重复字符且不包含字符`s[i]`时，`M(i)`为 1，否则为 0。

#### 代码

```js
var lengthOfLongestSubstring = function (s) {
  let cache = {};
  if (s.length === 0) {
    return 0;
  }
  let maxLength = 1;
  let flag = true;
  for (let i = 1; i < s.length; i++) {
    for (let j = i; j >= i - maxLength; j--) {
      if (cache[s[j]]) {
        flag = false;
        break;
      } else {
        cache[s[j]] = 1;
      }
    }
    if (flag) {
      maxLength++;
    }
    cache = {};
    flag = true;
  }
  return maxLength;
};
```

### 丑数

#### 思路

dp[i]表示第 i 个丑数，用三个指针 p2，p3 和 p5。p2 表示当计算 dp[n]时候，前面从 i=1 ～ p2-1 个 dp[i]都已经用*2 得到的结果放在了对应的 dp[i~n-1]的位置，因此下一个位置 dp[n
]应该至少是后面一个 dp[p2]*2，或者是已经有 dp[1~p3-1]已经通过乘 3 放在了对应后面的位置，下面就是最小的 dp[p3]乘 3，或者是 dp[p5]乘 5。比如结果最小的是 dp[p2]乘 2，下一个用来进行乘 2 比较的就应该是 dp[p2+1]，因为当前 dp[p2]已经用过了，所以就把 p2+1。

根本原理可以理解成，每个位置 dp[i]都要乘 2，乘 3，乘 5 后安排到后面的位置，只是乘的进度不一样，需要用指针来标记他们的进度，有 p2 个都已经乘过 2，p3 个已经乘过 3，p5 个已经乘过 5。

#### 代码

```js
var nthUglyNumber = function (n) {
  if (n === 1) {
    return 1;
  }
  let p2 = 1;
  let p3 = 1;
  let p5 = 1;
  const dp=[0,1];
  for(let i=2;i<=n;i++){
    dp[i]=Math.min(dp[p2]*2,dp[p3]*3,dp[p5]*5);
    if(dp[i]===dp[p2]*2){
      p2++;
    }
    if(dp[i]===dp[p3]*3){
      p3++;
    }
    if(dp[i]===dp[p5]*5){
      p5++;
    }
  }
  return dp[n];
};
```
