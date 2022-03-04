# 链表

### 逆序打印链表

```js
const subPrint = (arr, head) => {
  if (!head) {
    return;
  }
  subPrint(arr, head.next);
  arr.push(head.val);
};
var reversePrint = function (head) {
  const res = [];
  subPrint(res, head);
  return res;
};
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
    let next = p.next;
    p.val = next.val;
    p.next = next.next;
    next = null;
  } else if (head === p) {
    // 是头节点
    head = null;
    p = null;
  } else {
    // 是多节点链表的尾节点
    let temp = head;
    while (temp.next !== p) {
      temp = temp.next;
    }
    temp.next = p.next;
    p = null;
  }
  return head;
};
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
  const guard = new ListNode(-101, head);
  let pre = guard;
  let p = head;
  if (head === null || head.next === null) {
    return head;
  }
  while (p && p.next) {
    // 当前节点和下一个不同，pre后移
    if (p.val !== p.next.val) {
      pre.next = p;
      pre = p;
      p = p.next;
    } else {
      // 当前节点是重复节点
      while (p && p.next && p.val === p.next.val) {
        p = p.next;
        // 尾部节点重复了就应该返回
        if (p.next === null) {
          pre.next = null;
          // 注意这里应该立刻返回
          return guard.next;
        }
      }
      // 停下来后还要向后移动一个到不重复的节点上
      if (p.next) {
        p = p.next;
      }
    }
  }
  // 结束的时候p是尾部节点且没有重复，区分于尾部节点重复的情况
  if (p.next === null) {
    pre.next = p;
  }
  return guard.next;
};
```

### 链表的环的入口节点

**_（LeetCode 142. 环形链表 II）_**

给定一个链表，返回链表开始入环的第一个节点。  如果链表无环，则返回  null。

为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 pos 是 -1，则在该链表中没有环。注意，pos 仅仅是用于标识环的情况，并不会作为参数传递到函数中。

说明：不允许修改给定的链表。

进阶：

你是否可以使用 O(1) 空间解决此题？

#### 思路

1. 快慢指针判断是否有环
2. 设环的长度为 c，链表头到环入口为 a，两指针相遇的位置到入口为 b；则慢指针走了`a+b`,快走了`2(a+b)`。根据设定，有`2(a+b)=a+nc+b`，从而`a+b=nc`。从相遇节点开始，第三个指针从链表头开始移动，慢指针和第三个指针相遇的时候，第三个指针走了 a，慢指针走了 nc。他们相遇在环入口。

```js
const detectCycle = (head) => {
  if (head === null) {
    return null;
  }
  let fast = head;
  let slow = head;
  let p = head;
  while (fast && fast.next) {
    fast = fast.next;
    fast = fast.next;
    slow = slow.next;
    if (slow === fast) {
      break;
    }
  }
  if (!fast || !fast.next) {
    return null;
  }
  while (p !== slow) {
    p = p.next;
    slow = slow.next;
  }
  return slow;
};
```

### 两个链表的公共节点

#### 思路

两个链表如果相交，总有一段长度是共有的，相交的节点位于共有长度某个位置。用两个指针，分别计算两个链表的长度。计算差值后，让两个指针从共同长度的起点开始寻找。
注意两个指针指向的节点的值相同但可以不是同一个节点。

#### 代码

```js
var getIntersectionNode = function (headA, headB) {
  if (headA === null || headB === null) {
    return null;
  }
  let pa = headA;
  let pb = headB;
  let lenA = 0;
  let lenB = 0;
  while (pa) {
    lenA++;
    pa = pa.next;
  }
  while (pb) {
    lenB++;
    pb = pb.next;
  }
  pa = headA;
  pb = headB;
  while (lenA > lenB) {
    pa = pa.next;
    lenA--;
  }
  while (lenB > lenA) {
    pb = pb.next;
    lenB--;
  }
  while (pa && pb) {
    if (pa === pb) {
      return pa;
    }
    pa = pa.next;
    pb = pb.next;
  }
  return null;
};
```

### 移除重复节点

```js
var removeDuplicateNodes = function (head) {
  const set = {};
  let p = head;
  let pre = head;
  if (!head) {
    return null;
  }
  while (p) {
    if (set[p.val] === undefined) {
      set[p.val] = true;
      pre = p;
      p = p.next;
    } else {
      pre.next = p.next;
      p = p.next;
    }
  }
  return head;
};
```

### 返回倒数第 K 个节点

```js
/**
 * @param {ListNode} head
 * @param {number} k
 * @return {number}
 */
var kthToLast = function (head, k) {
  let p1 = head;
  let p2 = head;
  for (let i = 0; i < k; i++) {
    p2 = p2.next;
  }
  while (p2) {
    p2 = p2.next;
    p1 = p1.next;
  }
  return p1.val;
};
```

### 删除中间节点\*

**_ 2.3 _**

#### 思路

当前节点和后继节点的值交换，再删除后继节点

#### 代码

```js
/**
 * @param {ListNode} node
 * @return {void} Do not return anything, modify node in-place instead.
 */
var deleteNode = function (node) {
  let nextNode = node.next;
  let temp = node.val;
  node.val = nextNode.val;
  nextNode.val = temp;
  node.next = nextNode.next;
};
```

### 分割链表

**_ 2.4 _**

#### 思路

两个指针，一个遍历当前链表，一个指向小于数字的最后一个节点，新的小节点在该位置插入
需要一个哨兵节点

#### 代码

```js
function ListNode(val) {
  this.val = val;
  this.next = null;
}
var partition = function (head, x) {
  let q = new ListNode(0);
  let newHead = q;
  q.next = head;
  let p = q;
  let temp = null;
  while (p.next) {
    if (p.next.val >= x) {
      p = p.next;
    } else {
      if (p === q) {
        p = p.next;
        q = q.next;
      } else {
        // 摘下节点
        temp = p.next;
        p.next = p.next.next;
        temp.next = q.next;
        q.next = temp;
        q = q.next;
      }
    }
  }
  return newHead.next;
};
```

### 回文链表

```js
var isPalindrome = function (head) {
  const pNew = new ListNode(0);
  let len = 0;
  let p1 = head;
  let p2 = head;
  let middle = null;
  if (!head.next) {
    return true;
  }
  while (p2 && p2.next) {
    p2 = p2.next.next;
    p1 = p1.next;
  }
  // 奇数节点
  if (p2) {
    middle = p1;
    p1 = p1.next;
  }
  if (!p2) {
    middle = pNew;
    pNew.next = p1;
  }
  let temp = null;
  while (p1 && p1.next) {
    temp = p1.next;
    p1.next = temp.next;
    temp.next = middle.next;
    middle.next = temp;
  }
  p1 = middle.next;
  p2 = head;
  while (p1 && p2) {
    if (p1.val === p2.val) {
      p1 = p1.next;
      p2 = p2.next;
    } else {
      return false;
    }
  }
  return true;
};
```

### 环线检测

#### 思路

双指针，快慢指针一定会相遇。从相遇的地方再次相遇会在环开始处。

#### 代码

```js
var detectCycle = function (head) {
  let fast = head;
  let slow = head;
  if (!head) {
    return null;
  }
  while (fast && fast.next) {
    fast = fast.next.next;
    slow = slow.next;
    if (fast === slow) {
      break;
    }
  }
  if (!fast || !fast.next) {
    return null;
  }
  slow = head;
  while (fast !== slow) {
    fast = fast.next;
    slow = slow.next;
  }
  return fast;
};
```
