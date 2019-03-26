//
//  MUPropertyCreator.h
//  MUHookDemo
//
//  Created by 吴双 on 2019/1/25.
//  Copyright © 2019 unique. All rights reserved.
//

#import <Foundation/Foundation.h>

#define MUHAddPropertyGetter(c, type, name, getter) \
[MUPropertyCreator add:MUHClass(c) sel:@selector(getter) typeEncoding:MUHEncode(type,id,SEL)][nil] = ^type(c *self)

#define MUHAddPropertySetter(c, type, name, setter) \
[MUPropertyCreator add:MUHClass(c) sel:@selector(setter) typeEncoding:MUHEncode(void,id,SEL,type)][nil] = ^(c *self, type name)

@interface MUPropertyCreator : NSObject

@property (nonatomic, strong, readonly) Class cls;

@property (nonatomic, assign, readonly) SEL sel;

@property (nonatomic, strong, readonly) NSString *typeEncoding;

+ (instancetype)add:(Class)cls sel:(SEL)sel typeEncoding:(NSString *)typeEncoding;

- (void)setObject:(id)obj forKeyedSubscript:(NSString *)key;

@end
