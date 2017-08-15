//
//  MUExtendsSuperClass.h
//  MUHookDemo
//
//  Created by Shuang Wu on 2017/8/15.
//  Copyright © 2017年 unique. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MUExtendsSuperClass : NSObject

+ (instancetype)superInstanceWithInt:(NSInteger)integer object:(id)object;

- (void)superVoidMethodWithObject:(id)object;

- (id)superReturnValueMethod;

@end
