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

**_(LeetCode 219)_**
给定一个整数数组和一个整数  k，判断数组中**是否存在**两个不同的索引  i  和  j，使得  nums [i] = nums [j]，并且 i 和 j  的差的 绝对值 至多为 k。
输入: nums = [1,2,3,1], k = 3
输出: true

1. 变形,需要记录索引
2. 不是所有都要满足，而是只要有一对索引满足即可

```js
function findDuplicate(arr, k) {
  const hash = {}
  const len = arr.length
  for (let i = 0; i < len; i++) {
    if (hash[arr[i]] === undefined) {
      hash[arr[i]] = [i]
    } else {
      hash[arr[i]].push(i)
    }
  }
  let res = false
  // 注意forEach的返回不是函数的返回
  Object.keys(hash).forEach((num) => {
    let len = hash[num].length
    if (len > 1) {
      for (let i = 1; i < len; i++) {
        if (hash[num][i] - hash[num][i - 1] <= k) {
          res = true
        }
      }
    }
  })
  return res
}
```

#### 解法 3:索引交换

利用题目条件，数字范围在`0~n-1`，索引下标和数字应该一一对应，把数字放在对应的位置，一定有数字不能对应索引，在交换的过程中就能发现一个索引对应了两个数字。
时间复杂度`O(n)`，空间复杂度`O(1)`

相同解法 **_（LeetCode 442）_**

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

### 删除有序数组中的重复项

**_（LeetCode 26）_**
给你一个有序数组 nums ，请你 原地 删除重复出现的元素，使每个元素 只出现一次 ，返回删除后数组的新长度。

不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。

输入：nums = [1,1,2]
输出：2, nums = [1,2]
解释：函数应该返回新的长度 2 ，并且原数组 nums 的前两个元素被修改为 1, 2 。不需要考虑数组中超出新长度后面的元素。

#### 解法 1:单指针

总是比较当前元素和前一个元素，如果相等，则删除当前元素，指针后移

```js
const deleteRepeatNumber = (nums) => {
  const len = nums.length
  if (len <= 1) {
    return len
  }
  let p = 1
  // nums.length会动态变化
  while (p < nums.length) {
    if (nums[p] === nums[p - 1]) {
      nums.splice(p, 1)
    } else {
      p++
    }
  }
  return nums.length
}
```

#### 解法 2:双指针

慢指针指向更新的元素，每次移动都意味着有不同的元素填在了当前位置，快指针向前寻找下一个不重复的元素。

```js
const deleteRepeatNumber = (nums) => {
  const len = nums.length
  let slow = 0
  let fast = 1
  while (fast < len) {
    if (nums[slow] !== nums[fast]) {
      //fast指向了新的不同元素
      slow++
      nums[slow] = nums[fast]
    }
    // 无论fast是不是要更新的元素，都要向后移动
    fast++
  }
  // slow是最后一个元素的索引，长度要加1
  return slow + 1
}
```

### 删除有序数组中的重复项 II

**_（LeetCode 80）_**
给你一个有序数组 nums ，请你 原地 删除重复出现的元素，使每个元素 最多出现两次 ，返回删除后数组的新长度。

不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。
输入：nums = [1,1,1,2,2,3]
输出：5, nums = [1,1,2,2,3]
解释：函数应返回新长度 length = 5, 并且原数组的前五个元素被修改为 1, 1, 2, 2, 3 。 不需要考虑数组中超出新长度后面的元素。

#### 1. 单指针

需要设置一个标记变量，标记当前元素是否已经重复出现了，默认为`false`，当出现一次时为`true`不进行操作，后面继续遇到重复元素并且状态为`true`时则可以进行删除

扩展：如果元素最多出现次数为`n`，则状态变量设置为整型，当值增加到`n-1`后遇到重复元素进行删除

```js
const deleteRepeatNumber = (nums) => {
  const len = nums.length
  if (len <= 2) {
    return len
  }
  let hasOneRepeat = false
  let p = 1
  // 判断条件这里务必注意，随着splice操作，数组长度会更改
  while (p < nums.length) {
    if (nums[p] !== nums[p - 1]) {
      hasOneRepeat = false
      p++
    } else {
      if (!hasOneRepeat) {
        // 第一次重复
        hasOneRepeat = true
        p++
      } else {
        // 不是第一次重复了
        nums.splice(p, 1)
      }
    }
  }
  return nums.length
}
```

#### 2.双指针

没啥特别的，移动慢指针时候，再多判断一次，如果后面元素相同则再向后移动一个

```js
const deleteRepeatNumber = (nums) => {
  const len = nums.length
  if (len <= 2) {
    return len
  }
  let slow = 0
  let fast = 1
  // 注意这里，需要让fast指向第一个不同的元素
  while (fast < len && nums[fast] === nums[slow]) {
    fast++
  }
  // 如果第一个元素就有重复，需要slow后移
  if (fast > 1) {
    slow++
    nums[slow] = nums[slow - 1]
  }
  while (fast < len) {
    if (nums[fast] !== nums[slow]) {
      slow++
      nums[slow] = nums[fast]
      if (fast < len - 1 && nums[fast] === nums[fast + 1]) {
        slow++
        nums[slow] = nums[slow - 1]
        fast++
      }
    }
    fast++
  }
  return slow + 1
}
```


### 数组中超过一半的数字
**_（offer 39）/(LeetCode 169)_**
#### 思路
**相同加，不同减**
每出现一次该数字，该数字出现次数加1，不是该数字就减1。减到0就换数字。该数字超过一半的话，最终次数是正的。
#### 解法
```js
const majorityElement=(numArray)=>{
  let len=numArray.length;
  let count=1;
  let cur=numArray[0];
  for(let i=1;i<len;i++){
    if(count===0){
      cur=numArray[i];
      count++;
    }else{
      if(numArray[i]===cur){
        count++;
      }else{
        count--;
      }
    }
  }
  return cur;
}
```
## 二维数组

### 二维数组中的查找

**_（剑指 offer 03）/(LeetCode 240. 搜索二维矩阵 II)_**

编写一个高效的算法来搜索  m x n  矩阵 matrix 中的一个目标值 target 。该矩阵具有以下特性：

每行的元素从左到右升序排列。
每列的元素从上到下升序排列。

输入：matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
输出：false

#### 解法 1.二分查找

一维的二分查找是以中间值线性分为两个部分，分别是有序的。
二维的二分查找可以以中间分成四个部分，左上，右上，左下，右下，每个子数组可以递归查找。
二维数组的特征是有数的范围，左上角是最小，右下角是最大。不在这个范围直接返回。

```js
// 在任意子二维数组中查找
var searchBinary = function (
  matrix,
  target,
  rowStart,
  rowEnd,
  colStart,
  colEnd
) {
  let r = matrix.length
  let c = matrix[0].length
  // 超出范围
  if (rowStart < 0 || rowEnd >= r || colStart < 0 || colEnd >= c) {
    return false
  }
  // 直接等于左上角的最小值（右下角的最大值）
  if (
    matrix[rowStart][colStart] === target ||
    matrix[rowEnd][colEnd] === target
  ) {
    return true
    // 不在[min,max]中
  } else if (
    matrix[rowStart][colStart] > target ||
    matrix[rowEnd][colEnd] < target
  ) {
    return false
  } else {
    // 在(min,max)范围内
    // 子数组变成了一维数组，直接换成普通的二分查找
    if (rowStart === rowEnd) {
      let i = colStart
      let j = colEnd
      while (i <= j && i >= 0 && j >= 0 && i <= colEnd && j <= colEnd) {
        let mid = Math.floor((i + j) / 2)
        if (matrix[rowStart][mid] === target) {
          return true
        } else if (matrix[rowStart][mid] > target) {
          j = mid - 1
        } else {
          i = mid + 1
        }
      }
      return false
    }
    if (colStart === colEnd) {
      let i = rowStart
      let j = rowEnd
      while (i <= j && i >= 0 && j >= 0 && i <= rowEnd && j <= rowEnd) {
        let mid = Math.floor((i + j) / 2)
        if (matrix[mid][colStart] === target) {
          return true
        } else if (matrix[mid][colStart] > target) {
          j = mid - 1
        } else {
          i = mid + 1
        }
      }
      return false
    }
    // 递归查找四个子数组
    if (rowStart !== rowEnd && colStart !== colEnd) {
      let rowMid = Math.floor((rowStart + rowEnd) / 2)
      let colMid = Math.floor((colStart + colEnd) / 2)
      return (
        searchBinary(matrix, target, rowStart, rowMid, colStart, colMid) ||
        searchBinary(matrix, target, rowStart, rowMid, colMid + 1, colEnd) ||
        searchBinary(matrix, target, rowMid + 1, rowEnd, colStart, colMid) ||
        searchBinary(matrix, target, rowMid + 1, rowEnd, colMid + 1, colEnd)
      )
    }
  }
  // return false
}
var searchMatrix = function (matrix, target) {
  let rows = matrix.length
  let cols = matrix[0].length
  return searchBinary(matrix, target, 0, rows - 1, 0, cols - 1)
}
```

#### 解法 2.渐进筛选

以左下角或者右上角开始进行判断，小于右上角，则排除右上角所在列；大于右上角，则排除所在行。
直到变成一维数组。

```js
// 存储下当前所在筛选数组的右上角的位置
const searchMatrix = function (matrix, target) {
  const rows = matrix.length
  const cols = matrix[0].length
  let row = 0
  let col = cols - 1
  while (row < rows && col >= 0) {
    if (matrix[row][col] === target) {
      return true
    } else if (matrix[row][col] < target) {
      // 排除所在行
      row++
    } else {
      // 排除所在列
      col--
    }
  }
  return false
}
```

