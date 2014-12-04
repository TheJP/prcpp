package ch.fhnw.prcpp.u02;


public class Main {

	public static void main(String[] args) {
		//Load c++ code
		System.loadLibrary("NativeFunctions");
		Matrix a = new Matrix(6000, 400);
		Matrix b = new Matrix(300, 6000);
		long startJava = System.currentTimeMillis();
		Matrix r = a.multiply(b);
		long startNative = System.currentTimeMillis();
		Matrix n = a.multiplyNative(b);
		long endNative = System.currentTimeMillis();
		boolean same = r.equals(n);
		/*System.out.println("a");
		System.out.println(a);
		System.out.println("b");
		System.out.println(b);
		System.out.println("r java");
		System.out.println(r);
		System.out.println("r native");
		System.out.println(n);*/
		System.out.println("Same? " + same);
		System.out.println("Time Java: " + (startNative - startJava));
		System.out.println("Time Native: " + (endNative - startNative));
		/**
		 * With Debug:
		 * Same? true
		 * Time Java: 4024
         * Time Native: 7645
		 */
		/**
		 * With Release:
		 * Same? true
		 * Time Java: 3979
		 * Time Native: 3988
		 */
	}

}
