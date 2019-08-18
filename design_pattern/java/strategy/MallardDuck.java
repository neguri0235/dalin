
public class MallardDuck extends Duck{
	
	// MallardDuck 객체 생성할 때, 생성자 안에다가 객체의 특성을 처리하도록 함
	
	public MallardDuck() {
		quackBehavior = new Squeak();
		flyBehavior = new FlyWithWings();
	}
	
	public void display() {
		System.out.println("저는 물 오리 입니다");
	}
	
}
