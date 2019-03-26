//
//  MUClassCreator.m
//  MUHookDemo
//
//  Created by Magic-Unique on 2019/1/5.
//  Copyright © 2019 unique. All rights reserved.
//

#import "MUClassCreator.h"
#import <objc/runtime.h>
#import <objc/message.h>

@implementation MUClassCreator {
    Class _cls;
}

+ (instancetype)_create:(NSString *)cls extends:(NSString *)sprCls {
    Class _superClass = sprCls ? objc_getClass(sprCls.UTF8String) : objc_getClass("NSObject");
    Class _class = objc_allocateClassPair(_superClass, cls.UTF8String, 0);
    if (_class) {
        return [[self alloc] initWithClass:_class];
    } else {
        return nil;
    }
}

- (instancetype)initWithClass:(Class)cls {
    self = [super init];
    if (self) {
        _cls = cls;
    }
    return self;
}

- (id)objectForKeyedSubscript:(id)key {
    objc_registerClassPair(_cls);
    return nil;
}

- (void)setObject:(id)obj forKeyedSubscript:(id)key {
    void (^block)(Class cls) = obj;
    block(_cls);
    objc_registerClassPair(_cls);
}

@end
