//
//  MUExtendsSubClass.h
//  MUHookDemo
//
//  Created by Magic-Unique on 2017/8/15.
//  Copyright © 2017年 unique. All rights reserved.
//

#import "MUExtendsSuperClass.h"
#import <MUHook/MUHook.h>

@interface MUExtendsSubClass : MUExtendsSuperClass

@property (nonatomic, copy) NSString *name;

@property (nonatomic, assign) NSUInteger age;

@property (nonatomic, assign) NSRect frame;

@property (nonatomic, strong) NSString *nickName;

@end

void MUHInitClass(MUExtendsSubClass)(void);
