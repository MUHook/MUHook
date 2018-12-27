//
//  MUExtendsSubClass.m
//  MUHookDemo
//
//  Created by Magic-Unique on 2017/8/15.
//  Copyright © 2017年 unique. All rights reserved.
//

#import "MUExtendsSubClass.h"

MUHClassImplementation(MUExtendsSubClass, subInstance, MUExtendsSubClass *, NSInteger integer, id object) {
    NSLog(@"+[MUExtendsSubClass superInstanceWithInt:(NSInteger)%ld object:(id)%@]", integer, object);
    integer += 1; // Modify arguments
    MUExtendsSubClass *subInstancce = MUHSuper(MUExtendsSubClass, subInstance, integer, object);
    return subInstancce;
}

MUHInstanceImplementation(MUExtendsSubClass, voidMethod, void, id object) {
    NSLog(@"+[MUExtendsSubClass superVoidMethodWithObject:(id)%@]", object);
    object = [MUExtendsSuperClass new]; // Modify arguments
    MUHSuper(MUExtendsSubClass, voidMethod, object);
}

MUHInstanceImplementation(MUExtendsSubClass, returnMethod, id) {
    NSLog(@"+[MUExtendsSubClass superReturnValueMethod]");
    id returnValue = MUHSuper(MUExtendsSubClass, returnMethod);
    return returnValue;
}

void MUHInitClass(MUExtendsSubClass) {
    MUHCreateClass(MUExtendsSubClass, MUExtendsSuperClass);
    MUHAddClassMethod(MUExtendsSubClass, subInstance, superInstanceWithInt:object:, @@:q@);
    MUHAddInstanceMethod(MUExtendsSubClass, voidMethod, superVoidMethodWithObject:, v@:@);
    MUHAddInstanceMethod(MUExtendsSubClass, returnMethod, superReturnValueMethod, @@:);
}
