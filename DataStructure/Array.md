# 数组

特点：连续的存储结构，查找操作快，插入删除慢

## 重复类

### 数组中重复的数字

**_（剑指 offer 03）_**  
在一个长度为 n 的数组 nums 里的所有数字都在 0 ～ n-1 的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。

输入：[2, 3, 1, 0, 2, 5, 3]  
输出：2 或 3

#### 解法 1:排序

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

#### 解法 2:hash

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

#### 解法 3:索引交换

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

### 寻找重复数

**_（剑指 offer 03-II）/（LeetCode 287）_**  
给定一个包含  n + 1 个整数的数组  nums ，其数字都在 1 到 n  之间（包括 1 和 n），可知至少存在一个重复的整数。

假设 nums 只有 一个重复的整数 ，找出 这个重复的数 。

你设计的解决方案必须不修改数组 nums 且只用常量级 O(1) 的额外空间。

#### 思路

1. 不修改数组，也不使用额外空间，上面一题的三种方案都不可行
2. 注意题目数组中元素个数比数字的范围多一个，可知**因为重复导致了这种溢出**，只有一个重复的数，那么不包含这个数的范围，`m~n`中的数都是有且只有一个，该范围有`m-n+1`个数；否则会含有`m-n+2`个数。因此可以根据给定范围内数字的数量判断重复数字在不在该范围内，迭代过程类似**二分查找**，只是判断依据是数字的数量
3. 上面的问题是不适用这种方法的，因为即使重复也不一定会产生溢出，如`[1,3,3,4,5,6]`,`1~3`范围内有 3 个数字，无法继续判断下去

#### 解题

```js
const getCount = (nums, start, end) => {
  return nums.filter((i) => start <= i && end >= i).length
}
const findDuplicate = (nums) => {
  const len = nums.length
  let mid = null
  let start = 1
  let end = len - 1
  while (start < end) {
    mid = Math.floor((start + end) / 2)
    let leftCount = getCount(nums, start, mid)
    if (leftCount > mid - start + 1) {
      end = mid
    } else {
      // 务必注意二分查找时的几个范围，包括加不加等号，这里是`mid+1`而不是`mid`，否则会死循环
      start = mid + 1
    }
  }
  return start
}
```
