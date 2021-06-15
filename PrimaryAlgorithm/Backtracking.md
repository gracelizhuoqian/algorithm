# 回溯

### 单词搜索

给定一个  m x n 二维字符网格  board 和一个字符串单词  word 。如果  word 存在于网格中，返回 true ；否则，返回 false 。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。  
输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"  
输出：true

```js
function hasPath(board, target) {
  const rows = board.length
  if (rows === 0) {
    return !!target
  }
  const cols = board[0].length
  const map = []
  for (let i = 0; i < rows; i++) {
    map[i] = []
    for (let j = 0; j < cols; j++) {
      map[i][j] = false
    }
  }
  for (let i = 0; i < rows; i++) {
    for (let j = 0; j < cols; j++) {
      if (subHasPath(board, i, j, 0, map, target)) {
        return true
      }
    }
  }
  return false
}
function subHasPath(board, row, col, depth, map, target) {
  // 失败条件
  // 1. 路径越界
  const rows = board.length
  const cols = board[0].length
  if (row >= rows || row < 0 || col >= cols || col < 0) {
    return false
  }
  // 2. 已经路过
  if (map[row][col]) {
    return false
  }
  // 3. 终止判断
  if (depth < target.length && board[row][col] !== target[depth]) {
    return false
  }
  // 满足条件
  if (depth === target.length - 1 && board[row][col] === target[depth]) {
    return true
  }
  if (depth < target.length - 1 && board[row][col] === target[depth]) {
    map[row][col] = true
    let result =
      subHasPath(board, row - 1, col, depth + 1, map, target) ||
      subHasPath(board, row, col - 1, depth + 1, map, target) ||
      subHasPath(board, row + 1, col, depth + 1, map, target) ||
      subHasPath(board, row, col + 1, depth + 1, map, target)
    // 注意这里的处理，每次不满足条件都去撤销选择，从而避免每次都重置map
    if (result) {
      return true
    } else {
      map[row][col] = false
      return false
    }
  }
}
```
