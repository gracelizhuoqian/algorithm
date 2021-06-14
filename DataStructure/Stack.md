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
