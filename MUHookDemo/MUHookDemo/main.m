//
//  main.m
//  MUHookDemo
//
//  Created by Magic-Unique on 2017/3/20.
//  Copyright © 2017年 unique. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MUHook.h"

#import "MUExtrendsSample.h"
#import "MUFastCallSample.h"
#import "MUHookSample.h"
#import "MUHookSymbolSample.h"

#import "MUClass.h"

#import <mach-o/dyld.h>
#include <dlfcn.h>

MUHInstanceImplementation(NSDictionary, objectForKey, id, NSString *key) {
    if ([key isEqualToString:@"a"]) {
        return @"1";
    }
    return MUHOrig(NSDictionary, objectForKey, key);
}

void testDic(NSDictionary *dic) {
    id value = dic[@"a"];
    Class c = object_getClass(dic);
    
    Dl_info info = {0};
    
    if(dladdr((__bridge void *)c, &info) == 0) {
        
    }
    
    NSString *path = [NSString stringWithUTF8String:info.dli_fname];
    if ([value isEqualToString:@"1"]) {
        
        NSLog(@"%@-YES-in %@", object_getClass(dic), path);
    } else {
        NSLog(@"%@-NO-in %@", object_getClass(dic), path);
    }
}

#define MUHHookClusterMessage(c,n)

void MUHookClusterMessageEx(Class _class, SEL sel, IMP imp, IMP *result) {
    unsigned int outCount = 0;
//    const char **classNames = objc_copyClassNamesForImage("/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation", &outCount);
    Class *classNames = objc_copyClassList(&outCount);
    for (NSUInteger i = 0; i < outCount; i++) {
        Class cls = classNames[i];//objc_getClass(classNames[i]);
        if (class_getSuperclass(cls) == _class) {
            NSLog(@"%@", cls);
        } else if (cls == _class) {
            NSLog(@"==== %@", cls);
        }
    }
}

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        MUHHookInstanceMessage(NSDictionary, objectForKey, objectForKeyedSubscript:);
        MUHookClusterMessageEx(MUHClass(NSDictionary), @selector(objectForKeyedSubscript:), NULL, NULL);
        
        testDic(@{@"a":@"b"});
        testDic(@{@"a":@"b", @"c":@"d"});
        testDic(@{@"a":@"b"}.mutableCopy);
        testDic(@{@"a":@"b", @"c":@"d"}.mutableCopy);
        testDic([NSDictionary dictionaryWithObject:@"a" forKey:@"b"]);
        testDic([NSDictionary dictionaryWithObjectsAndKeys:@"a", @"b", @"cd", @"ef", nil]);
        testDic([NSMutableDictionary dictionaryWithObject:@"a" forKey:@"b"]);
        testDic([NSMutableDictionary dictionaryWithObjectsAndKeys:@"a", @"b", @"cd", @"ef", nil]);
        
//        initMUHookSymbolSample();
        
//        int c = getchar();
//        printf("%c\n", c);

//        MUSubClass *obj = [MUSubClass new];
//        MUHAsct(obj, name, strong) = @"hh";
//        NSLog(@"%@", MUHAsct(obj, name, strong));
//
//        MUHInitClass(MUExtendsSubClass)();
//        MUExtendsSubClass *subInstance = MUHAllocInitWith(MUExtendsSubClass, init);
//        [subInstance superVoidMethodWithObject:[NSObject new]];
//        [subInstance superReturnValueMethod];
//        subInstance.name = @"name";
//        subInstance.age = 12;
//        subInstance.frame = NSMakeRect(1, 2, 3, 4);
//        NSLog(@"test subclass ivar: %@ %@ %@", subInstance.name, @(subInstance.age), NSStringFromRect(subInstance.frame));
//
//        fastCall();
//
//        MUHInitClass(MUHookClass)();
//        MUHookClass *hookInstance = MUHSendClassMsg(MUHookClass, instanceWithInt:0 object:nil);
//        [hookInstance voidMethodWithObject:@"aaa"];
//        [hookInstance returnValueMethod];
    }
    return 0;
}
