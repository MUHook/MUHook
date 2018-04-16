//
//  MUFastCallSample.m
//  MUHookDemo
//
//  Created by Shuang Wu on 2017/8/15.
//  Copyright © 2017年 unique. All rights reserved.
//

#import "MUFastCallSample.h"

void fastCall() {
    MUFastCallClass *instance = MUHAllocInitWith(MUFastCallClass, initWithInteger:1 object:[NSObject new]);
    NSObject *obj = MUHGetObjectAsct(instance, object);
    MUHSetObjectAsct(instance, object, nil, weak);
    NSLog(@"%@", obj);
}
