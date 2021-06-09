# singleton--单例模式

2021.06.09

## background

定义：一个只有一个实例的类  
应用：缓存池，全局变量，window 对象等，在全局中只需要有一个  
要点：

1. 单一职责，每个函数实现一个主要功能，因此需要两个函数，一个构造函数，一个控制单例
2. 具有通用可扩展性，遇到下一个单例，可以不用复制代码

## instance

### 代理模式

分离的两个函数

```js
// 构造函数
const ConstructorExp = function(name){
  this.name = name
}
// 代理类，注意返回的是一个函数，闭包是为了封装状态变量
const proxySingleton = (() => {
  // 可以用闭包或者用this绑定到类上
  let instance
  return (arguments) => {
    if (!instance) {
      instance = new ConstructorExp(arguments)
    }
    return instance
  }
})()

proxySingleton('jolly');
// ConstructorExp {name: "jolly"}
proxySingleton('test');
// ConstructorExp {name: "jolly"}
```

### 通用惰性单例

实现单例的作为一个工厂函数，将构造函数作为参数

```js
// 调用getSingleton()会返回一个实现了单例的构造
const getSingleton =function (constructorFn) {
  let instance
  return function() {
      if(!instance){
          instance = new constructorFn(arguments)
      }
    return instance
  }
}
const ConstructorExp = function(arguments){
  this.name = arguments[0];
}
const singletonDemo = getSingleton(ConstructorExp)
singletonDemo('jolly')
// ConstructorExp {name: "jolly"}
singletonDemo('test')
// ConstructorExp {name: "jolly"}
```

### js 特性单例

js 无类的概念，本身单例可以通过全局变量实现。但全局变量会有命名空间污染，解决方案：

1. 命名空间  
   一个灵活的动态命名空间方案：

```js
const MyApp = {}
const getNameSpace = (name) => {
  const nameArr = name.split('.')
  let current = MyApp
  nameArr.forEach((name) => {
    if (!current[name]) {
      current[name] = {}
    }
    current = current[name]
  })
}
getNameSpace('a.b.c')
/* 
MyApp{
  a:{
    b:{
      c:{}
    }
  }
}
**/
```

2. 闭包  
   如上第一种代理模式下，为了将`instance`封装在其中，代理实现需要使用闭包

### 其他语言

js 是单线程，当出现多线程的情况下，需要注意并发，可以通过加锁来控制，作为了解不做详述
