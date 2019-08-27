package decorator;

public class StarbuzzCoffee {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
			Beverage order1 = new Espresso();
			System.out.println(order1.getDescription() + " $:" + order1.cost());
			
			Beverage order2 = new DarkRoast();
			order2 = new Mocha(order2);
			order2 = new Mocha(order2);
			order2 = new Whip(order2);
			System.out.println(order2.getDescription() + " $:" + order2.cost());
			
			Beverage order3 = new HouseBlend();
			order3 = new Soy(order3);
			order3 = new Mocha(order3);
			order3 = new Whip(order3);
			System.out.println(order3.getDescription() + " $:" + order3.cost());
	}

}
