<!--
 * @Author: your name
 * @Date: 2022-02-10 15:24:51
 * @LastEditTime: 2022-02-28 14:53:26
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /algorithm/DataStructure/String.md
-->

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
  const strArray = str.split("");
  let spaceCount = 0;
  strArray.forEach((s) => {
    if (s === " ") {
      spaceCount++;
    }
  });
  for (let i = strArray.length - 1; i >= 0; i--) {
    if (strArray[i] !== " ") {
      strArray[i + spaceCount * 2] = strArray[i];
    } else {
      strArray[i + spaceCount * 2] = "0";
      strArray[i + spaceCount * 2 - 1] = "2";
      strArray[i + spaceCount * 2 - 2] = "%";
      spaceCount--;
    }
  }
  return strArray.join("");
};
```

### 反转单词顺序

#### 思路

先把多个空格替换成一个的，然后用 split 切分，然后数组 reverse

#### 代码

```js
var reverseWords = function (s) {
  let sNew = s.replace(/(\s)+/g, " ").replace(/(^\s*)|(\s*$)/g, "");
  let sArray = sNew.split(" ");
  sArray.reverse();
  return sArray.join(" ");
};
```

### 左旋转字符串

字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部。请定义一个函数实现字符串左旋转操作的功能。比如，输入字符串"abcdefg"和数字 2，该函数将返回左旋转两位得到的结果"cdefgab"。

#### 思路

两个字符串拼起来，然后从第 k 位开始截取原字符串长度的子串。

#### 代码

```js
var reverseLeftWords = function (s, n) {
  let temp = s + s;
  return temp.substr(n, s.length);
};
```

### 把字符串转换成整数

**_ 剑指 Offer 67. _**
写一个函数 StrToInt，实现把字符串转换成整数这个功能。不能使用 atoi 或者其他类似的库函数。

首先，该函数会根据需要丢弃无用的开头空格字符，直到寻找到第一个非空格的字符为止。

当我们寻找到的第一个非空字符为正或者负号时，则将该符号与之后面尽可能多的连续数字组合起来，作为该整数的正负号；假如第一个非空字符是数字，则直接将其与之后连续的数字字符组合起来，形成整数。

该字符串除了有效的整数部分之后也可能会存在多余的字符，这些字符可以被忽略，它们对于函数不应该造成影响。

注意：假如该字符串中的第一个非空格字符不是一个有效整数字符、字符串为空或字符串仅包含空白字符时，则你的函数不需要进行转换。

在任何情况下，若函数不能进行有效的转换时，请返回 0。

说明：

假设我们的环境只能存储 32 位大小的有符号整数，那么其数值范围为  [−231,  231 − 1]。如果数值超过这个范围，请返回  INT_MAX (231 − 1) 或  INT_MIN (−231) 。

#### 代码

```js
var strToInt = function (str) {
  const MaxValue = Math.pow(2, 31) - 1;
  const MinValue = -Math.pow(2, 31);
  let trimSpaceStr = str.replace(/^(\s)*/g, "");
  if (trimSpaceStr.length === 0 || !/[\+\-0-9]/.test(trimSpaceStr[0])) {
    return 0;
  }
  let flag = 1;
  let index = 0;
  let num = 0;
  if (trimSpaceStr[0] === "-") {
    flag = -1;
    index++;
  }
  if (trimSpaceStr[0] === "+") {
    index++;
  }
  while (index < trimSpaceStr.length && /[0-9]/.test(trimSpaceStr[index])) {
    // 务必注意加括号
    num = num * 10 + (trimSpaceStr[index] - "0");
    if (flag === 1 && num > Math.pow(2, 31) - 1) {
      return MaxValue;
    }
    if (flag === -1 && num > Math.pow(2, 31)) {
      return MinValue;
    }
    index++;
  }
  return num * flag;
};
```
