//
//  MUHRuntime.h
//  MUHookDemo
//
//  Created by Shuang Wu on 2017/3/30.
//  Copyright © 2017年 unique. All rights reserved.
//

#ifndef MUHRuntime_h
#define MUHRuntime_h

#define MUHDefinedSend(var, returnType, argsTypes...)   returnType (* var )(id, SEL, ##argsTypes) = (returnType (*)(id,SEL, ##argsTypes))objc_msgSend
#define MUHMakeMsgSend(returnType, argsTypes...)        ((returnType (*)(id,SEL, ##argsTypes))objc_msgSend)
#define MUHCallMsgSend(msgsend, obj, sel, args...)      ( msgsend (obj, @selector(sel), ##args))

#endif /* MUHRuntime_h */
