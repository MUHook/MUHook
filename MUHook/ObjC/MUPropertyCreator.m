//
//  MUPropertyCreator.m
//  MUHookDemo
//
//  Created by Magic-Unique on 2019/1/25.
//  Copyright © 2019 unique. All rights reserved.
//

#import "MUPropertyCreator.h"
#import <objc/runtime.h>

@implementation MUPropertyCreator

+ (instancetype)add:(Class)cls sel:(SEL)sel typeEncoding:(NSString *)typeEncoding {
    MUPropertyCreator *creator = [[self alloc] init];
    creator->_cls = cls;
    creator->_sel = sel;
    creator->_typeEncoding = [typeEncoding copy];
    return creator;
}

- (void)setObject:(id)obj forKeyedSubscript:(NSString *)key {
    class_addMethod(_cls, _sel, imp_implementationWithBlock(obj), _typeEncoding.UTF8String);
}

@end
