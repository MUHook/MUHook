//
//  NSObject+MUHook.m
//  MUHookDemo
//
//  Created by Magic-Unique on 2018/4/16.
//  Copyright © 2018年 unique. All rights reserved.
//

#import "NSObject+MUHook.h"
#import <objc/runtime.h>

typedef id(^PackageBlock)(void);

@implementation NSObject (MUHook)

- (void)muh_setAssosiationObject:(id)object forKey:(NSString *)key type:(MUHAssosiationType)type {
    PackageBlock block;
    switch (type) {
        case MUHAssosiationTypeStrong: {
            block = ^id() {
                return object;
            };
            break;
        }
        case MUHAssosiationTypeCopy: {
            object = [object copy];
            block = ^id() {
                return object;
            };
            break;
        }
        case MUHAssosiationTypeAssign: {
            __unsafe_unretained id blockObj = object;
            block = ^id() {
                return blockObj;
            };
            break;
        }
        case MUHAssosiationTypeWeak: {
            __weak id blockObj = object;
            block = ^id() {
                return blockObj;
            };
            break;
        }
        default:
            break;
    }
    objc_setAssociatedObject(self, (const void *)key.hash, block, OBJC_ASSOCIATION_COPY_NONATOMIC);
}

- (id)muh_getAssosiationForKey:(NSString *)key {
    PackageBlock block = objc_getAssociatedObject(self, (const void *)key.hash);
    if (block) {
        return block();
    } else {
        return nil;
    }
}

@end
