package ct01;
import java.util.Scanner;
/*
* 정수를 읽어서 2진수 , 8진수, 16진수로 출력하는 프로그램을 작성하라. 역수를 16진수 부동소수점으로 출력하라
* */

import java.util.Scanner;

public class ex1 {
    public static void main(String[] args){
        System.out.println("연습문제 1번");
        Scanner in = new Scanner(System.in);
        int number = in.nextInt();
        System.out.println("input number is " + number);
        System.out.println(Integer.toBinaryString(number));
        System.out.println(Integer.toOctalString(number));
        System.out.println(Integer.toHexString(number));
        System.out.printf("%x",number);



    }
}
