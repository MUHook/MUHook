//
//  MUHook.m
//
//  Created by Shuang Wu on 2017/2/9.
//
//  Copyright Shuang Wu 2017
//

#import "MUHook.h"
#import <objc/runtime.h>

void MUHookMessageEx(Class _class, SEL sel, IMP imp, IMP *result) {
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

void MUAddMessageEx(Class _class, SEL sel, IMP imp, const char *typeEncoding, IMP *result) {
    if (class_addMethod(_class, sel, imp, typeEncoding)) {
        Class superClass = class_getSuperclass(_class);
        Method ori_method = class_getInstanceMethod(superClass, sel);
        *result = ori_method ? method_getImplementation(ori_method) : NULL;
    } else {
        *result = NULL;
    }
}

Class MUAllocateClassPair(Class superClass, const char *className, size_t extraBytes) {
    superClass = superClass ? superClass : objc_getClass("NSObject");
    return objc_allocateClassPair(superClass, className, extraBytes);
}

void MURegisterClassPair(Class _class) {
    objc_registerClassPair(_class);
}
