const path = require('path');

const ffi = require('ffi-napi');
const ref = require('ref-napi');
const StructType = require('ref-struct-di')(ref);
const ArrayType = require('ref-array-di')(ref);

const sign = {
    /**
     * 回调消息map
     */
    eMsgTypeMap: {
        '-1': '无类型(错误)',
        0: '开始签名（可用于开始录像）',
        1: '所有签名已确认',
        2: '取消签名',
        3: '正在签名',
        4: '录像文件接收完成',
        5: '接收文件失败',
        6: '读取身份证成功',
        7: '网络正常',
        8: '网络异常',
        9: '设备硬件运行正常',
        10: '设备硬件运行不正常',
        11: '摄像头掉线',
        12: '超时'
    },
    /**
     * 过程状态管理
     */
    processState: {
        init: false,
        pHandler: null
    },
    /**
     * 初始化设备(dll)
     */
    initDll() {
        var kernel32 = new ffi.Library("kernel32", {
            SetDllDirectoryA: ["bool", ["string"]]
        });
        var dllPath = "";
        if (process.env.NODE_ENV !== 'development') {
            if (!this.processState.init) {
                kernel32.SetDllDirectoryA(path.join(process.cwd(), '/resources/extraResources/GSAndroidESSDK'));
                dllPath = path.join(process.cwd(), '/resources/extraResources/GSAndroidESSDK', 'GSAndroidESSDK.dll');
            } else {
                dllPath = "GSAndroidESSDK.dll";
            }
        } else {
            if (!this.processState.init) {
                kernel32.SetDllDirectoryA(path.join(process.cwd(), '/extraResources/GSAndroidESSDK'));
                dllPath = path.join(process.cwd(), '/extraResources/GSAndroidESSDK', 'GSAndroidESSDK.dll');
            } else {
                dllPath = "GSAndroidESSDK.dll";
            }
        }
        var signStructor = this.getSignStructor();
        var signInstance = new ffi.Library(dllPath, {
            'ADESS_SDK_Init': [ref.types.int, [ref.types.CString]],
            'ADESS_SDK_CreateDevice': [ref.types.int, [ref.types.CString, ref.types.int, ref.types.CString, ref.types.int]],
            'ADESS_SDK_SetMsgCallBack': [ref.types.int, ['pointer', ref.types.CString]],
            'ADESS_SDK_ClickSign': [ref.types.int, [ref.refType(ref.types.void), signStructor]],
            'ADESS_SDK_DestoryDevice': [ref.types.int, [ref.types.CString]],
            'ADESS_SDK_UnInit': [ref.types.int, []]
        });
        if (this.processState.init) {
            return {
                instance: signInstance,
                signStructor: signStructor,
                code: 0
            };
        } else {
            var code = signInstance.ADESS_SDK_Init('');
            if (code == 0) {
                this.processState.init = true;
            }
            return {
                instance: signInstance,
                signStructor: signStructor,
                code: code
            };
        }
    },
    /**
     * 初始化设备(so)
     */
    initSo() {
        var signStructor = this.getSignStructor();
        var signInstance = new ffi.Library(path.join(process.cwd(), '/extraResources/uossign', 'libGSAndroidESSDK.so'), {
            'ADESS_SDK_Init': [ref.types.int, [ref.types.CString]],
            'ADESS_SDK_CreateDevice': [ref.types.int, [ref.types.CString, ref.types.int, ref.types.CString, ref.types.int]],
            'ADESS_SDK_SetMsgCallBack': [ref.types.int, ['pointer', ref.types.CString]],
            'ADESS_SDK_ClickSign': [ref.types.int, [ref.refType(ref.types.void), signStructor]],
            'ADESS_SDK_DestoryDevice': [ref.types.int, [ref.types.CString]],
            'ADESS_SDK_UnInit': [ref.types.int, []]
        });
        var code = signInstance.ADESS_SDK_Init('');
        return {
            instance: signInstance,
            signStructor: signStructor,
            code: code
        };
    },
    /**
     * 连接签名板
     * @param {Object} signInstance 初始化的实例
     * @param {String} ip 签名板IP
     * @param {String} port 签名板端口号
     */
    createDevice(signInstance, ip, port) {
        var pHandle = ref.alloc(ref.refType(ref.types.int));
        var code = signInstance.ADESS_SDK_CreateDevice(pHandle, 0, ip, port);
        var pHandler = pHandle.deref();
        return {
            handle: pHandler,
            code: code
        };
    },
    /**
     * 设置签名板回调
     * @param {Object} signInstance 初始化的实例
     * @param {Function} callback 回调
     */
    setCallBack(signInstance, callback) {
        var setMsgCallBackFunc = ffi.Callback(ref.types.void,
            [ref.types.int, ref.types.int, ref.types.CString, ref.types.CString, ref.types.int],
            (handle, eMsgType, szSignJsonData, szPdfBase64Data, pUser) => {
                callback({
                    handle: handle,
                    eMsgType: eMsgType,
                    eMsgTypeText: this.eMsgTypeMap[eMsgType],
                    szSignJsonData: szSignJsonData,
                    szPdfBase64Data: szPdfBase64Data,
                    pUser: pUser
                });
            });
        var code = signInstance.ADESS_SDK_SetMsgCallBack(setMsgCallBackFunc, '');
        process.on('exit', () => {
            /* eslint-disable-next-line */
            setMsgCallBackFunc // keep reference avoid gc
        });
        return {
            code: code
        };
    },
    /**
     * 发送pdf
     * @param {Object} signInstance 初始化的实例
     * @param {Object} pHandler 句柄
     */
    sendPdf(signInstance, pHandler, inPdfPath, outPdfPath, signStructor) {
        var signStructorInstance = new signStructor({
            eSignType: 0,
            szPdfFilePath: this.strToArray(inPdfPath, 512),
            szOutPdfFilePath: this.strToArray(outPdfPath, 512),
        });
        var code = signInstance.ADESS_SDK_ClickSign(pHandler, signStructorInstance);
        return {
            code: code
        };
    },
    /**
     * 退出并断开设备
     * @param {Object} signInstance 初始化的实例
     * @param {Object} pHandler 句柄
     */
    destoryDevice(signInstance, pHandler) {
        var code = signInstance.ADESS_SDK_DestoryDevice(pHandler);
        return {
            code: code
        };
    },
    /**
     * 反初始化
     * @param {Object} signInstance 初始化的实例
     */
    unInit(signInstance) {
        var code = signInstance.ADESS_SDK_UnInit();
        return {
            code: code
        };
    },
    /**
     * 字符串转数组
     * @param {String} str 字符串
     * @param {Number} size 数组长度
     */
    strToArray(str, size) {
        var arr = new Array(size).fill(0);
        for (var i = 0; i < str.length; ++i) {
            arr[i] = str[i];
        }
        return arr;
    },
    /**
     * 获取签名结构体对象
     */
    getSignStructor() {
        return StructType({
            eSignType: ref.types.int,
            szPdfFilePath: ArrayType(ref.types.char, 512),
            szOutPdfFilePath: ArrayType(ref.types.char, 512),
            szLocation: ArrayType(ref.types.char, 512),
            bEncryption: ref.types.bool,
            nFaceCheck: ref.types.int
        });
    },
    test(){
        console.log('zzz');
    }
}

module.exports = sign;