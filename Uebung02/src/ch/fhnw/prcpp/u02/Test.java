package ch.fhnw.prcpp.u02;

/**
 * Test class from Aufgabe02
 * @author JP
 */
public class Test {
	public static native void display();
	public static native int increment(int value);
	public static void main(String[] args){
		//Load c++ code
		System.loadLibrary("NativeFunctions");
		display();
		int i = 5;
		System.out.println(String.format("%d -> %d", i, increment(i)));
	}
}
