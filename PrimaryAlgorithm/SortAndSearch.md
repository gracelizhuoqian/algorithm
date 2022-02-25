# 排序

## 经典算法

### 快排

#### 特点

1. 每次都将一个元素放到正确的位置
2. 递归排序正确元素左右子数组

#### 实现

```js
function partition(arr, start, end) {
  if (start >= end) {
    return;
  }
  let selectedNum = arr[start];
  // 注意这里需要从下一个开始
  let p1 = start + 1;
  let p2 = end;
  // p2指向左边比selectedNum小的数，所以需要等号
  while (p1 <= p2) {
    if (arr[p1] < selectedNum) {
      p1++;
    } else if (arr[p2] > selectedNum) {
      p2--;
    } else {
      // else代表arr[p1] >= selectedNum&&arr[p2] <= selectedNum
      let temp = arr[p1];
      arr[p1] = arr[p2];
      arr[p2] = temp;
    }
  }
  arr[start] = arr[p2];
  arr[p2] = selectedNum;
  partition(arr, start, p2 - 1);
  partition(arr, p2 + 1, end);
}
function quickSort(arr) {
  partition(arr, 0, arr.length - 1);
  return arr;
}
```

### 数组中的逆序对

在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组，求出这个数组中的逆序对的总数。

示例 1:

输入: [7,5,6,4]
输出: 5

#### 思路

冒泡排序，没交换一次就正序了一组逆序数对。每次都会产生一个当前轮次最大的数，交换的次数就是由这个数产生的逆序数对，所有的数字都会被轮到。但是双层循环超时了！采用归并排序，lp 每向后移动一次，0 ～ rp-1 都比当前要小，也就是有 rp 个比当前 lp 小的逆序对产生。

#### 代码

```js
// 超时冒泡
var reversePairs = function (nums) {
  let reverseCouple = 0;
  const length = nums.length;
  if (length <= 1) {
    return 0;
  }
  let temp;
  // 循环length-1 次，当后面的数字都排好第一个就自然定了
  for (let i = 1; i < length; i++) {
    for (let j = 1; j <= length - i; j++) {
      let pre = nums[j - 1];
      let cur = nums[j];
      if (pre > cur) {
        temp = nums[j - 1];
        nums[j - 1] = nums[j];
        nums[j] = temp;
        reverseCouple++;
      }
    }
  }
  return reverseCouple;
};

// 归并排序
let reverseCouple;
var reversePairs = function (nums) {
  if (nums.length <= 1) {
    return 0;
  }
  reverseCouple = 0;
  mergeSort(nums, 0, nums.length - 1);
  return reverseCouple;
};
const mergeSort = (nums, start, end) => {
  if (start === end) {
    return [nums[start]];
  }
  const resArray = [];
  let mid = Math.floor((start + end) / 2);
  let leftArray = mergeSort(nums, start, mid);
  let rightArray = mergeSort(nums, mid + 1, end);
  let pl = 0;
  let pr = 0;
  while (pl <= leftArray.length && pr <= rightArray.length) {
    if (leftArray[pl] <= rightArray[pr]) {
      resArray.push(leftArray[pl]);
      reverseCouple += pr;
      pl++;
    } else {
      resArray.push(leftArray[pr]);
      pr++;
    }
  }
  while (pl <= leftArray.length) {
    resArray.push(leftArray[pl]);
    reverseCouple += pr;
    pl++;
  }
  while (pr <= rightArray.length) {
    resArray.push(leftArray[pr]);
    pr++;
  }
  return resArray;
};
```

### 有排序数组中查找数字

求一个数字在有序数组中出现的次数。

#### 思路

二分查找，先找到最大的比该数字小的数的位置。在找到最小的比该数字大的数字的位置。中间即该数字。

#### 代码

```js
var search = function (nums, k) {
  const len = nums.length;
  let count = 0;
  if (len === 0) {
    return count;
  }
  let leftIndex = findMaxSmaller(nums, k);
  let rightIndex = findMinBigger(nums, k);
  return rightIndex - leftIndex - 1;
};
const findMaxSmaller = (nums, k) => {
  let start = 0;
  let end = nums.length - 1;
  while (start <= end) {
    let mid = Math.floor((start + end) / 2);
    if (nums[mid] >= k) {
      end = mid - 1;
    } else {
      start = mid + 1;
    }
  }
  return start - 1;
};
const findMinBigger = (nums, k) => {
  let start = 0;
  let end = nums.length - 1;
  while (start <= end) {
    let mid = Math.floor((start + end) / 2);
    if (nums[mid] > k) {
      end = mid - 1;
    } else {
      start = mid + 1;
    }
  }
  return end + 1;
};
```

### 0~n-1 中缺失的数字

#### 思路

二分区间查找：如果当前[0,n]区间不缺少数字，那么任意一个位置 i 上有 nums[i]=i。如果该区间缺少数字则会导致 nums[i]>i。

#### 代码

```js
// 根据求和来找
var missingNumber = function (nums) {
  let len = nums.length;
  let sum = ((1 + len) * len) / 2;
  for (let i = 0; i < len; i++) {
    sum -= nums[i];
  }
  return sum;
};
// 二分 永远都必须是start=mid+1，end=mid-1，否则会死循环，只有判断条件会改变！！！
var missingNumber = function (nums) {
  let start = 0;
  let end = nums.length - 1;
  while (start <= end) {
    let mid = Math.floor((start + end) / 2);
    if (nums[mid] === mid) {
      start = mid + 1;
    }
    if (nums[mid] > mid) {
      end = mid - 1;
    }
  }
  return end + 1;
};
```

### 扑克牌中的顺子

#### 思路

如果数组中不包括 0，那么组成顺子的 5 个数字只要满足如下要求：

1. 不重复
2. 最大值最小值相差 4  
   如果包括 n 个 0，那么剩余的数字需要满足：
3. 不重复
4. 最大最小值(不包括 0 的！！！)相差[4-n,4]

#### 代码

```js
var isStraight = function (nums) {
  const pokes = [];
  for (let i = 0; i <= 13; i++) {
    pokes[i] = 0;
  }
  let min = 13;
  let max = 0;
  for (let i = 0; i < 5; i++) {
    if (pokes[nums[i]] > 0 && nums[i] !== 0) {
      return false;
    } else {
      pokes[nums[i]]++;
      if (nums[i] > max) {
        max = nums[i];
      }
      if (nums[i] < min && nums[i] !== 0) {
        min = nums[i];
      }
    }
  }
  return max - min >= 4 - pokes[0] && max - min <= 4;
};
```
