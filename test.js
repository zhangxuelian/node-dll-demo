const { initDll } = require('./sign.dll.so');
const sign = require('./sign.dll.so');

var initRet = sign.initSo();
console.log(`初始化：${initRet.code}`)
if(initRet.code != 0){
    return;
}
var instance = initRet.instance,signStructor=initRet.signStructor;
var devRet = sign.createDevice(instance,'192.168.37.164','45008');
console.log(`连接签名板:${devRet.code}`);
if(devRet.code != 0){
    return;
}
var handle = devRet.handle;
var callbackRet = sign.setCallBack(instance,function(ret){
    console.log(`回调：${JSON.stringify(ret)}`)
});
if(callbackRet.code != 0){
    return;
}
sign.sendPdf(instance,handle,'./test1.pdf','./test2.pdf',signStructor);