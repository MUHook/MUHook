//
//  MUSymbol.h
//  MUHookDemo
//
//  Created by Magic-Unique on 2019/3/26.
//  Copyright © 2019 unique. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "fishhook.h"

#if DEBUG == 1

#import "MUSymbol+Debug.h"

#else

#import "MUSymbol+Release.h"

#endif

/** Please use MUHHookSymbolFunction() */
extern int MURebindSymbol(const char *symbol, void *imp, void **result);
