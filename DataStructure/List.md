# 链表

### 逆序打印链表

```js
const subPrint = (arr, head) => {
  if (!head) {
    return
  }
  subPrint(arr, head.next)
  arr.push(head.val)
}
var reversePrint = function (head) {
  const res = []
  subPrint(res, head)
  return res
}
```

### 删除链表的节点

**_（剑指 offer 18-1）_**
给定单向链表的头指针和一个要删除的节点的值，定义一个函数删除该节点。

返回删除后的链表的头节点。**要求时间复杂度 O(1)**

示例 1:

输入: head = [4,5,1,9], val = 5
输出: [4,1,9]
解释: 给定你链表中值为  5  的第二个节点，那么在调用了你的函数之后，该链表应变为 4 -> 1 -> 9.

#### 奇思妙想

1. 当节点不是尾节点，可以把节点的下一个节点复制到该节点，然后删掉下一个节点
2. 尾节点需要查找到前序节点，因为直接将该节点`p`赋值`null`并不能改变该节点，只是将指针`p`的指向改了，前序节点依然指向该节点
3. 平均时间复杂度是`O(1)`

#### 实现

```js
const deleteNode = function (head, p) {
  // 不是尾部节点
  if (p.next !== null) {
    let next = p.next
    p.val = next.val
    p.next = next.next
    next = null
  } else if (head === p) {
    // 是头节点
    head = null
    p = null
  } else {
    // 是多节点链表的尾节点
    let temp = head
    while (temp.next !== p) {
      temp = temp.next
    }
    temp.next = p.next
    p = null
  }
  return head
}
```

### 删除排序链表中的重复元素 II

**_（LeetCode 82）/（剑指 offer 18-2）_**
存在一个按升序排列的链表，给你这个链表的头节点 head ，请你删除链表中所有存在数字重复情况的节点，只保留原始链表中没有重复出现的数字。

返回同样按升序排列的结果链表。

#### 思路

1. 一定需要两个指针，一个指向截止当前没有重复的最后一个元素，一个进行后移
2. 指针 p 进行移动，当没有到达尾部节点时，如果 p 和 p 下一个不同，则 pre 可以后移；否则 p 一直移动到不相同的元素
3. 防止头节点本身就是重复的元素，设定一个**哨兵作为头部节点**

```js
const deleteDuplicates = function (head) {
  const guard = new ListNode(-101, head)
  let pre = guard
  let p = head
  if (head === null || head.next === null) {
    return head
  }
  while (p && p.next) {
    // 当前节点和下一个不同，pre后移
    if (p.val !== p.next.val) {
      pre.next = p
      pre = p
      p = p.next
    } else {
      // 当前节点是重复节点
      while (p && p.next && p.val === p.next.val) {
        p = p.next
        // 尾部节点重复了就应该返回
        if (p.next === null) {
          pre.next = null
          // 注意这里应该立刻返回
          return guard.next
        }
      }
      // 停下来后还要向后移动一个到不重复的节点上
      if (p.next) {
        p = p.next
      }
    }
  }
  // 结束的时候p是尾部节点且没有重复，区分于尾部节点重复的情况
  if (p.next === null) {
    pre.next = p
  }
  return guard.next
}
```
