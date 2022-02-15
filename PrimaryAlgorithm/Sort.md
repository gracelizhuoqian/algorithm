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
  reverseCouple=0;
  mergeSort(nums,0,nums.length-1);
  return reverseCouple;
};
const mergeSort=(nums,start,end)=>{
  if(start===end){
    return [nums[start]];
  }
  const resArray=[];
  let mid=Math.floor((start+end)/2);
  let leftArray=mergeSort(nums,start,mid);
  let rightArray=mergeSort(nums,mid+1,end);
  let pl=0;
  let pr=0;
  while(pl<=leftArray.length&&pr<=rightArray.length){
    if(leftArray[pl]<=rightArray[pr]){
      resArray.push(leftArray[pl]);
      reverseCouple+=pr;
      pl++;
    }else{
      resArray.push(leftArray[pr]);
      pr++;
    }
  }
  while(pl<=leftArray.length){
      resArray.push(leftArray[pl]);
      reverseCouple+=pr;
      pl++;
  }
  while(pr<=rightArray.length){
      resArray.push(leftArray[pr]);
      pr++;
  }
  return resArray;
}
```
