# MUHook

Hook ObjC method without jailbreak.

非越狱环境 hook 工具。

## Feature

1. Hook methods of ObjC class. Hook一个二进制文件中的类的对象方法
2. Create subclass extends ObjC class. 创建一个二进制文件中的类的子类
3. Create instances of the classes in binary file, 创建一个二进制文件中的类的对象
4. Send message to class in binary file. 向二进制文件中的类发消息（工厂方法）

## Usage - Fast Call 快速发消息

**orig code**

```objective-c
@interface MUFastCallClass : NSObject
{
	NSString *_name;
}

- (instancetype)initWithInteger:(NSInteger)integer object:(id)object;

+ (instancetype)instanceWithInteger:(NSInteger)integer object:(id)object;

@end
```

**hook code**

```objective-c
MUFastCallClass *instance = MUHAllocInitWith(MUFastCallClass, initWithInteger:1 object:[NSObject new]); // fast alloc instance
NSObject *obj = MUHGetObjectAsct(instance, object);// fast get associated object
MUHSetObjectAsct(instance, object, nil); // fast set associated object
NSLog(@"%@", obj);
NSString *name = MUHGetObjectIvar(instance, _name);
MUHSetObjectIvar(instance, _name, @"New Name");
```

**See more: MUHookDemo/Sample-FastCall**

## Usage - Hook Method

**orig code**

```objective-c
@interface MUHookClass : NSObject

+ (instancetype)instanceWithInt:(NSInteger)integer object:(id)object;

- (void)voidMethodWithObject:(id)object;

- (id)returnValueMethod;

@end
```

**hook code**

```objective-c
//	Define a class method named 'factory' to hook +[MUHookClass instanceWithInt:object:]
MUHClassImplementation(MUHookClass, factory, MUHookClass *, NSInteger integer, id object) {
    NSLog(@"__hook__ -[MUHookClass instanceWithInt:object:]");
    MUHookClass *instance = MUHOrig(MUHookClass, factory, integer, object);
    return instance;
}

//	Define an instance method named 'voidMethod' to hook
//	-[MUHookClass voidMethodWithObject:]
MUHInstanceImplementation(MUHookClass, voidMethod, void, id object) {
    NSLog(@"__hook__ -[MUHookClass voidMethodWithObject:]");
    MUHOrig(MUHookClass, voidMethod, object);
}

//	Define an instance method named 'returnMethod' to hook
//	-[MUHookClass returnValueMethod]
MUHInstanceImplementation(MUHookClass, returnMethod, id) {
    NSLog(@"__hook__ -[MUHookClass returnValueMethod]");
    return MUHOrig(MUHookClass, returnMethod);
}

//	Execute hook
void MUHInitClass(MUHookClass) 
  	//	Hook class method：ClassName,MethodName,SEL
    MUHHookClassMessage(MUHookClass, factory, instanceWithInt:object:);
  	//	Hook instance method：ClassName,MethodName,SEL
    MUHHookInstanceMessage(MUHookClass, voidMethod, voidMethodWithObject:);
    MUHHookInstanceMessage(MUHookClass, returnMethod, returnValueMethod);
}

```

**See more: MUHookDemo/Sample-Hook**

## Usage - Create subclass

**orig code**

```objective-c
@interface MUExtendsSuperClass : NSObject

+ (instancetype)superInstanceWithInt:(NSInteger)integer object:(id)object;

- (void)superVoidMethodWithObject:(id)object;

- (id)superReturnValueMethod;

@end
```

**hook code**

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
	 */
  	//	Create a subclass
    MUHCreateClass(MUExtendsSubClass, MUExtendsSuperClass);
  	//	Add class method：ClassName,MethodName,SEL,typeencoding
    MUHAddClassMethod(MUExtendsSubClass, subInstance, superInstanceWithInt:object:, @@:q@);
  	//	Add instance method：ClassName,MethodName,SEL,typeencoding
    MUHAddInstanceMethod(MUExtendsSubClass, voidMethod, superVoidMethodWithObject:, v@:@);
    MUHAddInstanceMethod(MUExtendsSubClass, returnMethod, superReturnValueMethod, @@:);
}
```

**See more: MUHookDemo/Sample-Extends**

## Usage - Hook Symbol function (Power by fishhook)

```objc
// Define function to hook malloc()
MUHSymbolImplementation(malloc, void *, size_t size) {
    printf("malloc(%lu)\n", size);
    return MUHSymbolOrig(malloc, size);
}

// Define function to hook getchar()
MUHSymbolImplementation(getchar, int) {
    printf("New temp\n");
    return MUHSymbolOrig(getchar);
}

void initMUHookSymbolSample() {
    MUHHookSymbolFunction(getchar);
    MUHHookSymbolFunction(malloc);
}

```