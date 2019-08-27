package decorator;

public abstract class Beverage {
	
	String description = "이름 없음";
	
	public String getDescription() {
		return description;
	}
	
	public abstract double cost();
}
