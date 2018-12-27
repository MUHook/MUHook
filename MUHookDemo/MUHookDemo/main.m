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

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        
//        initMUHookSymbolSample();
        
//        int c = getchar();
//        printf("%c\n", c);

        MUSubClass *obj = [MUSubClass new];
        MUHAsct(obj, name, strong) = @"hh";
        NSLog(@"%@", MUHAsct(obj, name, strong));
        
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
