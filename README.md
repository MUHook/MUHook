# MUHook

Hook ObjC method without jailbreak.

非越狱环境 hook 工具。

## Feature

1. Hook methods of ObjC class in binary file. Hook一个二进制文件中的类的方法
2. Create subclass extends ObjC class in binary file. 创建一个二进制文件中的类的子类

## Usage - Hook Method

```objc
// in UITableViewHook.m.h

void MUHInitClass(UITableViewController);
```

```objc
// in UITableViewHook.m

// Define Hook Method -[UITableViewController tableView:cellForRowAtIndexPath:]
MUHImplementation(UITableViewController, DataSourceCreateCell, UITableViewCell *, UITableView *tableView, NSIndexPath *indexPath) {
	UITableViewCell *cell = MUHOrig(UITableViewController, DataSourceCreateCell, tableView, indexPath);
	cell.backgroundColor = UIColor.whiteColor;
	return cell;
}

/* other define ... */

void MUHInitClass(UITableViewController) {
	MUHHookMessage(UITableViewController, DataSourceCreateCell, tableView:cellForRowAtIndexPath:);
	/* other method hook */
}

```

```objc
// in main()
int main() {
	MUHInitClass(UIViewController);
	return 0;
}
```

## Usage - Create subclass

```objc
// in .h

@interface MyTableViewController : UITableViewController

- (NSUInteger)numberOfRowsInSection:(NSUInteger)section;

@end

void MUHInitClass(MyTableViewController);
```

```objc
// in .m

// Define Override Method -[MyTableViewController viewDidLoad]
MUHImplementation(MyTableViewController, ViewDidLoad, void) {
	MUHOrig(MyTableViewController, ViewDidLoad); // [super viewDidLoad];
	self.title = @"TITLE";
}

// Define method -[MyTableViewController numberOfRowsInSection]
MUHImplementation(MyTableViewController, GetSectionRow, NSUInteger, NSUInteger section) {
	return [self.tableView numberOfRowsInSection:section];
}

void MUHInitClass(UIViewController) {
	MUHAllocateClass(UIViewController, MyViewController, 0);
	MUHAddMessage(MyViewController, GetSectionRow, numberOfRowsInSection:, i@:i);
	MUHAddMessage(MyViewController, ViewDidLoad, viewDidLoad, v@:);
	MUHRegisterClass(MyViewController);
}

```

```objc
// in main()
int main() {
	MUHInitClass(MyViewController);
}
```