<!--
 * @Author: your name
 * @Date: 2022-02-14 21:55:33
 * @LastEditTime: 2022-02-14 21:57:44
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
