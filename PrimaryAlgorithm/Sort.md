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
    return
  }
  let selectedNum = arr[start]
  // 注意这里需要从下一个开始
  let p1 = start + 1
  let p2 = end
  // p2指向左边比selectedNum小的数，所以需要等号
  while (p1 <= p2) {
    if (arr[p1] < selectedNum) {
      p1++
    } else if (arr[p2] > selectedNum) {
      p2--
    } else {
      // else代表arr[p1] >= selectedNum&&arr[p2] <= selectedNum
      let temp = arr[p1]
      arr[p1] = arr[p2]
      arr[p2] = temp
    }
  }
  arr[start] = arr[p2]
  arr[p2] = selectedNum
  partition(arr, start, p2 - 1)
  partition(arr, p2 + 1, end)
}
function quickSort(arr) {
  partition(arr, 0, arr.length - 1)
  return arr
}
```
