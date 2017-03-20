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

MUHImplementation(MUClass, setName, void, NSString *name) {
    NSLog(@"%s", __FUNCTION__);
    self.name = name;
}

MUHImplementation(MUClass, getName, NSString *) {
    NSLog(@"%s", __FUNCTION__);
    return self.name;
}












@interface MUSubclass : MUClass

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
    MUHAddMessage(MUSubclass, @selector(setName3:), newSetName, v@:@);
    MUHAddMessage(MUSubclass, @selector(name3), newGetName, v@:);
    MUHRegisterClass(MUSubclass);
}







MUHImplementation(MUSubSubClass, subSetName, void, NSString *name) {
    NSLog(@"%s", __FUNCTION__);
    MUHOrig(MUSubSubClass, subSetName, name);
}

MUHImplementation(MUSubSubClass, subGetName, NSString *) {
    NSLog(@"%s", __FUNCTION__);
    return MUHOrig(MUSubSubClass, subGetName);
}




int main(int argc, const char * argv[]) {
    @autoreleasepool {
        MUHHookMessage(MUClass, @selector(setName2:), setName);
        MUHHookMessage(MUClass, @selector(name2), getName);
        
//        MUClass *obj = [MUClass new];
//        obj.name2 = @"name";
//        NSLog(@"Name: %@", obj.name2);
        
        MUHInitClass(MUSubclass);
        MUSubclass *obj = [NSClassFromString(@"MUSubclass") new];
        obj.name3 = @"haha";
        NSLog(@"Name: %@", obj.name3);
        
//        MUHHookMessage(MUSubSubClass, @selector(setName:), subSetName);
//        MUHHookMessage(MUSubSubClass, @selector(name), subGetName);
//        MUSubClass *obj = [MUSubClass new];
//        obj.name = @"name";
//        NSLog(@"Name: %@", obj.name);
    }
    return 0;
}
