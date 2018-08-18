if(!Function.prototype.bind){
    Function.prototype.bind = function(oThis){
        if(typeof this !== 'function'){
            throw new TypeError('the bind should be called by a function');
        }
        let bindArgs = Array.prototype.slice.call(arguments,1);
        let simpleFun = function(){};
        let originFun = this;
        let resFun = function(){
            return originFun.apply(this instanceof simpleFun?this:oThis,
                                  bindArgs.concat(Array.prototype.slice.call(arguments)));
        }
        if(this.prototype){
            simpleFun.prototype = this.prototype;
            // 不丢失原先的函数原型
        }
        resFun.prototype = new simpleFun();
        // 返回的函数的原型-(原型)->simpleFun,那么当resFun作为new调用，其中的this->resFun.prototype->simpleFun.prototype,从而this instanceof simpleFun为真
        return resFun;
    }   
}