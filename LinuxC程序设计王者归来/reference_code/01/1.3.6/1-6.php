<?php
	class foo
	{
	//类foo包含一个成员变量x
	private $x;
	//默认构造函数
	public function __construct()
	{
		$this->x = "Construction is called";
	}
	// 带参数的构造函数
	public function __construct($x)
	{
		$this->x = $x;
	}
	// 析构函数
	public function __destruct()
	{
		printf("Destruction is called!");
	}
	//设置成员变量x的值
	public function setX($x) 
	{ 
		$this->x = $x; 
	} 
	//访问成员变量的x值
	public function getX() 
	{ 
		return $this->x; 
	} 
	// 输出变量的值
	public function display()
	{
		printf($this->x);
	}
	}
	//声明一个foo类型的变量 a
	$a = new foo(); 
	$a->display();
	//对变量a重新赋值
	$a->setX("Hello World!");
	$a->display();
	//声明一个foo类型的变量 a
	$b = new foo("Welcome to php");
	$b->display();
?>
