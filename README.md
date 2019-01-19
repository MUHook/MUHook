# MUHook

A **powerful**, **quickly**, **light-weight** hooking tool on iOS device without jailbreak.

在非越狱 iOS 平台上的强大的、快速的、轻量级 Hook 工具。

## Feature 功能

1. Hook methods of ObjC class. Hook一个二进制文件中的类的对象方法
2. Create subclass extends ObjC class. 创建一个二进制文件中的类的子类
	* 新增或重写方法
	* 新增实例变量
	* 新增属性
3. Create instances of the classes in binary file, 创建一个二进制文件中的类的对象
4. Send message to class in binary file. 向二进制文件中的类发消息（工厂方法）
5. Support code hinting in Xcode.	支持 Xcode 的代码提示

## Installation 使用

**CocoaPods**

```ruby
pod 'MUHook'
```

**Source**

Drag *MUHook*、*fishhook* folder to your project

**Import**

```objc
#import <MUHook/MUHook.h>
```

## Usage - Fast Call 快速发消息

**orig code 原代码**

```objective-c
@interface MUFastCallClass : NSObject
{
	NSString *_name;
}

- (instancetype)initWithInteger:(NSInteger)integer object:(id)object;

+ (instancetype)instanceWithInteger:(NSInteger)integer object:(id)object;

@end
```

**hook code 插件代码**

```objective-c
//	Alloc an instance without linking.
//	创建一个对象，如果直接 [[Class alloc] init] 调用，编译时候报 link 错误
MUFastCallClass *instance = MUHAllocInitWith(MUFastCallClass, initWithInteger:1 object:[NSObject new]);

//	Get associated object
//	取关联对象
NSObject *obj = MUHAsct(instance, object, strong);

//	Set associated object, supporting: strong/weak/assign/copy
//	设置关联对象，最后一个值支持: strong、weak、assign、copy
MUHAsct(instance, object, strong) = nil;

//	Get ivar value
//	取实例变量
NSString *name = MUHIvar(instance, _name);

//	Set ivar value
//	设置实例变量
MUHIvar(instance, _name) = @"New Name";
```

**See more: MUHookDemo/Sample-FastCall**

## Usage - Hook Method 勾住方法

**orig code 原代码**

```objective-c
@interface MUHookClass : NSObject

+ (instancetype)instanceWithInt:(NSInteger)integer object:(id)object;

- (void)voidMethodWithObject:(id)object;

- (id)returnValueMethod;

@end
```

**hook code 插件代码**

```objective-c
//	Define a class method named 'factory' to hook +[MUHookClass instanceWithInt:object:]
//	定义一个新的类方法实现体，称之'factory'（该名称只要自己保证类内唯一性即可）
MUHClassImplementation(MUHookClass, factory, MUHookClass *, NSInteger integer, id object) {
    NSLog(@"__hook__ -[MUHookClass instanceWithInt:object:]");
    MUHookClass *instance = MUHOrig(MUHookClass, factory, integer, object);
    return instance;
}

//	Define an instance method named 'voidMethod' to hook
//	-[MUHookClass voidMethodWithObject:]
//	定义一个新的带参数、无返回值的实例方法实现体
MUHInstanceImplementation(MUHookClass, voidMethod, void, id object) {
    NSLog(@"__hook__ -[MUHookClass voidMethodWithObject:]");
    MUHOrig(MUHookClass, voidMethod, object);
}

//	Define an instance method named 'returnMethod' to hook
//	-[MUHookClass returnValueMethod]
//	定义一个新的带返回值，无参数的实例方法体
MUHInstanceImplementation(MUHookClass, returnMethod, id) {
    NSLog(@"__hook__ -[MUHookClass returnValueMethod]");
    return MUHOrig(MUHookClass, returnMethod);
}

//	Execute hook
//	You need call the function MUHInitClass() in MUHMain()
//	执行 Hook
//	请在 MUHMain() 中手动调用该函数以生效以上 hook
void MUHInitClass(MUHookClass) 
  	//	Hook class method：ClassName,MethodName,SEL
  	//	参数列表：类名，自己取得方法名（与上面的方法体相同），SEL
    MUHHookClassMessage(MUHookClass, factory, instanceWithInt:object:);
  	//	Hook instance method：ClassName,MethodName,SEL
  	//	参数列表：类名，自己取得方法名（与上面的方法体相同），SEL
    MUHHookInstanceMessage(MUHookClass, voidMethod, voidMethodWithObject:);
    MUHHookInstanceMessage(MUHookClass, returnMethod, returnValueMethod);
}

//	In the other files(such as: Main.m).
//	Create an entry function to excute all hook.
//	在某个文件中（如 Main.m）
//	创建一个 MUHMain() 函数，来执行以上所有类的 Hook。
void MUHMain() {
	MUHInitClass(MUHookClass);
	MUHInitClass(...);
	...
}

```

**See more: MUHookDemo/Sample-Hook**

## Usage - Create subclass 创建子类

**orig code 原父类代码**

```objective-c
@interface MUExtendsSuperClass : NSObject

+ (instancetype)superInstanceWithInt:(NSInteger)integer object:(id)object;

- (void)superVoidMethodWithObject:(id)object;

- (id)superReturnValueMethod;

@end
```

**hook code 插件子类代码**

```objective-c
//	Define a class method named 'subInstance' to override
//	+[MUExtendsSuperClass superInstanceWithInt:object:]
MUHClassImplementation(MUExtendsSubClass, subInstance, MUExtendsSubClass *, NSInteger integer, id object) {
    NSLog(@"+[MUExtendsSubClass superInstanceWithInt:(NSInteger)%ld object:(id)%@]", integer, object);
    integer += 1; // Modify arguments
    MUExtendsSubClass *subInstancce = MUHSuper(MUExtendsSubClass, subInstance, integer, object);
    return subInstancce;
}

//	Define an instance method named 'voidMethod' to override
//	+[MUExtendsSuperClass superVoidMethodWithObject:]
MUHInstanceImplementation(MUExtendsSubClass, voidMethod, void, id object) {
    NSLog(@"+[MUExtendsSubClass superVoidMethodWithObject:(id)%@]", object);
    object = [MUExtendsSuperClass new]; // Modify arguments
    MUHSuper(MUExtendsSubClass, voidMethod, object);
}

//	Define an instance method named 'returnMethod' to override
//	+[MUExtendsSuperClass superReturnValueMethod]
MUHInstanceImplementation(MUExtendsSubClass, returnMethod, id) {
    NSLog(@"+[MUExtendsSubClass superReturnValueMethod]");
    id returnValue = MUHSuper(MUExtendsSubClass, returnMethod);
    return returnValue;
}

void MUHInitClass(MUExtendsSubClass) {
	/**
	 * PS: When you call MUHCreateClass(), it will call createClass() and registerClassPair().
	 * So you can't add any ivar to this class.
	 * Please use association-object if you want to add propertys to the new class.
	 * 
	 * 注意：当你调用 MUHCreateClass()，会自动调用 createClass() 和 registerClassPair() 函数。
	 * 所以你不能自定义添加实例变量到新的子类中
	 * 如果你需要定义属性，请使用关联对象
	 */
  	//	Create a subclass
    MUHCreateClass(MUExtendsSubClass, MUExtendsSuperClass);
    
	/**
	 * PS: If you want to add ivar to the new class, you must use MUHook (> 1.3.0).
	 * And use this code:
	 * Ivar only support: `strong` for object , `assign` for base type.
	 * 
	 * 注意：当你想加入实例变量到新的类中时，你必须使用 1.3.0 以上的 MUHook，并使用一下代码：
	 * 实例变量只支持 `strong` 修饰对象，`assign` 修饰基本数据类型。
	 */
    MUHCreateClass(MUExtendsSubClass, MUExtendsSuperClass) withIvarList {
    	MUHAddIvar(NSString *, _name);
    	MUHAddIvar(NSUInteger, _age);
    	MUHAddIvar(CGRect, _frame);
    };
    
    MUHAddClassMethod(MUExtendsSubClass, subInstance, superInstanceWithInt:object:, @@:q@);
    MUHAddInstanceMethod(MUExtendsSubClass, voidMethod, superVoidMethodWithObject:, v@:@);
    MUHAddInstanceMethod(MUExtendsSubClass, returnMethod, superReturnValueMethod, @@:);
}
```

**See more: MUHookDemo/Sample-Extends**

## Usage - Hook Symbol function 符号函数 (Power by fishhook) 

```objc
// Define function to hook malloc()
//	定义一个新的 malloc 函数实现体
MUHSymbolImplementation(malloc, void *, size_t size) {
    printf("malloc(%lu)\n", size);
    return MUHSymbolOrig(malloc, size);
}

// Define function to hook getchar()
//	定义一个新的 getchar 函数实现体
MUHSymbolImplementation(getchar, int) {
    printf("New temp\n");
    return MUHSymbolOrig(getchar);
}

//	Hook functions.
//	You need call the function in MUHMain().
//	执行本文件的模块 hook
//	该函数需要在 MUHMain() 中被调用，以上实现才生效
void initMUHookSymbolSample() {
    MUHHookSymbolFunction(getchar);
    MUHHookSymbolFunction(malloc);
}

```