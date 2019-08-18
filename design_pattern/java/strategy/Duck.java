
public  class Duck {
	
	FlyBehavior flyBehavior;
	QuackBehavior quackBehavior;
	
	public Duck (){
		
	}
	void performQuack() {
		quackBehavior.quack();
	}
	
	void performFly() {
		flyBehavior.fly();
	}
}
