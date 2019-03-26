//
//  NSObject+MUHook.h
//  MUHookDemo
//
//  Created by Magic-Unique on 2018/4/16.
//  Copyright © 2018年 unique. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, MUHAssosiationType) {
    MUHAssosiationTypeStrong,
    MUHAssosiationTypeAssign,
    MUHAssosiationTypeCopy,
    MUHAssosiationTypeWeak,
};

#define _MUHAsctType(mm) ({\
__unused MUHAssosiationType strong = MUHAssosiationTypeStrong;\
__unused MUHAssosiationType assign = MUHAssosiationTypeAssign;\
__unused MUHAssosiationType copy = MUHAssosiationTypeCopy;\
__unused MUHAssosiationType weak = MUHAssosiationTypeWeak;\
mm;\
})

@interface NSObject (MUHook)

- (void)muh_setAssosiationObject:(id)object forKey:(NSString *)key type:(MUHAssosiationType)type;

- (id)muh_getAssosiationForKey:(NSString *)key;

@end
