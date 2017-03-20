//
//  MUHook.h
//
//  Created by Shuang Wu on 2017/2/9.
//
//  Copyright Shuang Wu 2017
//

#import <Foundation/Foundation.h>
#import <objc/runtime.h>

/**
 *  Hook Usage
 *
 *  In .h file:
 *
 *  MUHookInitClassFunction(MUTableViewController);
 *
 *  In .m file:
 *
 *  MUHHookImplementation(MUTableViewController, cellForRowAtIndexPath, UITableViewCell *, UITableView *tableView, NSIndexPath *indexPath) {
 *      UITableViewCell *cell = MUHOrig(MUTableViewController, cellForRowAtIndexPath, UITableView *tableView, NSIndexPath *indexPath);
 *      // some code to modify cell
 *      return cell;
 *  }
 *
 *  void MUHInitClass(MUTableViewController) {
 *      MUHookMessageEx(MUTableViewController, @selector(tableView:cellForRowAtIndexPath:), cellForRowAtIndexPath);
 *  }
 *
 *  In main():
 *
 *  MUHookInitClass(MUTableViewController);
 *
 **/

#define MUHInitClass(c) init_##c ()

#pragma mark - Implementation

#define MUHImplementation(c, name, returnType, args...) \
static returnType (*_unique_ori##$##c##$##name) ( c * obj, SEL, ##args );\
static returnType   _unique_new##$##c##$##name  ( c * self, SEL _cmd, ##args )

#pragma mark - Execute Orig

#define MUHOrig(c, name, args...) !_unique_ori$##c##$##name ? 0 : _unique_ori$##c##$##name (self, _cmd, ##args)

#pragma mark - Hook

#define MUHHookMessage(c, sel, name) \
MUHookMessageEx(objc_getClass( #c ), sel, (IMP)&_unique_new$##c##$##name, (IMP*)&_unique_ori$##c##$##name);

#pragma mark - Create

#define MUHAllocateClass(sc, c, es) Class _unique_class$##c = MUAllocateClassPair(objc_getClass( #sc ), #c , es)

#define MUHAddMessage(c, sel, name, encode) MUAddMessageEx(_unique_class$##c, sel, (IMP)&_unique_new$##c##$##name, #encode , (IMP*)&_unique_ori$##c##$##name)

#define MUHRegisterClass(c) MURegisterClassPair(_unique_class$##c)

#pragma mark - Function

void MUHookMessageEx(Class _class, SEL sel, IMP imp, IMP *result);

void MUAddMessageEx(Class _class, SEL sel, IMP imp, const char *typeEncoding, IMP *result);

Class MUAllocateClassPair(Class superClass, const char *className, size_t extraBytes);

void MURegisterClassPair(Class _class);
