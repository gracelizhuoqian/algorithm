# 有效性检验

### 表示数值的字符串\*

**_（剑指 Offer 20）_**

请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。  
数值（按顺序）可以分成以下几个部分：

若干空格  
一个 小数 或者 整数  
（可选）一个 'e' 或 'E' ，后面跟着一个 整数  
若干空格

#### 思路

1. 除空格外，有效数值的模式为 `A[.[B]][e|EC]`或者`.B[e|EC]`，之所以是`A[.[B]]`是因为形如`2.`也是有效的
2. A 和 C 的形式一致，可以有符号`+/-`；
3. B 前面不允许有符号

```js
let index = 0
const scanUnsignedInt = (str) => {
  while (/[0-9]/.test(str[index])) {
    index++
  }
  return p > index
}
const scanSignedInt = (str) => {
  if (str[index] === '+' || str[index] === '-') {
    index++
  }
  return scanUnsignedInt(str)
}
const isNumber = function (s) {
  // 去掉首位空字符
  index = 0
  s = s.replace(/^\s*/, '').replace(/\s*$/, '')
  // 空字符串
  if (!s) {
    return false
  }
  let isNumber = scanSignedInt(s)
  let pointSection = true
  let eSection = true
  // 可以有的 小数部分
  if (s[index] === '.') {
    index++
    // 小数点左右只要有至少一个数字就可以
    isNumber = scanUnsignedInt(s) || isNumber
  }
  // 可以有的 指数部分
  if (s[index] === 'e' || s[index] === 'E') {
    index++
    isNumber = scanSignedInt(s) && isNumber
  }
  return isNumber && index === s.length
}
```
