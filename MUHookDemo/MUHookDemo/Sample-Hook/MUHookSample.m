//
//  MUHookSample.m
//  MUHookDemo
//
//  Created by Shuang Wu on 2017/8/15.
//  Copyright © 2017年 unique. All rights reserved.
//

#import "MUHookSample.h"

MUHClassImplementation(MUHookClass, factory, MUHookClass *, NSInteger integer, id object) {
    NSLog(@"__hook__ -[MUHookClass instanceWithInt:object:]");
    MUHookClass *instance = MUHOrig(MUHookClass, factory, integer, object);
    return instance;
}

MUHInstanceImplementation(MUHookClass, voidMethod, void, id object) {
    NSLog(@"__hook__ -[MUHookClass voidMethodWithObject:]");
    MUHOrig(MUHookClass, voidMethod, object);
}

MUHInstanceImplementation(MUHookClass, returnMethod, id) {
    NSLog(@"__hook__ -[MUHookClass returnValueMethod]");
    return MUHOrig(MUHookClass, returnMethod);
}

void MUHInitClass(MUHookClass) {
    MUHHookClassMessage(MUHookClass, factory, instanceWithInt:object:);
    MUHHookInstanceMessage(MUHookClass, voidMethod, voidMethodWithObject:);
    MUHHookInstanceMessage(MUHookClass, returnMethod, returnValueMethod);
}
