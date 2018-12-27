//
//  MUHookClass.m
//  MUHookDemo
//
//  Created by Magic-Unique on 2017/8/15.
//  Copyright © 2017年 unique. All rights reserved.
//

#import "MUHookClass.h"

@implementation MUHookClass

+ (instancetype)instanceWithInt:(NSInteger)integer object:(id)object {
    return [self new];
}

- (void)voidMethodWithObject:(id)object {
    
}

- (id)returnValueMethod {
    return nil;
}

@end
