//
//  MUClass.h
//  MUHookDemo
//
//  Created by Shuang Wu on 2017/3/20.
//  Copyright © 2017年 unique. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MUClass : NSObject

@property (nonatomic, copy) NSString *name;

- (void)setName2:(NSString *)name2;
- (NSString *)name2;

@end



@interface MUSubClass : MUClass

@end

@interface MUSubSubClass : MUSubClass

@end
