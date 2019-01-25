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

MUHPropertyImplementation(MUExtendsSubClass, strong, NSString *, nickName);

void MUHInitClass(MUExtendsSubClass)(void) {
    MUHCreateClass(MUExtendsSubClass, MUExtendsSuperClass) withIvarList {
        MUHAddIvar(NSString *, _name);
        MUHAddIvar(NSUInteger, _age);
        MUHAddIvar(CGRect, _frame);
    };
    MUHAddClassMessage(MUExtendsSubClass, subInstance, id, superInstanceWithInt:object:, NSInteger, id);
    MUHAddInstanceMessage(MUExtendsSubClass, voidMethod, void, superVoidMethodWithObject:, id);
    MUHAddInstanceMessage(MUExtendsSubClass, returnMethod, id, superReturnValueMethod);
    
    //  Add property - 添加属性
    
    //  Method 1: for normal, support base type, struct and object, custom with association-object and ivar. support readonly
    //  方法 1：支持基本数据类型、结构体、对象，支持自定义 ivar 或者关联对象。代码多，灵活度高，可只读
    //  Usage with MUHInstanceImplementation()
    MUHAddInstanceMessage(MUExtendsSubClass, setName, void, setName:, NSString *);
    MUHAddInstanceMessage(MUExtendsSubClass, getName, NSString *, name);
    MUHAddInstanceMessage(MUExtendsSubClass, setAge, void, setAge:, NSUInteger);
    MUHAddInstanceMessage(MUExtendsSubClass, getAge, NSUInteger, age);
    
    //  Method 2: for struct, custom with association-object or ivar. manual transform it in getter and setter. support readonly
    //  方法 2：支持基本数据类型、结构体、对象，支持自定义 ivar 或者关联对象，非对象需要自己转换，代码中等，灵活度中等，可只读
    MUHAddPropertyGetter(MUExtendsSubClass, CGRect, frame, frame) {
        return [(NSValue *)MUHSelfIvar(_frame) rectValue];
    };
    MUHAddPropertySetter(MUExtendsSubClass, CGRect, frame, setFrame:) {
        MUHSelfIvar(_frame) = [NSValue valueWithRect:frame];
    };
    
    //  Method 3: for object, only support association-object with strong,copy,weak,assign. unsupport readonly
    //  方法 3：仅支持对象，仅支持关联对象，代码少、灵活度低，不可只读
    //  Usage with MUHPropertyImplementation()
    MUHAddProperty(MUExtendsSubClass, NSString *, nickName, setNickName:, nickName);
}
