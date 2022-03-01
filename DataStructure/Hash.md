<!--
 * @Author: your name
 * @Date: 2022-02-14 21:55:33
 * @LastEditTime: 2022-03-01 10:51:06
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /algorithm/DataStructure/Hash.md
-->

### 第一个只出现一次的字符

**_ 剑指 Offer 50 _**
在字符串 s 中找出第一个只出现一次的字符。如果没有，返回一个单空格。 s 只包含小写字母。

示例 1:

输入：s = "abaccdeff"
输出：'b'
示例 2:

输入：s = ""
输出：' '

#### 思路

长的并且字符固定的用 hash 来存储出现的次数。先后顺序用队列（数组）记录下来。两者结合

#### 代码

```js
var firstUniqChar = function (s) {
  const cache = {};
  const length = s.length;
  const queue = [];
  for (let i = 0; i < length; i++) {
    // 没有出现过
    if (!cache[s[i]]) {
      cache[s[i]] = 1;
      queue.push(s[i]);
    } else {
      cache[s[i]]++;
    }
  }
  for (let i = 0; i < queue.length; i++) {
    if (cache[queue[i]] === 1) {
      return queue[i];
    }
  }
  return " ";
};
```

### 判定字符是否唯一

**_ 程金 面试题 01.01. _**
实现一个算法，确定一个字符串 s 的所有字符是否全都不同。

示例 1：

输入: s = "leetcode"
输出: false
示例 2：

输入: s = "abc"
输出: true
限制：

0 <= len(s) <= 100
如果你不使用额外的数据结构，会很加分。

#### 思路

hash，由于字符不确定范围，所以使用对象存储

#### 代码

```js
var isUnique = function (astr) {
  let len = astr.length;
  const set = {};
  for (let i = 0; i < len; i++) {
    if (set[astr[i]]) {
      return false;
    } else {
      set[astr[i]] = true;
    }
  }
  return true;
};
```

### 判定是否互为字符重排

**_ 金典 面试题 01.02. _**
给定两个字符串 s1 和 s2，请编写一个程序，确定其中一个字符串的字符重新排列后，能否变成另一个字符串。

示例 1：

输入: s1 = "abc", s2 = "bca"
输出: true
示例 2：

输入: s1 = "abc", s2 = "bad"
输出: false
说明：

0 <= len(s1) <= 100
0 <= len(s2) <= 100

#### 代码

```js
var CheckPermutation = function (s1, s2) {
  const set = {};
  const len1 = s1.length;
  const len2 = s2.length;
  if (len1 !== len2) {
    return false;
  }
  for (let i = 0; i < len1; i++) {
    set[s1[i]] = set[s1[i]] === undefined ? 1 : set[s1[i]] + 1;
  }
  for (let i = 0; i < len2; i++) {
    if (set[s2[i]] === 0 || set[s2[i]] === undefined) {
      return false;
    } else {
      set[s2[i]]--;
    }
  }
  return true;
};
```
