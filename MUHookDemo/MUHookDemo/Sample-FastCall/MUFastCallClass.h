//
//  MUFastCallClass.h
//  MUHookDemo
//
//  Created by Magic-Unique on 2017/8/15.
//  Copyright © 2017年 unique. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MUFastCallClass : NSObject

- (instancetype)initWithInteger:(NSInteger)integer object:(id)object;

+ (instancetype)instanceWithInteger:(NSInteger)integer object:(id)object;

@end
