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

Class MUCreateClass(const char *className, const char *superClass);

void MUHookInstanceMessageEx(Class _class, SEL sel, IMP imp, IMP *result);

void MUHookClassMessageEx(Class _class, SEL sel, IMP imp, IMP *result);

void MUAddInstanceMessageEx(Class _class, SEL sel, IMP imp, const char *typeEncoding, IMP *result);

void MUAddClassMessageEx(Class _class, SEL sel, IMP imp, const char *typeEncoding, IMP *result);

Class MUAllocateClassPair(Class superClass, const char *className, size_t extraBytes);

void MURegisterClassPair(Class _class);

int MURebindSymbol(const char *symbol, void *imp, void **result);
