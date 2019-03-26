//
//  MUSymbol+Release.h
//  MUHookDemo
//
//  Created by 吴双 on 2019/3/26.
//  Copyright © 2019 unique. All rights reserved.
//


#define _MUHSymbolImplementation(symbol, returnType, args...) \
_Pragma("clang diagnostic push") \
_Pragma("clang diagnostic ignored \"-Wstrict-prototypes\"") \
__unused static returnType (*_unique_symbol_ori$##symbol)(args); \
__unused static returnType   _unique_symbol_new$##symbol (args)  \
_Pragma("clang diagnostic pop")
#define MUHSymbolImplementation(symbol, returnType, args...) _MUHSymbolImplementation(symbol, returnType, ##args)

#define _MUHSymbolOrig(symbol, args...)     (_unique_symbol_ori$##symbol(args))
#define MUHSymbolOrig(symbol, args...)      _MUHSymbolOrig(symbol, ##args)

#define _MUHHookSymbolFunction(symbol) \
MURebindSymbol(#symbol, _unique_symbol_new$##symbol, (void *)&_unique_symbol_ori$##symbol)
#define MUHHookSymbolFunction(symbol) _MUHHookSymbolFunction(symbol)
