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

MUHInstanceImplementation(MUExtendsSubClass, setName, void, NSString *name) {
    MUHSelfIvar(_name) = [name copy];
}

MUHInstanceImplementation(MUExtendsSubClass, getName, NSString *) {
    return MUHSelfIvar(_name);
}

MUHInstanceImplementation(MUExtendsSubClass, setAge, void, NSUInteger age) {
    MUHSelfIvar(_age) = @(age);
}

MUHInstanceImplementation(MUExtendsSubClass, getAge, NSUInteger) {
    return [MUHSelfIvar(_age) unsignedIntegerValue];
}

MUHInstanceImplementation(MUExtendsSubClass, setFrame, void, CGRect frame) {
    MUHSelfIvar(_frame) = [NSValue valueWithRect:frame];
}

MUHInstanceImplementation(MUExtendsSubClass, getFrame, CGRect) {
    return [(NSValue *)MUHSelfIvar(_frame) rectValue];
}

void MUHInitClass(MUExtendsSubClass)(void) {
    MUHCreateClass(MUExtendsSubClass, MUExtendsSuperClass) withIvarList {
        MUHAddIvar(NSString *, _name);
        MUHAddIvar(NSUInteger, _age);
        MUHAddIvar(CGRect, _frame);
    };
    MUHAddClassMethod(MUExtendsSubClass, subInstance, superInstanceWithInt:object:, @@:q@);
    MUHAddInstanceMethod(MUExtendsSubClass, voidMethod, superVoidMethodWithObject:, v@:@);
    MUHAddInstanceMethod(MUExtendsSubClass, returnMethod, superReturnValueMethod, @@:);
    
    MUHAddInstanceMethod(MUExtendsSubClass, setName, setName:, v@:@);
    MUHAddInstanceMethod(MUExtendsSubClass, getName, name, @@:);
    MUHAddInstanceMethod(MUExtendsSubClass, setAge, setAge:, v@:Q);
    MUHAddInstanceMethod(MUExtendsSubClass, getAge, age, Q@:);
    MUHAddInstanceMethod(MUExtendsSubClass, setFrame, setFrame:, v@:{CGRect={CGPoint=dd}{CGSize=dd}});
    MUHAddInstanceMethod(MUExtendsSubClass, getFrame, frame, {CGRect={CGPoint=dd}{CGSize=dd}}@:);
}
