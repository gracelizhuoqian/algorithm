# 树

### 重建二叉树

输入某二叉树的前序遍历和中序遍历的结果，请重建该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。

例如，给出

前序遍历 preorder = [3,9,20,15,7]
中序遍历 inorder = [9,3,15,20,7]
返回如下的二叉树：[3,9,20,null,null,15,7]
限制：

0 <= 节点个数 <= 5000

```js
const reconstructTree = function (pre, ps, pe, ino, is, ie) {
  // 注意溢出数组
  if (ps > pe || is > ie || pe >= pre.length || ie >= pre.length) {
    return null;
  }
  if (ps === pe && is === ie) {
    return new TreeNode(pre[ps]);
  }
  let root = new TreeNode(pre[ps]);
  let rootIndexOfIn;
  // 注意这里ie是索引，因此应该有=判断
  for (let i = is; i <= ie; i++) {
    if (ino[i] === root.val) {
      rootIndexOfIn = i;
    }
  }
  let leftSize = rootIndexOfIn - is;
  let rightSize = ie - rootIndexOfIn;
  root.left = reconstructTree(
    pre,
    ps + 1,
    leftSize + ps,
    ino,
    is,
    rootIndexOfIn - 1
  );
  root.right = reconstructTree(
    pre,
    pe - rightSize + 1,
    pe,
    ino,
    rootIndexOfIn + 1,
    ie
  );
  return root;
};
const buildTree = function (preorder, inorder) {
  const len = inorder.length;
  return reconstructTree(preorder, 0, len - 1, inorder, 0, len - 1);
};
```

### 数的子结构

输入两棵二叉树 A 和 B，判断 B 是不是 A 的子结构。**(约定空树不是任意一个树的子结构)**

B 是 A 的子结构， 即 A 中有出现和 B 相同的结构和节点值。
示例 1：

输入：A = [1,2,3], B = [3,1]
输出：false

#### 思路

1. 遍历 A 的每一个节点，找到那些和 B 的根节点值一致的节点，那么子结构可能出现在以这些节点为根的子树中
2. 对上面的每个节点，以 B 为原型递归 B 中的每个节点，看是否在 A 中对应位置存在且相等，一旦不满足，则返回否

#### 实现

```js
const hasSameStructure = function (ra, rb) {
  if (!ra && !rb) {
    return true;
  }
  if (rb && !ra) {
    return false;
  }
  if (!rb && ra) {
    return true;
  }
  if (ra.val === rb.val) {
    return (
      hasSameStructure(ra.left, rb.left) && hasSameStructure(ra.right, rb.right)
    );
  } else {
    // 注意这里，不想等应该直接返回false
    return false;
  }
};
const isSubStructure = function (A, B) {
  let res = false;
  if (!A && B) {
    return false;
  }
  if (!B) {
    return false;
  }
  // 先序遍历
  if (A.val === B.val) {
    // A 是满足条件的根节点
    res = hasSameStructure(A, B);
    if (res) {
      return true;
    }
  }
  return isSubStructure(A.left, B) || isSubStructure(A.right, B);
};
```

### 从上到下打印二叉树 II

从上到下按层打印二叉树，同一层的节点按从左到右的顺序打印，每一层打印到一行。

例如:
给定二叉树: [3,9,20,null,null,15,7],
返回其层次遍历结果：

[
[3],
[9,20],
[15,7]
]

#### 思路

设置三个变量，level 表当前层，nextLevel 表下一层节点数，curRest 表当前层未打印节点数

#### 实现

```js
var levelOrder = function (root) {
  const queue = [];
  const res = [];
  if (!root) {
    return res;
  }
  let nextLevel = 0;
  let curRest = 1;
  queue.push(root);
  let level = 0;
  while (queue.length) {
    let front = queue.shift();
    if (!res[level]) {
      res[level] = [];
    }
    res[level].push(front.val);
    curRest--;
    if (front.left) {
      queue.push(front.left);
      nextLevel++;
    }
    if (front.right) {
      queue.push(front.right);
      nextLevel++;
    }
    if (curRest === 0) {
      curRest = nextLevel;
      nextLevel = 0;
      level++;
    }
  }
  return res;
};
```

### 从上到下打印二叉树 III

请实现一个函数按照之字形顺序打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右到左的顺序打印，第三行再按照从左到右的顺序打印，其他行以此类推。

例如:
给定二叉树: [3,9,20,null,null,15,7],

返回其层次遍历结果：

[
[3],
[20,9],
[15,7]
]

```js
var levelOrder = function (root) {
  // 双栈结构
  if (!root) {
    return [];
  }
  const stack1 = [];
  const stack2 = [];
  const res = [];
  let level = 0;
  stack1.push(root);
  while (stack1.length || stack2.length) {
    if (!res[level]) {
      res[level] = [];
    }
    //  偶数层，往栈2压，从左向右
    while (level % 2 === 0 && stack1.length) {
      let front = stack1.pop();
      res[level].push(front.val);
      if (front.left) {
        stack2.push(front.left);
      }
      if (front.right) {
        stack2.push(front.right);
      }
    }
    //  奇数层，往栈1压，从右向左
    while (level % 2 === 1 && stack2.length) {
      let front = stack2.pop();
      res[level].push(front.val);
      if (front.right) {
        stack1.push(front.right);
      }
      if (front.left) {
        stack1.push(front.left);
      }
    }
    level++;
  }
  return res;
};
```

### 二叉树中和为某一值的路径

输入一棵二叉树和一个整数，打印出二叉树中节点值的和为输入整数的所有路径。从树的根节点开始往下一直到叶节点所经过的节点形成一条路径。

```js
const subPathSum = function (root, path, target, res) {
  if (!root) {
    return;
  }
  if (root && !root.left && !root.right && root.val === target) {
    res.push(path.slice());
  }
  if (root.left) {
    path.push(root.left.val);
    subPathSum(root.left, path, target - root.val, res);
  }
  if (root.right) {
    path.push(root.right.val);
    subPathSum(root.right, path, target - root.val, res);
  }
  // 访问了当前节点后，把当前节点从路径中去除
  path.pop();
};
var pathSum = function (root, target) {
  const res = [];
  if (!root) {
    return [];
  }
  const path = [root.val];
  subPathSum(root, path, target, res);
  return res;
};
```

### 二叉排序树转换有序链表

#### 思路

1. 二叉排序树中序遍历
2. 设置当前最大的节点为全局变量，以在递归过程中实时更新
3. 另外一种方法是返回一个最小值和最大值的数组

#### 实现

```js
let maxNode = null;
const subTreeToDL = function (root) {
  if (!root) {
    return null;
  }
  if (root.left) {
    subTreeToDL(root.left);
  }
  if (maxNode) {
    maxNode.right = root;
    root.left = maxNode;
  }
  maxNode = root;
  if (root.right) {
    subTreeToDL(root.right, maxNode);
  }
};
var treeToDoublyList = function (root) {
  if (!root) {
    return null;
  }
  maxNode = null;
  subTreeToDL(root);
  let minNode = maxNode;
  while (minNode && minNode.left) {
    minNode = minNode.left;
  }
  minNode.left = maxNode;
  maxNode.right = minNode;
  return minNode;
};
```

### 序列化和反序列化二叉树 \*

请实现两个函数，分别用来序列化和反序列化二叉树。

```js
const subSerialize = (r, serialStr) => {
  const queue = [];
  queue.push(r);
  serialStr = `${r.val}`;
  while (queue.length) {
    let front = queue.shift();
    if (front.left) {
      serialStr += `,${front.left.val}`;
      queue.push(front.left);
    } else {
      serialStr += `,null`;
    }
    if (front.right) {
      serialStr += `,${front.right.val}`;
      queue.push(front.right);
    } else {
      serialStr += `,null`;
    }
  }
  return serialStr;
};
const serialize = (root) => {
  if (!root) {
    return "[]";
  }
  let str = "[";
  str += subSerialize(root);
  str += "]";
  return str;
};

// 这里反过来的思路要多多思考
const deserialize = (str) => {
  if (str === "[]") {
    return null;
  }
  const nodeArray = str.slice(1, str.length - 1).split(",");
  let root = new ListNode(nodeArray[0]);
  const queue = [];
  queue.push(root);
  let index = 1;
  while (queue.length) {
    let front = queue.pop();
    let left = nodeArray[i++];
    if (left !== "null") {
      front.left = new ListNode(left);
      queue.push(front.left);
    } else {
      front.left = null;
    }
    let right = nodeArray[i++];
    if (right !== "null") {
      front.right = new ListNode(right);
      queue.push(front.right);
    } else {
      front.right = null;
    }
  }
  return root;
};
```

### 二叉搜索树的第 K 大节点

#### 思路

二叉搜索树的左子树节点的值都要小于根节点，右子树上的节点的值都要大于根节点。因此采用二叉树的逆中序遍历可以得到递减的结果。找第 K 个节点可以记录当前遍历的节点的个数，达到 K 就不再继续执行。

#### 代码

```js
const innerKthLargest = function (root, k) {
  if (!root) {
    return null;
  }
  if (root.right) {
    let num = innerKthLargest(root.right, k);
    if (index === k) {
      return num;
    }
  }
  index++;
  if (index === k) {
    return root.val;
  }
  if (root.left) {
    let num = innerKthLargest(root.left, k);
    if (index === k) {
      return num;
    }
  }
};
let index = 0;
var kthLargest = function (root, k) {
  // 注意对index的初始化
  index = 0;
  return innerKthLargest(root, k);
};
```

### 二叉树的深度

#### 思路

1. 层序遍历，一个指针 p1 指向当前层的最后一个节点，一个指针 p2 指向下一层的最后一个节点。遍历到 p1 的时候，意味着当前层已经遍历完，层数加一，p1=p2，p2 随着子节点进入队列而移动。
2. 后序遍历，递归左右子树的深度，取最大值

#### 代码

```js
// 层序遍历
var maxDepth = function (root) {
  if (!root) {
    return 0;
  }
  const head = root;
  const queue = [head];
  let p1 = head;
  let p2 = head;
  let level = 0;
  while (queue.length) {
    let cur = queue.shift();
    if (cur.left) {
      queue.push(cur.left);
      p2 = cur.left;
    }
    if (cur.right) {
      queue.push(cur.right);
      p2 = cur.right;
    }
    if (cur === p1) {
      level++;
      p1 = p2;
    }
  }
  return level;
};
// 后序遍历
var maxDepth = function (root) {
  if (!root) {
    return 0;
  }
  let leftDepth = maxDepth(root.left);
  let rightDepth = maxDepth(root.right);
  return Math.max(leftDepth, rightDepth) + 1;
};
```

### 平衡二叉树

#### 思路

后序遍历，一个变量，如果该节点作为根节点的子树是平衡的话该变量记录当前节点的树的深度，否则用-1 表示该子节点作为根节点的子树不是平衡树。

#### 代码

```js
var isBalanced = function (root) {
  if (!root) {
    return true;
  }
  if (maxDepth(root) > 0) {
    return true;
  } else {
    return false;
  }
};
var maxDepth = function (root) {
  if (!root) {
    return 0;
  }
  let leftDepth = maxDepth(root.left);
  if (leftDepth === -1) {
    return -1;
  }
  let rightDepth = maxDepth(root.right);
  if (rightDepth === -1) {
    return -1;
  }
  if (Math.abs(leftDepth - rightDepth) <= 1) {
    return Math.max(leftDepth, rightDepth) + 1;
  } else {
    return -1;
  }
};
```

### 二叉搜索树的最近公共祖先

**_ 剑指 Offer 68 - I. _**

#### 思路

当前节点 r，目标节点 p1，p2，三种情况

1. `p1<r && p2<r`或者`p1>r && p2>r`则公共节点在 r 的左子树或者右子树
2. `p1==r||p2==r` 则公共节点为当前相等的 p1(p2)
3. `p1<r&&r<p2`，公共节点为 r

#### 代码

```js
/**
 * @param {TreeNode} root
 * @param {TreeNode} p
 * @param {TreeNode} q
 * @return {TreeNode}
 */
var lowestCommonAncestor = function (root, p, q) {
  if (!root) {
    return null;
  }
  if (root.val < p.val && root.val < q.val) {
    return lowestCommonAncestor(root.right, p, q);
  }
  if (root.val > p.val && root.val > q.val) {
    return lowestCommonAncestor(root.left, p, q);
  }
  if (root.val === p.val) {
    return p;
  }
  if (root.val === q.val) {
    return q;
  }
  if (
    (p.val < root.val && root.val < q.val) ||
    (q.val < root.val && root.val < p.val)
  ) {
    return root;
  }
};
```

### 二叉搜索树的最近公共祖先

**_ 剑指 Offer 68 - II. _**

#### 思路

把路径求出来，最近的节点是路径上最后一个值相等的节点。

#### 代码

```js
/**
 * @param {TreeNode} root
 * @param {TreeNode} p
 * @param {TreeNode} q
 * @return {TreeNode}
 */
var findNode = function (root, p, path) {
  if (!root) {
    return false;
  }
  if (root.val === p.val) {
    path.push(root);
    return true;
  }
  path.push(root);
  if (findNode(root.left, p, path) || findNode(root.right, p, path)) {
    return true;
  } else {
    path.pop();
    return false;
  }
};
var lowestCommonAncestor = function (root, p, q) {
  if (!root) {
    return null;
  }
  const pathP = [];
  const pathQ = [];
  findNode(root, p, pathP);
  findNode(root, q, pathQ);
  let index = 1;
  let target = root;
  while (
    index < pathP.length &&
    index < pathQ.length &&
    pathQ[index].val === pathP[index].val
  ) {
    if (target.left === pathQ[index]) {
      target = target.left;
    } else {
      target = target.right;
    }
    index++;
  }
  return target;
};
```
