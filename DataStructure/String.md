<!--
 * @Author: your name
 * @Date: 2022-02-10 15:24:51
 * @LastEditTime: 2022-02-18 11:10:02
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
### 反转单词顺序

#### 思路
先把多个空格替换成一个的，然后用split切分，然后数组reverse

#### 代码
```js
var reverseWords = function(s) {
  let sNew=s.replace(/(\s)+/g,' ').replace(/(^\s*)|(\s*$)/g,'');
  let sArray=sNew.split(' ');
  sArray.reverse();
  return sArray.join(' ');
};
```

### 左旋转字符串
字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部。请定义一个函数实现字符串左旋转操作的功能。比如，输入字符串"abcdefg"和数字2，该函数将返回左旋转两位得到的结果"cdefgab"。

#### 思路
两个字符串拼起来，然后从第k位开始截取原字符串长度的子串。

#### 代码
```js
var reverseLeftWords = function(s, n) {
  let temp=s+s;
  return temp.substr(n,s.length);
};
```