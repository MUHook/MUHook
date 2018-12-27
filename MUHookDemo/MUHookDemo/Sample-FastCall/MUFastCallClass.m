//
//  MUFastCallClass.m
//  MUHookDemo
//
//  Created by Magic-Unique on 2017/8/15.
//  Copyright © 2017年 unique. All rights reserved.
//

#import "MUFastCallClass.h"
#import "MUHook.h"

@implementation MUFastCallClass

- (instancetype)initWithInteger:(NSInteger)integer object:(id)object {
    self = [super init];
    if (self) {
        MUHAsct(self, integer, copy) = @(integer);
        MUHAsct(self, object, weak) = object;
    }
    return self;
}

+ (instancetype)instanceWithInteger:(NSInteger)integer object:(id)object {
    return [[self alloc] initWithInteger:integer object:object];
}

@end
