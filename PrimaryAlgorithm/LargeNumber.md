# 大数问题

### 打印从 1 到最大的 n 位数

**_(剑指 offer 17)_**

输入数字 n，按顺序打印出从 1 到最大的 n 位十进制数。比如输入 3，则打印出 1、2、3 一直到最大的 3 位数 999。

示例 1:

输入: n = 1
输出: [1,2,3,4,5,6,7,8,9]

说明：
n 为正整数

#### 思考

1. n 可能超过数字的范围，应该考虑大数问题，用字符数组代替数字
2. 考虑进位问题，何时到达最后一个数字
3. 前面的 0 不要打印出来

#### 实现 1. 用字符数组模拟数字加法

```js
const increment = (num, n) => {
  // num[n-1]表示个位 否则打印时候不方便
  let overflow = false
  let overtake = 0
  let temp = 0
  for (let i = n - 1; i >= 0; i--) {
    // 要在这里就加进位
    temp = num[i] - '0' + overtake
    if (i === n - 1) {
      temp++
    }
    if (temp >= 10) {
      // 当前位溢出了
      if (i === 0) {
        // 是最后一位，应该终止打印
        overflow = true
      } else {
        // 是中间的位
        num[i] = temp - 10 + ''
        overtake = 1
      }
    } else {
      num[i] = temp + ''
      overtake = 0
    }
  }
  return overflow
}
const printNum = (num) => {
  return num.join('').replace(/^0*/, '')
}
const printNumbers = function (n) {
  if (n <= 0) {
    return []
  }
  const numArray = []
  const printArray = []
  for (let i = 0; i < n; i++) {
    numArray[i] = '0'
  }
  while (!increment(numArray, n)) {
    printArray.push(printNum(numArray))
  }
  return printArray
}
```

#### 实现 2. 全排列

见回溯（Backtracking）部分
