
public class MiniDuckSimulator {

	public static void main(String [] args) {
		Duck mallard = new MallardDuck();
		((MallardDuck) mallard).display();
		mallard.performQuack();
		mallard.performFly();

		System.out.println("-----------------------------");
	/*
	 * 이 오리는 MallardDuck() 과 다르게 동적으로 행동을 결정함
	 * */
		Duck model = new ModelDuck();
		((ModelDuck) model).display();
		model.performFly();
		model.performQuack();
	
	/*
	 * 여기서 객체 생성할 때 생성한 행동을 변경함.
	 * */
		model.setFlyBehavior(new FlyRocketPowered());
		model.performFly();
		model.setQuackBehavior(new MuteQuack());
		model.performQuack();
	}
}
