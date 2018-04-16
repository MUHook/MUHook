//
//  NSObject+MUHook.h
//  MUHookDemo
//
//  Created by 吴双 on 2018/4/16.
//  Copyright © 2018年 unique. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, MUHAssosiationType) {
    MUHAssosiationType_strong,
    MUHAssosiationType_assign,
    MUHAssosiationType_copy,
    MUHAssosiationType_weak,
};

@interface NSObject (MUHook)

- (void)muh_setAssosiationObject:(id)object forKey:(NSString *)key type:(MUHAssosiationType)type;

- (id)muh_getAssosiationForKey:(NSString *)key;

@end
