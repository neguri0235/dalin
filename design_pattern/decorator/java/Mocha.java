package decorator;

public class Mocha extends CondimentDecorator{
	Beverage beverage;
	
	public Mocha(Beverage beverage) {
		this.beverage = beverage;
	}
	
	public String getDescription() {
		return beverage.getDescription() + " " + ", 모카";
	}
	
	public double cost() {
		return 0.20 +  beverage.cost();
	}
}
