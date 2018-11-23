//
//  MUHMember.m
//  MUHookDemo
//
//  Created by 吴双 on 2018/11/23.
//  Copyright © 2018年 unique. All rights reserved.
//

#import "MUHMember.h"
#import <objc/runtime.h>

@interface _MUHIvarMember : MUHMember @end
@interface _MUHAssociationMember : MUHMember @end

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

- (MUHMember *)_asct:(MUHAssosiationType)type {
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
    MUHAssosiationType _type;
}

- (MUHMember *)_asct:(MUHAssosiationType)type {
    _type = type;
    return [super _asct:type];
}

- (id)objectForKeyedSubscript:(NSString *)key {
    return [self.object muh_getAssosiationForKey:key];
}

- (void)setObject:(id)obj forKeyedSubscript:(NSString *)key {
    [self.object muh_setAssosiationObject:obj forKey:key type:_type];
}

@end
