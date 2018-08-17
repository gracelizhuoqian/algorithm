const deepCopy = function(sobj){
    let robj = null;
    let type = Object.prototype.toString.call(sobj).match(/^\[object (\w+)]$/)[1];
    switch(type){
        case "Array":
            robj = [];
            sobj.forEach((item)=>{
                robj.push(deepCopy(item));
            })
            return robj;
        case "Object":
            robj = {};
            Object.keys(sobj).forEach((item)=>{
                robj[item] = deepCopy(sobj[item]);
            })
            return robj;
        default:
            return robj = sobj;
    } 
}
var key1 = 'name',
    key2 = 13,
    key3 = true,
    key4 = undefined,
    key5 = null,
    key6 = [78,89],
    key7 = {"name":'lzq'};
console.log(deepCopy(key1));
console.log(deepCopy(key2));
console.log(deepCopy(key3));
console.log(deepCopy(key4));
console.log(deepCopy(key5));
var deep6=deepCopy(key6);
var deep7=deepCopy(key7);
console.log(deep6);
console.log(deep7);
key7.name="Jolly";
key6.push(12);
console.log(deep6);
console.log(deep7);