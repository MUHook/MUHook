//
//  MUClass.m
//  MUHookDemo
//
//  Created by Magic-Unique on 2017/3/20.
//  Copyright © 2017年 unique. All rights reserved.
//

#import "MUClass.h"

@implementation MUClass

@end

@implementation MUSubClass

@end

@implementation MUSubSubClass

- (void)setName:(NSString *)name {
    NSLog(@"%s", __FUNCTION__);
    [super setName:name];
}

@end
