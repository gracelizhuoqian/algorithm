# 栈

### 两个队列模拟栈

#### 思路

1. 入栈，如果有非空的队列，必须压入非空队列中，否则下一步没法判断两个队列元素的先后顺序
2. 出栈，任何时刻都有一个队列是空的，作为元素存储使用。非空队列的最后一个元素要出来，必须把前面所有的元素都先移到空队列中，直到最后一个元素出队列作为出栈

#### 代码

```js
var MyStack = function () {
  this.queue1 = []
  this.queue2 = []
}

/**
 * Push element x onto stack.
 * @param {number} x
 * @return {void}
 */
MyStack.prototype.push = function (x) {
  if (this.queue1.length) {
    this.queue1.push(x)
  } else {
    this.queue2.push(x)
  }
}

/**
 * Removes the element on top of the stack and returns that element.
 * @return {number}
 */
MyStack.prototype.pop = function () {
  let currentQueue = this.queue1.length ? this.queue1 : this.queue2
  let emptyQueue = this.queue1.length ? this.queue2 : this.queue1
  if (currentQueue.length) {
    while (currentQueue.length > 1) {
      emptyQueue.push(currentQueue.shift())
    }
    return currentQueue.shift()
  }
}
```

### 栈的压入、弹出序列

**_(剑指 offer 31)_**
输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如，序列 {1,2,3,4,5} 是某栈的压栈序列，序列 {4,5,3,2,1} 是该压栈序列对应的一个弹出序列，但 {4,3,5,1,2} 就不可能是该压栈序列的弹出序列。

示例 1：

输入：pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
输出：true
解释：我们可以按以下顺序执行：
push(1), push(2), push(3), push(4), pop() -> 4,
push(5), pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1

#### 思路

一个辅助栈用于模拟，当弹出一个元素，如果栈顶不是该元素，则需要遍历后续没有被压栈的元素知道遇到该元素，或者后面所有都不是则不符合要求；如果栈顶是该元素，直接弹出。

#### 实现

```js
/**
 * @param {number[]} pushed
 * @param {number[]} popped
 * @return {boolean}
 */
var validateStackSequences = function (pushed, popped) {
  const stack = []
  let pushedIndex = 0
  if (pushed.length !== popped.length) {
    return false
  }
  for (let i = 0; i < popped.length; i++) {
    // 当前栈顶是要弹出元素
    if (popped[i] === stack[stack.length - 1]) {
      stack.pop()
    } else {
      while (pushedIndex < pushed.length && pushed[pushedIndex] !== popped[i]) {
        stack.push(pushed[pushedIndex])
        pushedIndex++
      }
      if (pushedIndex === pushed.length) {
        return false
      }
      if (pushed[pushedIndex] === popped[i]) {
        pushedIndex++
      }
    }
  }
  return true
}
```
