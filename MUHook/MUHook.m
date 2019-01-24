//
//  MUHook.m
//
//  Created by Magic-Unique on 2017/2/9.
//
//  Copyright Magic-Unique 2017
//

#import "MUHook.h"
#import "fishhook.h"

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

void MUAddMessageEx(Class _class, SEL sel, IMP imp, NSString *typeEncoding, IMP *result) {
    if (class_addMethod(_class, sel, imp, typeEncoding.UTF8String)) {
        Class superClass = class_getSuperclass(_class);
        Method ori_method = class_getInstanceMethod(superClass, sel);
        *result = ori_method ? method_getImplementation(ori_method) : NULL;
    } else {
        Method ori_method = class_getInstanceMethod(_class, sel);
        *result = method_getImplementation(ori_method);
        method_setImplementation(ori_method, imp);
    }
}

int MURebindSymbol(const char *symbol, void *imp, void **result) {
    return rebind_symbols((struct rebinding[1]){{symbol, imp, (void *)result}}, 1);
}
