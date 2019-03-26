//
//  MUHookMacro.h
//  MUHookDemo
//
//  Created by Magic-Unique on 2019/1/23.
//  Copyright © 2019 unique. All rights reserved.
//

#ifndef MUHookMacro_h
#define MUHookMacro_h

#import "MUHookMetaMacro.h"

#define MUHSTR(str)                     [NSString stringWithUTF8String:str]

#define _MUHEncode(INDEX, CONTEXT, VAR) MUHSTR(@encode(VAR)),

#define MUHEncode(...)                  [@[muhmacro_foreach_cxt(_MUHEncode,,,__VA_ARGS__)] componentsJoinedByString:@""]

#endif /* MUHookMacro_h */
