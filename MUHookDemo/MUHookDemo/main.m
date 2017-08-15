//
//  main.m
//  MUHookDemo
//
//  Created by Shuang Wu on 2017/3/20.
//  Copyright © 2017年 unique. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MUHook.h"

#import "MUExtrendsSample.h"
#import "MUFastCallSample.h"
#import "MUHookSample.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        MUHInitClass(MUExtendsSubClass);
        MUExtendsSubClass *subInstance = MUHAllocInitWith(MUExtendsSubClass, init);
        [subInstance superVoidMethodWithObject:[NSObject new]];
        [subInstance superReturnValueMethod];
        
        fastCall();
        
        MUHInitClass(MUHookClass);
        MUHookClass *hookInstance = MUHSendClassMsg(MUHookClass, instanceWithInt:0 object:nil);
        [hookInstance voidMethodWithObject:@"aaa"];
        [hookInstance returnValueMethod];
    }
    return 0;
}
