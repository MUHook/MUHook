//
//  MUClassCreator.h
//  MUHookDemo
//
//  Created by Magic-Unique on 2019/1/5.
//  Copyright © 2019 unique. All rights reserved.
//

#import <Foundation/Foundation.h>

#if DEBUG == 1

#define MUHCreateClass(c, sc)   {(c *)0x0;(sc *)0x0;}[MUClassCreator _create:@#c extends:@#sc][@"register"]

#else

#define MUHCreateClass(c, sc)   [MUClassCreator _create:@#c extends:@#sc][@"register"]

#endif

#define withIvarList             = ^(Class  _Nonnull __unsafe_unretained _class)

#define MUHAddIvar(_type, _name) class_addIvar(_class, #_name, sizeof(_type), log2(_Alignof(_type)), @encode(_type));

@interface MUClassCreator : NSObject

+ (instancetype)_create:(NSString *)cls extends:(NSString *)sprCls;

- (void)setObject:(id)obj forKeyedSubscript:(NSString *)key;

- (id)objectForKeyedSubscript:(NSString *)key;

@end
