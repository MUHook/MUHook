//
//  MUHookSample.m
//  MUHookDemo
//
//  Created by Magic-Unique on 2017/8/15.
//  Copyright © 2017年 unique. All rights reserved.
//

#import "MUHookSample.h"

MUHInstanceImplementation(NSUserDefaults, getInteger, NSInteger, NSString *key) {
    return MUHOrig(NSUserDefaults, getInteger, key);
}

void MUHInitClass(MUHookClass)(void) {
    MUHHookInstanceMessage(NSUserDefaults, getInteger, integerForKey:);
}
