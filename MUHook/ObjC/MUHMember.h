//
//  MUHMember.h
//  MUHookDemo
//
//  Created by Magic-Unique on 2018/11/23.
//  Copyright © 2018年 unique. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, MUHAssociationType) {
    MUHAssociationType_strong,
    MUHAssociationType_assign,
    MUHAssociationType_copy,
    MUHAssociationType_weak,
};

#if DEBUG == 1

#define _MUHAsctType(mm) ({\
__unused MUHAssociationType strong = MUHAssociationType_strong;\
__unused MUHAssociationType assign = MUHAssociationType_assign;\
__unused MUHAssociationType copy = MUHAssociationType_copy;\
__unused MUHAssociationType weak = MUHAssociationType_weak;\
mm;\
})

#else

#define _MUHAsctType(mm) (MUHAssociationType_##mm)

#endif

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

- (MUHMember *)_asct:(MUHAssociationType)type;

- (id)objectForKeyedSubscript:(NSString *)key;

- (void)setObject:(id)obj forKeyedSubscript:(NSString *)key;

@end
