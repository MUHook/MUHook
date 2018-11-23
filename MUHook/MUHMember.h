//
//  MUHMember.h
//  MUHookDemo
//
//  Created by 吴双 on 2018/11/23.
//  Copyright © 2018年 unique. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NSObject+MUHook.h"

#define MUHIvar(obj, key)       [[MUHMember _ivar] _obj:obj][@#key]
#define MUHSelfIvar(key)        [[MUHMember _ivar] _obj:self][@#key]

#define MUHAsct(obj, key, mm)   [[[MUHMember _asct] _obj:obj] _asct:_MUHAsctType(mm)][@#key]
#define MUHSelfAsct(key, mm)    [[[MUHMember _asct] _obj:self] _asct:_MUHAsctType(mm)][@#key]

@interface MUHMember : NSObject

@property (nonatomic, strong, readonly) id object;

+ (MUHMember *)_ivar;
+ (MUHMember *)_asct;

- (MUHMember *)_obj:(id)object;
- (MUHMember *)_sel:(SEL)selector;

- (MUHMember *)_asct:(MUHAssosiationType)type;

- (id)objectForKeyedSubscript:(NSString *)key;

- (void)setObject:(id)obj forKeyedSubscript:(NSString *)key;

@end
