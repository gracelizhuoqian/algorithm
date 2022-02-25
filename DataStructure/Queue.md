### 滑动窗口的最大值

给定一个数组 nums 和滑动窗口的大小 k，请找出所有滑动窗口里的最大值。

示例:

输入: nums = [1,3,-1,-3,5,3,6,7], 和 k = 3
输出: [3,3,5,5,6,7]
解释:

滑动窗口的位置 最大值

---

[1 3 -1] -3 5 3 6 7 3
1 [3 -1 -3] 5 3 6 7 3
1 3 [-1 -3 5] 3 6 7 5
1 3 -1 [-3 5 3] 6 7 5
1 3 -1 -3 [5 3 6] 7 6
1 3 -1 -3 5 [3 6 7] 7

#### 思路

优先队列，用一个非严格递增队列记录当前窗口内依次出现的最大值。当新的值比队列最尾部小，则入队，意味着如果队列前面的数都滑出窗口，当前的值就是最大值，也就是当滑出的是最大值时候，必须要把次大值记录下来，由此形成的是非严格递增的队列。当新的值比队列头要大，则意味着除非当前数字滑出了，否则最大值都是当前的值，因此前面的值都不需要管了，都进行弹出。

#### 代码

```js
var maxSlidingWindow = function (nums, k) {
  if (nums.length === 0) {
    return [];
  }
  const queue = [];
  const res = [];
  for (let i = 0; i < k; i++) {
    if (queue.length === 0) {
      queue.push(nums[i]);
    } else {
      if (queue[queue.length - 1] < nums[i]) {
        // 注意不是所有都出队列，比它小的出来就可以了
        while (queue.length && queue[queue.length - 1] < nums[i]) {
          queue.pop();
        }
        queue.push(nums[i]);
      } else {
        queue.push(nums[i]);
      }
    }
  }
  res[0] = queue[0];
  for (let i = k; i < nums.length; i++) {
    // 入队列
    if (queue.length === 0 || queue[queue.length - 1] >= nums[i]) {
      queue.push(nums[i]);
    } else {
      while (queue.length && queue[queue.length - 1] < nums[i]) {
        queue.pop();
      }
      queue.push(nums[i]);
    }
    // 出队列
    if (nums[i - k] === queue[0]) {
      queue.shift();
    }
    res.push(queue[0]);
  }
  return res;
};
```

### 队列的最大值

请定义一个队列并实现函数 max_value 得到队列里的最大值，要求函数 max_value、push_back 和 pop_front 的均摊时间复杂度都是 O(1)。

若队列为空，pop_front 和 max_value 需要返回 -1

示例 1：

输入:
["MaxQueue","push_back","push_back","max_value","pop_front","max_value"]
[[],[1],[2],[],[],[]]
输出:[null,null,null,2,1,2]
示例 2：

输入:
["MaxQueue","pop_front","max_value"]
[[],[],[]]
输出:[null,-1,-1]

限制：

1 <= push_back,pop_front,max_value 的总操作数<= 10000
1 <= value <= 10^5

#### 思路

单调队列

#### 代码

```js
var MaxQueue = function () {
  this.queue = [];
  this.maxQueue = [];
};

/**
 * @return {number}
 */
MaxQueue.prototype.max_value = function () {
  if (this.maxQueue.length) {
    return this.maxQueue[0];
  }
  return -1;
};

/**
 * @param {number} value
 * @return {void}
 */
MaxQueue.prototype.push_back = function (value) {
  while (
    this.maxQueue.length &&
    value > this.maxQueue[this.maxQueue.length - 1]
  ) {
    this.maxQueue.pop();
  }
  this.maxQueue.push(value);
  this.queue.push(value);
};

/**
 * @return {number}
 */
MaxQueue.prototype.pop_front = function () {
  if (this.queue.length === 0) {
    return -1;
  }
  let front = this.queue.shift();
  if ((front === this.maxQueue[0])) {
    this.maxQueue.shift();
  }
  return front;
};

/**
 * Your MaxQueue object will be instantiated and called as such:
 * var obj = new MaxQueue()
 * var param_1 = obj.max_value()
 * obj.push_back(value)
 * var param_3 = obj.pop_front()
 */
```
