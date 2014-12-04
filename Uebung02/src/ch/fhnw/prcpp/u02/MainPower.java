package ch.fhnw.prcpp.u02;

public class MainPower {

	public static void main(String[] args) {
		//Load c++ code
		System.loadLibrary("NativeFunctions");
		Matrix a = new Matrix(2, 2);
		System.out.println("a*a");
		System.out.println(a.multiply(a));
		System.out.println("a^2");
		System.out.println(a.power(2));
		System.out.println("a*a*a");
		System.out.println(a.multiply(a).multiply(a));
		System.out.println("a^3");
		System.out.println("a*a*a*a");
		System.out.println(a.multiply(a).multiply(a).multiply(a));
		System.out.println("a^4");
		System.out.println(a.power(4));
		System.out.println("a^9");
		System.out.println(a.power(9));
		System.out.println("a^9 native");
		System.out.println(a.powerNative(9));
		Matrix b = new Matrix(200, 200);
		long startJava = System.currentTimeMillis();
		Matrix b51 = b.power(51);
		long startNative = System.currentTimeMillis();
		Matrix b51n = b.powerNative(51);
		long endNative = System.currentTimeMillis();
		System.out.println("Same? " + b51.equals(b51n)); //Same with tolerance
		System.out.println("Same Exact? " + b51.equals(b51n, 0)); //Exactly the same (every bit)
		System.out.println("Time Java: " + (startNative - startJava));
		System.out.println("Time Native: " + (endNative - startNative));

		/**
		 * With Debug:
		 * Same? true
		 * Same Exact? true
		 * Time Java: 84
		 * Time Native: 216 
		 */
		/**
		 * With Release:
		 * Same? true
		 * Same Exact? true
		 * Time Java: 85
		 * Time Native: 65 
		 */
	}

}
