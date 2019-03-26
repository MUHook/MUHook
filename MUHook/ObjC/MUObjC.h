//
//  MUObjC.h
//  MUHook
//
//  Created by Magic-Unique on 2019/3/26.
//

#import <Foundation/Foundation.h>
#import <objc/runtime.h>
#import <objc/message.h>
#import "MUHRuntime.h"
#import "MUHMember.h"
#import "MUClassCreator.h"
#import "MUPropertyCreator.h"

#if DEBUG == 1

/*
 In Debug mode, MUHook will import more define and code to support Xcode-Code-Tips
 */
#import "MUObjC+Debug.h"

#else

/*
 In Release mode, Use minimum code to improve performance but without Xcode-Code-Tips
 */
#import "MUObjC+Release.h"

#endif

#pragma mark - Function

void MUHookMessageEx(Class _class, SEL sel, IMP imp, IMP *result);

void MUAddMessageEx(Class _class, SEL sel, IMP imp, NSString *typeEncoding, IMP *result);
