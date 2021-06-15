# 字符串

## 替换类

### 替换空格

**_（剑指 Offer 05）_**
请实现一个函数，把字符串 s 中的每个空格替换成"%20"。

示例 1：

输入：s = "We are happy."
输出："We%20are%20happy."

#### 思路

1. `replace`函数
2. 逐个比较，拼接新的字符串
3. 静态语言中，需要移动字符串到合适的位置，因为插入会导致字符串长度增加；且如果从头开始移动会导致后面的元素被覆盖，因此应该**从后向前移动**。

#### 解法

```js
const replaceSpace = (str) => {
  const strArray = str.split('')
  let spaceCount = 0
  strArray.forEach((s) => {
    if (s === ' ') {
      spaceCount++
    }
  })
  for (let i = strArray.length - 1; i >= 0; i--) {
    if (strArray[i] !== ' ') {
      strArray[i + spaceCount * 2] = strArray[i]
    } else {
      strArray[i + spaceCount * 2] = '0'
      strArray[i + spaceCount * 2 - 1] = '2'
      strArray[i + spaceCount * 2 - 2] = '%'
      spaceCount--
    }
  }
  return strArray.join('')
}
```