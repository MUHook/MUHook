//
//  MUSymbol.m
//  MUHookDemo
//
//  Created by 吴双 on 2019/3/26.
//  Copyright © 2019 unique. All rights reserved.
//

#import "MUSymbol.h"

int MURebindSymbol(const char *symbol, void *imp, void **result) {
    return rebind_symbols((struct rebinding[1]){{symbol, imp, (void *)result}}, 1);
}
