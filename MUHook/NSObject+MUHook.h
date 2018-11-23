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

#define _MUHAsctType(mm) ({\
__unused MUHAssosiationType strong = MUHAssosiationType_strong;\
__unused MUHAssosiationType assign = MUHAssosiationType_assign;\
__unused MUHAssosiationType copy = MUHAssosiationType_copy;\
__unused MUHAssosiationType weak = MUHAssosiationType_weak;\
mm;\
})

@interface NSObject (MUHook)

- (void)muh_setAssosiationObject:(id)object forKey:(NSString *)key type:(MUHAssosiationType)type;

- (id)muh_getAssosiationForKey:(NSString *)key;

@end
