# 回溯

## 思路

1. **做选择** 当前 n 满足条件，n 指的是题目的条件，下一个位置 n+1 可以有有限确定的几种选择，n+1 可以基于 n 做递归，选择会导致 depth 增加，方向改变等
2. **做标记** 不走回头路，每次做完选择，需要做标记；不满足条件可以当即撤销标记。标记可以是布尔，如果有更多的状态可以是数值
3. **停下来** 数组越边界；不走回头路；到达叶节点（depth）；当前 n 已经不满足条件

### 单词搜索

**_（剑指 offer 12）_**

给定一个  m x n 二维字符网格  board 和一个字符串单词  word 。如果  word 存在于网格中，返回 true ；否则，返回 false 。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。
输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
输出：true

```js
function hasPath(board, target) {
  // 特殊输入处理
  const rows = board.length;
  if (rows === 0) {
    return !!target;
  }
  const cols = board[0].length;
  // 状态变量初始化
  const map = [];
  for (let i = 0; i < rows; i++) {
    map[i] = [];
    for (let j = 0; j < cols; j++) {
      map[i][j] = false;
    }
  }
  for (let i = 0; i < rows; i++) {
    for (let j = 0; j < cols; j++) {
      if (subHasPath(board, i, j, 0, map, target)) {
        return true;
      }
    }
  }
  return false;
}
function subHasPath(board, row, col, depth, map, target) {
  // 失败条件
  // 1. 路径越界
  const rows = board.length;
  const cols = board[0].length;
  if (row >= rows || row < 0 || col >= cols || col < 0) {
    return false;
  }
  // 2. 不走回头路
  if (map[row][col]) {
    return false;
  }
  // 3. 当前 n 已经不满足条件
  if (depth < target.length && board[row][col] !== target[depth]) {
    return false;
  }
  // 到达叶节点
  if (depth === target.length - 1 && board[row][col] === target[depth]) {
    return true;
  }
  // 做选择
  if (depth < target.length - 1 && board[row][col] === target[depth]) {
    map[row][col] = true;
    let result =
      subHasPath(board, row - 1, col, depth + 1, map, target) ||
      subHasPath(board, row, col - 1, depth + 1, map, target) ||
      subHasPath(board, row + 1, col, depth + 1, map, target) ||
      subHasPath(board, row, col + 1, depth + 1, map, target);
    // 注意这里的处理，每次不满足条件都去撤销选择，从而避免每次都重置map
    if (result) {
      return true;
    } else {
      map[row][col] = false;
      return false;
    }
  }
}
```

### 机器人的运动范围

**_（剑指 offer 13）_**
地上有一个 m 行 n 列的方格，从坐标 [0,0] 到坐标 [m-1,n-1] 。一个机器人从坐标 [0, 0] 的格子开始移动，它每次可以向左、右、上、下移动一格（不能移动到方格外），**也不能进入行坐标和列坐标的数位之和大于 k 的格子**。例如，当 k 为 18 时，机器人能够进入方格 [35, 37] ，因为 3+5+3+7=18。但它不能进入方格 [35, 38]，因为 3+5+3+8=19。请问该机器人能够到达多少个格子？

示例 1：

输入：m = 2, n = 3, k = 1
输出：3
示例 2：

输入：m = 3, n = 1, k = 0
输出：1
提示：

1 <= n,m <= 100
0 <= k <= 20

```js
const subPath = (m, n, map, row, col, k) => {
  // 1. 数组越界
  if (col < 0 || col >= n || row < 0 || row >= m) {
    return;
  }
  // 2. 不走回头路
  if (map[row][col] !== 0) {
    // 走过的都不再走
    return;
  }
  // 3. 判断当前
  let rowTemp = row;
  let rowSum = 0;
  let colTemp = col;
  let colSum = 0;
  while (rowTemp) {
    rowSum += rowTemp % 10;
    rowTemp = Math.floor(rowTemp / 10);
  }
  while (colTemp) {
    colSum += colTemp % 10;
    colTemp = Math.floor(colTemp / 10);
  }
  // 当前不满足，做个标记
  if (colSum + rowSum > k) {
    // 如果当前格子不能走进来，就不能从当前格子继续走！！！
    map[row][col] = 1;
  } else {
    // 当前满足，也做个标记，
    map[row][col] = 2;
    // 只有当前格子可以进来，才能接着走
    subPath(m, n, map, row - 1, col, k);
    subPath(m, n, map, row + 1, col, k);
    subPath(m, n, map, row, col - 1, k);
    subPath(m, n, map, row, col + 1, k);
  }
};

var movingCount = function (m, n, k) {
  const cache = [];
  for (let i = 0; i < m; i++) {
    cache[i] = [];
    for (let j = 0; j < n; j++) {
      cache[i][j] = 0;
    }
  }
  subPath(m, n, cache, 0, 0, k);
  let res = 0;
  for (let i = 0; i < m; i++) {
    for (let j = 0; j < n; j++) {
      if (cache[i][j] === 2) {
        res++;
      }
    }
  }
  return res;
};
```

### 打印从 1 到最大的 n 位数

**_(剑指 offer 17)_**

输入数字 n，按顺序打印出从 1 到最大的 n 位十进制数。比如输入 3，则打印出 1、2、3 一直到最大的 3 位数 999。

```js
let res = [];
const printNum = (num) => {
  res.push(num.join("").replace(/^0*/, ""));
};
const printSubNum = (num, index) => {
  let len = num.length;
  if (index === len - 1) {
    printNum(num);
    return;
  }
  for (let i = 0; i < 10; i++) {
    num[index + 1] = i + "";
    printSubNum(num, index + 1);
  }
};
const printNumbers = (n) => {
  res = [];
  if (n <= 0) {
    return res;
  }
  const numArray = [];
  for (let i = 0; i < n; i++) {
    numArray[i] = "0";
  }
  for (let i = 0; i < 10; i++) {
    numArray[0] = i - "0";
    printSubNum(numArray, 0);
  }
  // 这里多了一个0
  res.shift();
  return res;
};
```

### 字符串的排列

**_(剑指 offer 38)/（面金 8.8）_**

1. 每次固定一个位置 i，该位置和后面所有位置分别交换，i 递增；
2. 注意重复元素

对于有重复元素的，构造字母哈希表，Map={a:1,b:3,c:2};
每次**选择**一个字母放在当前位置，比如选择 b，则**路径**为 `path + b`，后面是 Map={a:1,b:2,c:2}的全排列

```js
const buildMap = (str) => {
  const len = str.length;
  const map = {};
  for (let i = 0; i < len; i++) {
    if (!map[str[i]]) {
      map[str[i]] = 1;
    } else {
      map[str[i]]++;
    }
  }
  return map;
};
const subPermutation = (map, path, depth, result) => {
  // 先找终止条件
  if (depth === 0) {
    result.push(path);
    return;
  }
  // 做选择
  Object.keys(map).forEach((char) => {
    // 选择char
    if (map[char] > 0) {
      map[char]--;
      subPermutation(map, path + char, depth - 1, result);
      map[char]++;
    }
  });
};
const permutation = (str) => {
  if (!str) {
    return [];
  }
  const res = [];
  const map = buildMap(str);
  subPermutation(map, "", str.length, res);
  return res;
};
```

### n 个骰子的点数

把 n 个骰子扔在地上，所有骰子朝上一面的点数之和为 s。输入 n，打印出 s 的所有可能的值出现的概率。

你需要用一个浮点数数组返回答案，其中第 i 个元素代表这 n 个骰子所能掷出的点数集合中第 i 小的那个的概率。

#### 思路

回溯法

#### 代码

````js
var dicesProbability = function (n) {
  const times = [];
  const points = [];
  for (let i = 1; i <= 6; i++) {
    points[0] = i;
    recursion(points, i, times, n);
  }
  const result = [];
  times.forEach((t) => {
    if (t) {
      result.push(parseFloat((t / Math.pow(6, n)).toFixed(5)));
    }
  });
  return result;
};
const recursion = (points, sum, times, n) => {
  if (points.length === n) {
    times[sum] = times[sum] === undefined ? 1 : times[sum] + 1;
    return;
  }
  for (let i = 1; i <= 6; i++) {
    points.push(i);
    recursion(points, sum + i, times, n);
    points.pop();
  }
};
```˝
````
