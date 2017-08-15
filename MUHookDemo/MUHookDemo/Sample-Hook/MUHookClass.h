//
//  MUHookClass.h
//  MUHookDemo
//
//  Created by Shuang Wu on 2017/8/15.
//  Copyright © 2017年 unique. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MUHookClass : NSObject

+ (instancetype)instanceWithInt:(NSInteger)integer object:(id)object;

- (void)voidMethodWithObject:(id)object;

- (id)returnValueMethod;

@end
