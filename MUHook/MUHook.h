//
//  MUHook.h
//
//  Created by Magic-Unique on 2017/2/9.
//
//  Copyright Magic-Unique 2017
//

#import <Foundation/Foundation.h>
#import <objc/runtime.h>
#import <objc/message.h>
#import "MUHRuntime.h"
#import "NSObject+MUHook.h"
#import "MUHMember.h"
#import "MUClassCreator.h"

#if DEBUG == 1

/*
 In Debug mode, MUHook will import more define and code to support Xcode-Code-Tips
 */
#import "MUHookDebug.h"

#else

/*
 In Release mode, Use minimum code to improve performance but without Xcode-Code-Tips
 */
#import "MUHookRelease.h"

#endif

#pragma mark - Function

void MUHookMessageEx(Class _class, SEL sel, IMP imp, IMP *result);

void MUAddMessageEx(Class _class, SEL sel, IMP imp, NSString *typeEncoding, IMP *result);

int MURebindSymbol(const char *symbol, void *imp, void **result);
