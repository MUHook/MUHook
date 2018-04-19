//
//  MUHookSymbolSample.m
//  MUHookDemo
//
//  Created by 吴双 on 2018/4/15.
//  Copyright © 2018年 unique. All rights reserved.
//

#import "MUHookSymbolSample.h"
#import "MUHook.h"

MUHSymbolImplementation(malloc, void *, size_t size) {
    printf("malloc(%lu)\n", size);
    return MUHSymbolOrig(malloc, size);
}

MUHSymbolImplementation(getchar, int) {
    printf("New temp\n");
    return MUHSymbolOrig(getchar);
}

void initMUHookSymbolSample() {
    MUHHookSymbolFunction(getchar);
    MUHHookSymbolFunction(malloc);
}
