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
