//
//  MUHookRelease.h
//  MUHookDemo
//
//  Created by Magic-Unique on 2018/12/27.
//  Copyright © 2018 unique. All rights reserved.
//

#import <Foundation/Foundation.h>

#if DEBUG == 1
#else

#pragma mark - Main

#define MUHMain                                 static __attribute__((constructor)) initialize

#pragma mark - Quick Statement

#define MUHClass(c)                             objc_getClass(#c)

#define MUHSendClassMsg(c, factory)             [MUHClass(c) factory]

#define MUHAlloc(c)                             [MUHClass(c) alloc]

#define MUHAllocInitWith(c, init)               [MUHAlloc(c) init]

#define MUHInitClass(c)                         init_##c ()

#pragma mark - Implementation

#define MUHInstanceImplementation(c, name, returnType, args...) \
__unused static returnType (*_unique_objc_ori$##c##$##name)   ( c * self, SEL _cmd, ##args ); \
__unused static returnType   _unique_objc_new$##c##$##name    ( c * self, SEL _cmd, ##args )

#define MUHClassImplementation(c, name, returnType, args...) \
__unused static returnType (*_unique_objc_ori$##c##$##name)   ( __strong const Class self, SEL _cmd, ##args ); \
__unused static returnType   _unique_objc_new$##c##$##name    ( __strong const Class self, SEL _cmd, ##args )

#define MUHSymbolImplementation(symbol, returnType, args...) \
__unused static returnType (*_unique_symbol_ori$##symbol)(args); \
__unused static returnType   _unique_symbol_new$##symbol (args)

#pragma mark - Execute Orig or Super

#define MUHOrig(c, name, args...)               (!_unique_objc_ori$##c##$##name?0:_unique_objc_ori$##c##$##name (self, _cmd, ##args))
#define MUHSuper(c, name, args...)              (!_unique_objc_ori$##c##$##name?0:_unique_objc_ori$##c##$##name (self, _cmd, ##args))

#define MUHSymbolOrig(symbol, args...)          (_unique_symbol_ori$##symbol(args))

#pragma mark - Hook

#define MUHHookInstanceMessage(c, name, sel) \
MUHookInstanceMessageEx(objc_getClass( #c ), @selector(sel), (IMP)&_unique_objc_new$##c##$##name, (IMP*)&_unique_objc_ori$##c##$##name)

#define MUHHookClassMessage(c, name, sel) \
MUHookClassMessageEx(objc_getClass( #c ), @selector(sel), (IMP)&_unique_objc_new$##c##$##name, (IMP*)&_unique_objc_ori$##c##$##name)

#define MUHHookSymbolFunction(symbol) \
MURebindSymbol(#symbol, _unique_symbol_new$##symbol, (void *)&_unique_symbol_ori$##symbol)

#pragma mark - Create

#define MUHCreateClass(c, sc) MUCreateClass(#c, #sc)

#define MUHAddInstanceMethod(c, name, sel, encode) \
MUAddInstanceMessageEx(objc_getClass( #c ), @selector(sel), (IMP)&_unique_objc_new$##c##$##name, #encode , (IMP*)&_unique_objc_ori$##c##$##name)

#define MUHAddClassMethod(c, name, sel, encode) \
MUAddClassMessageEx(objc_getMetaClass( #c ), @selector(sel), (IMP)&_unique_objc_new$##c##$##name, #encode , (IMP*)&_unique_objc_ori$##c##$##name)

#endif
