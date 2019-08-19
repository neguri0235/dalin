
// ModelDuck은 동적으로 행동을 변경하는 오리

public class ModelDuck extends Duck {
	
	public ModelDuck() {
		flyBehavior = new FlyNoWay();
		quackBehavior = new Quack();
	}
	
	public void display() {
		System.out.println("저는 모형 오리입니다");
	}
}
