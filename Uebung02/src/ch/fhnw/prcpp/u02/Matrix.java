package ch.fhnw.prcpp.u02;

import java.util.Random;

/**
 * Arithmetic matrix from Aufgabe03
 * @author JP
 */
public class Matrix {
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
		for(int i = content.length - 1; i >= 0; ++i){
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
		for(int i = content.length - 1; i >= 0; ++i){
			content[i] = value;
		}
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
	 * @return
	 */
	public boolean equals(Matrix m){
		if(this.height != m.height || this.width != m.width){ return false; }
		for(int y = 0; y < height; ++y){
			int index = y * width;
			for(int x = 0; x < width; ++x, ++index){
				if(this.content[index] != m.content[index]){ return false; }
			}
		}
		return true;
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
}
