//
//  MUExtendsSuperClass.m
//  MUHookDemo
//
//  Created by Magic-Unique on 2017/8/15.
//  Copyright © 2017年 unique. All rights reserved.
//

#import "MUExtendsSuperClass.h"

@implementation MUExtendsSuperClass

+ (instancetype)superInstanceWithInt:(NSInteger)integer object:(id)object {
    NSLog(@"+[MUExtendsSuperClass superInstanceWithInt:(NSInteger)%ld object:(id)%@]", integer, object);
    return [[self alloc] init];
}

- (void)superVoidMethodWithObject:(id)object {
    NSLog(@"+[MUExtendsSuperClass superVoidMethodWithObject:(id)%@]", object);
}

- (id)superReturnValueMethod {
    NSLog(@"+[MUExtendsSuperClass superReturnValueMethod]");
    return [NSObject new];
}

@end
