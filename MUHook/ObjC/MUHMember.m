//
//  MUHMember.m
//  MUHookDemo
//
//  Created by Magic-Unique on 2018/11/23.
//  Copyright © 2018年 unique. All rights reserved.
//

#import "MUHMember.h"
#import <objc/runtime.h>

@interface _MUHIvarMember : MUHMember @end
@interface _MUHAssociationMember : MUHMember @end

typedef id(^PackageBlock)(void);

void MUSetAssociatedObject(id object, NSString *key, id value, MUHAssociationType type) {
    PackageBlock block;
    switch (type) {
            case MUHAssociationType_strong: {
                block = ^id() {
                    return value;
                };
                break;
            }
            case MUHAssociationType_copy: {
                value = [value copy];
                block = ^id() {
                    return value;
                };
                break;
            }
            case MUHAssociationType_assign: {
                __unsafe_unretained id blockObj = value;
                block = ^id() {
                    return blockObj;
                };
                break;
            }
            case MUHAssociationType_weak: {
                __weak id blockObj = value;
                block = ^id() {
                    return blockObj;
                };
                break;
            }
        default:
            break;
    }
    objc_setAssociatedObject(object, (const void *)key.hash, block, OBJC_ASSOCIATION_COPY_NONATOMIC);
}

id MUGetAssociatedObject(id object, NSString *key) {
    PackageBlock block = objc_getAssociatedObject(object, (const void *)key.hash);
    if (block) {
        return block();
    } else {
        return nil;
    }
}

@implementation MUHMember

+ (MUHMember *)_ivar {
    return [_MUHIvarMember new];
}

+ (MUHMember *)_asct {
    return [_MUHAssociationMember new];
}

- (MUHMember *)_obj:(id)object {
    _object = object;
    return self;
}

- (MUHMember *)_sel:(SEL)selector {
    return self;
}

- (MUHMember *)_asct:(MUHAssociationType)type {
    return self;
}

- (id)objectForKeyedSubscript:(NSString *)key {
    return nil;
}

- (void)setObject:(id)obj forKeyedSubscript:(NSString *)key {
}

@end

@implementation _MUHIvarMember

- (id)objectForKeyedSubscript:(NSString *)key {
    return object_getIvar(self.object, class_getInstanceVariable([self.object class], key.UTF8String));
}

- (void)setObject:(id)obj forKeyedSubscript:(NSString *)key {
    object_setIvar(self.object, class_getInstanceVariable([self.object class], key.UTF8String), obj);
}

@end

@implementation _MUHAssociationMember {
    MUHAssociationType _type;
}

- (MUHMember *)_asct:(MUHAssociationType)type {
    _type = type;
    return [super _asct:type];
}

- (id)objectForKeyedSubscript:(NSString *)key {
    return MUGetAssociatedObject(self.object, key);
}

- (void)setObject:(id)obj forKeyedSubscript:(NSString *)key {
    MUSetAssociatedObject(self.object, key, obj, _type);
}

@end
