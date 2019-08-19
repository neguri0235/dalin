
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
	
	/*
	 * 동적으로 행동을 설정 할 수 있도록 setter를 추가함.
	 * 클래스 생성시가 아니라 런타임에 동적으로 행동을 변경하고자 할때 아래 setter를 호출
	 * */
	public void setFlyBehavior(FlyBehavior fb) {
		flyBehavior = fb;
	}
	
	public void setQuackBehavior(QuackBehavior qb) {
		quackBehavior = qb;
	}
}
