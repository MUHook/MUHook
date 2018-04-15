//
//  MUHook.m
//
//  Created by Shuang Wu on 2017/2/9.
//
//  Copyright Shuang Wu 2017
//

#import "MUHook.h"

Class MUCreateClass(const char *className, const char *superClass) {
    Class _superClass = superClass ? objc_getClass(superClass) : objc_getClass("NSObject");
    Class _class = objc_allocateClassPair(_superClass, className, 0);
    objc_registerClassPair(_class);
    return _class;
}

void MUHookInstanceMessageEx(Class _class, SEL sel, IMP imp, IMP *result) {
    Method ori_method = class_getInstanceMethod(_class, sel);
    const char *typeEncoding = method_getTypeEncoding(ori_method);
    if(!class_addMethod(_class, sel, imp, typeEncoding)) {
        // Replace implementation and return old implementation
        *result = method_getImplementation(ori_method);
        method_setImplementation(ori_method, imp);
    } else {
        // Add implementation and return super implementation
        Class superClass = class_getSuperclass(_class);
        ori_method = class_getInstanceMethod(superClass, sel);
        *result = method_getImplementation(ori_method);
    }
}

void MUHookClassMessageEx(Class _class, SEL sel, IMP imp, IMP *result) {
	MUHookInstanceMessageEx(object_getClass(_class), sel, imp, result);
}

id MUGetAsctValue(id obj, const char *name) {
    NSString *key = [NSString stringWithUTF8String:name];
    return objc_getAssociatedObject(obj, (void *)key.hash);
}

void MUSetAsctValue(id obj, const char *name, id value) {
    NSString *key = [NSString stringWithUTF8String:name];
    objc_setAssociatedObject(obj, (void *)key.hash, value, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

void MUAddInstanceMessageEx(Class _class, SEL sel, IMP imp, const char *typeEncoding, IMP *result) {
    if (class_addMethod(_class, sel, imp, typeEncoding)) {
        Class superClass = class_getSuperclass(_class);
        Method ori_method = class_getInstanceMethod(superClass, sel);
        *result = ori_method ? method_getImplementation(ori_method) : NULL;
    } else {
        Method ori_method = class_getInstanceMethod(_class, sel);
        *result = method_getImplementation(ori_method);
        method_setImplementation(ori_method, imp);
    }
}

void MUAddClassMessageEx(Class _class, SEL sel, IMP imp, const char *typeEncoding, IMP *result) {
	MUAddInstanceMessageEx(object_getClass(_class), sel, imp, typeEncoding, result);
}

Class MUAllocateClassPair(Class superClass, const char *className, size_t extraBytes) {
    superClass = superClass ? superClass : objc_getClass("NSObject");
    return objc_allocateClassPair(superClass, className, extraBytes);
}

void MURegisterClassPair(Class _class) {
    objc_registerClassPair(_class);
}

void MUSetInstanceIvar(id obj, const char *ivar, id value) {
    object_setIvar(obj, class_getInstanceVariable([obj class], ivar), value);
}

id MUGetInstanceIvar(id obj, const char *ivar) {
    return object_getIvar(obj, class_getInstanceVariable([obj class], ivar));
}

