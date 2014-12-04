package ch.fhnw.prcpp.u02;

import java.util.Random;
import java.util.Stack;

/**
 * Arithmetic matrix from Aufgabe03
 * @author JP
 */
public class Matrix implements Cloneable {
	private int width;
	private int height;
	private double[] content;

	/**
	 * Initialize matrix with random values.
	 * The values are choosen inside the interval [0,1)
	 * @param width
	 * @param height
	 */
	public Matrix(int width, int height) {
		this.width = width;
		this.height = height;
		content = new double[width * height];
		Random r = new Random();
		for(int i = content.length - 1; i >= 0; --i){
			content[i] = r.nextDouble();
		}
	}

	/**
	 * Initialize matrix with the given value.
	 * @param width
	 * @param height
	 * @param value
	 */
	public Matrix(int width, int height, double value){
		this.width = width;
		this.height = height;
		content = new double[width * height];
		for(int i = content.length - 1; i >= 0; --i){
			content[i] = value;
		}
	}

	/**
	 * Returns the neutral Matrix with given dimension.
	 * @param dimension
	 * @return
	 */
	public static Matrix neutral(int dimension){
		Matrix result = new Matrix(dimension, dimension, 0);
		for(int i = 0; i < dimension; ++i){
			result.set(i, i, 1.0);
		}
		return result;
	}

	/**
	 * Get a single value out of the Matrix.
	 * @param x Column (0 based)
	 * @param y Row (0 based)
	 * @return Value stored at given Row and Column
	 */
	public double get(int x, int y){
		return content[x+(y*width)];
	}

	/**
	 * Set a single value in the Matrix.
	 * @param x Column (0 based)
	 * @param y Row (0 based)
	 * @param value Value to be stored at given Row and Column
	 */
	public void set(int x, int y, double value){
		content[x+(y*width)] = value;
	}

	/**
	 * Matrix multiplication.
	 * Result = this * m
	 * An exception is thrown, if invalid dimensions are multiplied
	 * @param m
	 * @return
	 */
	public Matrix multiply(Matrix m){
		if(m.height != this.width){ throw new IllegalArgumentException(); }
		Matrix result = new Matrix(m.width, this.height, 0);
		for(int y = 0; y < result.height; ++y){
			int index = y * result.width;
			for(int x = 0; x < result.width; ++x, ++index){
				double total = 0.0;
				for(int k = 0; k < m.height; ++k){
					total += this.content[k+(y*this.width)] * m.content[x+(k*m.width)];
				}
				result.content[index] = total;
			}
		}
		return result;
	}

	/**
	 * Matrix multiplication executed in native code.
	 * Result = this * m
	 * An exception is thrown, if invalid dimensions are multiplied
	 * @param m
	 * @return
	 */
	public Matrix multiplyNative(Matrix m){
		if(m.height != this.width){ throw new IllegalArgumentException(); }
		Matrix result = new Matrix(m.width, this.height, 0);
		Matrix.multiplyC(this.content, m.content, result.content, result.width, result.height, this.width);
		return result;
	}

	/**
	 * Native matrix multiplication code.
	 * R = A * B
	 * @param a Matrix A
	 * @param b Matrix B
	 * @param r Matrix R (Result)
	 * @param x R.width
	 * @param y R.height
	 * @param k A.width=B.height
	 */
	private static native void multiplyC(double[] a, double[] b, double[] r, int x, int y, int k);

	/**
	 * Compares the matrices and returns if they are equal.
	 * @param m
	 * @param diff e
	 * @return
	 */
	public boolean equals(Matrix m, double diff){
		if(this.height != m.height || this.width != m.width){ return false; }
		for(int y = 0; y < height; ++y){
			int index = y * width;
			for(int x = 0; x < width; ++x, ++index){
				if(Math.abs(this.content[index] - m.content[index]) > diff){ return false; }
			}
		}
		return true;
	}

	/**
	 * Compares the matrices and returns if they are equal.
	 * @param m
	 * @return
	 */
	public boolean equals(Matrix m){
		return this.equals(m, 0.000000000001);
	}

	/**
	 * Returns the Matrix to the power of given parameter k.
	 * A.height=A.width is required otherwise an IllegalArgumentException is thrown.
	 * @param k
	 * @return
	 */
	public Matrix power(int k){
		if(width != height || k < 0){ throw new IllegalArgumentException(); }
		if(k == 0){ return neutral(width); }
		Matrix result = this.clone();
		Stack<PowerType> s = new Stack<>();
		while(k > 1){
			if(k % 2 == 0){
				s.push(PowerType.Even);
				k /= 2;
			} else {
				s.push(PowerType.Odd);
				k = (k-1) / 2;
			}
		}
		while(!s.empty()){
			PowerType p = s.pop();
			if(p == PowerType.Even){
				result = result.multiply(result);
			} else if(p == PowerType.Odd){
				result = result.multiply(result).multiply(this);
			}
		}
		return result;
	}

	/**
	 * Calculates the power with a native call.
	 * @param k
	 * @return
	 */
	public Matrix powerNative(int k){
		if(width != height || k < 0){ throw new IllegalArgumentException(); }
		Matrix result = new Matrix(width, height, 0);
		powerC(this.content, result.content, width, k);
		return result;
	}

	private static native void powerC(double[] a,  double[] r, int dimension, int k);

	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		for(int y = 0; y < height; ++y){
			int index = y * width;
			for(int x = 0; x < width; ++x, ++index){
				sb.append(content[index]);
				sb.append('\t');
			}
			sb.append(System.lineSeparator());
		}
		return sb.toString();
	}

	@Override
	public Matrix clone() {
		Matrix m;
		try {
			m = (Matrix)super.clone();
		} catch (CloneNotSupportedException e) {
			throw new IllegalStateException();
		}
		m.content = m.content.clone(); //Deep copy
		return m;
	}

	public int getWidth() {
		return width;
	}

	public void setWidth(int width) {
		this.width = width;
	}

	public int getHeight() {
		return height;
	}

	public void setHeight(int height) {
		this.height = height;
	}

	public double[] getContent() {
		return content;
	}

	public void setContent(double[] content) {
		this.content = content;
	}

	private static enum PowerType{ Even, Odd }
}
