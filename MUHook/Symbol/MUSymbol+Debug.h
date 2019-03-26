//
//  MUSymbol+Debug.h
//  MUHookDemo
//
//  Created by Magic-Unique on 2019/3/26.
//  Copyright © 2019 unique. All rights reserved.
//

#if DEBUG == 1

/**
 Create function implementation

 @param symbol Function name
 @param returnType Function return type
 @param args... Function arguments list
 */
#define _MUHSymbolImplementation(symbol, returnType, args...) \
_Pragma("clang diagnostic push") \
_Pragma("clang diagnostic ignored \"-Wstrict-prototypes\"") \
__unused static returnType (*_unique_symbol_ori$##symbol)(args); \
__unused static returnType   _unique_symbol_new$##symbol (args) \
_Pragma("clang diagnostic pop")
#define MUHSymbolImplementation(symbol, returnType, args...) _MUHSymbolImplementation(symbol, returnType, ##args)


/**
 Call origin function

 @param symbol Function name
 @param args... Argument list
 */
#define _MUHSymbolOrig(symbol, args...)         ((void)&symbol,_unique_symbol_ori$##symbol(args))
#define MUHSymbolOrig(symbol, args...)          _MUHSymbolOrig(symbol, ##args)

/**
 Hook function

 @param symbol Function name
 */
#define _MUHHookSymbolFunction(symbol) \
{(void)&symbol;}MURebindSymbol(#symbol, _unique_symbol_new$##symbol, (void *)&_unique_symbol_ori$##symbol)
#define MUHHookSymbolFunction(symbol) _MUHHookSymbolFunction(symbol)

#else
#endif
