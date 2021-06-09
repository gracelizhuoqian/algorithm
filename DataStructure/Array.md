# 数组

特点：连续的存储结构，查找操作快，插入删除慢

## 数组中重复的数字

**_（剑指 offer 03）_**  
在一个长度为 n 的数组 nums 里的所有数字都在 0 ～ n-1 的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。

输入：[2, 3, 1, 0, 2, 5, 3]  
输出：2 或 3

### 解法 1:排序

缺点：时间复杂度`O(n)`

```js
function findDuplicate(arr) {
  const len = arr.length
  if (!len) {
    return null
  }
  arr.sort((a, b) => {
    return a - b
  })
  for (let i = 1; i < len; i++) {
    if (arr[i] === arr[i - 1]) {
      return arr[i]
    }
  }
}
```

### 解法 2:hash

缺点：空间复杂度`O(n)`

```js
function findDuplicate(arr) {
  const hash = {}
  const len = arr.length
  for (let i = 0; i < len; i++) {
    if (hash[arr[i]] === undefined) {
      hash[arr[i]] = 1
    } else {
      return arr[i]
    }
  }
  return null
}
```

### 解法 3:索引交换

利用题目条件，数字范围在`0~n-1`，索引下标和数字应该一一对应，把数字放在对应的位置，一定有数字不能对应索引，在交换的过程中就能发现一个索引对应了两个数字。  
时间复杂度`O(n)`，空间复杂度`O(1)`

```js
function findDuplicate(arr) {
  const len = arr.length
  for (let i = 0; i < len; i++) {
    if (arr[i] !== i) {
      // 当前数字和索引不等，找到它本来应该的位置arr[i]
      let temp = arr[arr[i]]
      // 本来的位置的数字和位置对应，说明重复了
      if (temp === arr[i]) {
        return arr[i]
      } else {
        // 否则交换当前数字到正确的位置
        arr[arr[i]] = arr[i]
        arr[i] = temp
        // 需要重新审视当前位置
        i--
      }
    }
  }
  return null
}
```
