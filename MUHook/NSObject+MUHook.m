//
//  NSObject+MUHook.m
//  MUHookDemo
//
//  Created by 吴双 on 2018/4/16.
//  Copyright © 2018年 unique. All rights reserved.
//

#import "NSObject+MUHook.h"
#import <objc/runtime.h>

typedef id(^PackageBlock)(void);

@implementation NSObject (MUHook)

- (void)muh_setAssosiationObject:(id)object forKey:(NSString *)key type:(MUHAssosiationType)type {
    PackageBlock block;
    switch (type) {
        case MUHAssosiationType_strong: {
            block = ^id() {
                return object;
            };
            break;
        }
        case MUHAssosiationType_copy: {
            object = [object copy];
            block = ^id() {
                return object;
            };
            break;
        }
        case MUHAssosiationType_assign: {
            __unsafe_unretained id blockObj = object;
            block = ^id() {
                return blockObj;
            };
            break;
        }
        case MUHAssosiationType_weak: {
            __weak id blockObj = object;
            block = ^id() {
                return blockObj;
            };
            break;
        }
        default:
            break;
    }
    objc_setAssociatedObject(self, (const void *)key.hash, block, OBJC_ASSOCIATION_RETAIN);
}

- (id)muh_getAssosiationForKey:(NSString *)key {
    PackageBlock block = objc_getAssociatedObject(self, (const void *)key.hash);
    return block();
}

@end
