//
//  MUFastCallClass.m
//  MUHookDemo
//
//  Created by Shuang Wu on 2017/8/15.
//  Copyright © 2017年 unique. All rights reserved.
//

#import "MUFastCallClass.h"
#import "MUHook.h"

@implementation MUFastCallClass

- (instancetype)initWithInteger:(NSInteger)integer object:(id)object {
    self = [super init];
    if (self) {
        MUHSetSelfAsct(integer, @(integer), copy);
        MUHSetSelfAsct(object, object, weak);
    }
    return self;
}

+ (instancetype)instanceWithInteger:(NSInteger)integer object:(id)object {
    return [[self alloc] initWithInteger:integer object:object];
}

@end
