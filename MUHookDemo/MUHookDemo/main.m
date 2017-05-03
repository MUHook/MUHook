//
//  main.m
//  MUHookDemo
//
//  Created by Shuang Wu on 2017/3/20.
//  Copyright © 2017年 unique. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MUHook.h"
#import "MUClass.h"

#pragma mark - Hook 已有的类

MUHImplementation(MUClass, setName, void, NSString *name) {
    NSLog(@"%s", __FUNCTION__);
    self.name = name;
}

MUHImplementation(MUClass, getName, NSString *) {
    NSLog(@"%s", __FUNCTION__);
    return self.name;
}

void MUHInitClass(MUClass) {
    MUHHookMessage(MUClass, getName, name2);
    MUHHookMessage(MUClass, setName, setName2:);
}

#pragma mark - 创建已有的类的子类

@interface MUSubclass : MUClass // 只有 interface 的 class，其实现是通过 runtime 动态创建出来的

@property (nonatomic, strong) NSString *name3;

@end

MUHImplementation(MUSubclass, newSetName, void, NSString *name) {
    self.name = name;
}

MUHImplementation(MUSubclass, newGetName, NSString *) {
    return self.name;
}

void MUHInitClass(MUSubclass) {
    MUHAllocateClass(MUClass, MUSubclass, 0);
    MUHAddMessage(MUSubclass, newSetName, setName3:, v@:@);
    MUHAddMessage(MUSubclass, newGetName, name3, v@:);
    MUHRegisterClass(MUSubclass);
}


#pragma mark - 夸父类hook


MUHImplementation(MUSubSubClass, subSetName, void, NSString *name) {
    NSLog(@"%s", __FUNCTION__);
    MUHOrig(MUSubSubClass, subSetName, name);
}

MUHImplementation(MUSubSubClass, subGetName, NSString *) {
    NSLog(@"%s", __FUNCTION__);
    return MUHOrig(MUSubSubClass, subGetName);
}

void MUHInitClass(MUSubSubClass) {
    MUHHookMessage(MUSubSubClass, subSetName, setName:);
    MUHHookMessage(MUSubSubClass, subGetName, name);
}

int main(int argc, const char * argv[]) {
    @autoreleasepool {
//        MUClass *obj = [MUClass new];
//        obj.name2 = @"name";
//        NSLog(@"Name: %@", obj.name2);
        
        MUHInitClass(MUSubclass);
        MUSubclass *obj = MUHAllocInitWith(MUSubclass, init);
        obj.name3 = @"haha";
        NSLog(@"Name: %@", obj.name3);
        NSString *a = [MUHAlloc(NSArray) initWithObjects:@"1", nil];
        
        MUHDefinedSend(makeString, NSString *, const char *, NSUInteger);
        a = MUHCallMsgSend(makeString, MUHClass(NSString), stringWithCString:encoding:, "aaa", 4);
        NSLog(@"a: %@", a);
//        MUSubClass *obj = [MUSubClass new];
//        obj.name = @"name";
//        NSLog(@"Name: %@", obj.name);
    }
    return 0;
}
