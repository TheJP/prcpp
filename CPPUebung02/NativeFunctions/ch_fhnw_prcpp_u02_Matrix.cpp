#include "ch_fhnw_prcpp_u02_Matrix.h"
#include <memory>
#include <stack>

using namespace std;

void multiply(jdouble * a, jdouble * b, jdouble * r, jint width, jint height, jint k){
	for (jint y = 0; y < height; ++y){
		jint index = y * width;
		for (jint x = 0; x < width; ++x, ++index){
			jdouble total = 0.0;
			for (jint i = 0; i < k; ++i){
				total += a[i + (y*k)] * b[x + (i*width)];
			}
			r[index] = total;
		}
	}
}

JNIEXPORT void JNICALL Java_ch_fhnw_prcpp_u02_Matrix_multiplyC(JNIEnv * env, jclass c, jdoubleArray a, jdoubleArray b, jdoubleArray r, jint x, jint y, jint k){
	jboolean acopy, bcopy, rcopy;
	jdouble * pa = env->GetDoubleArrayElements(a, &acopy);
	jdouble * pb = env->GetDoubleArrayElements(b, &bcopy);
	jdouble * pr = env->GetDoubleArrayElements(r, &rcopy);
	multiply(pa, pb, pr, x, y, k);
	/*
	//Debug code
	cout << "c++ r: " << endl;
	for (int i = 0; i < x*y; ++i){ cout << pr[i] << " "; }
	cout << endl;
	*/
	if (acopy == JNI_TRUE){ env->ReleaseDoubleArrayElements(a, pa, JNI_ABORT); }
	if (bcopy == JNI_TRUE){ env->ReleaseDoubleArrayElements(b, pb, JNI_ABORT); }
	if (rcopy == JNI_TRUE){ env->ReleaseDoubleArrayElements(r, pr, 0); }
}

JNIEXPORT void JNICALL Java_ch_fhnw_prcpp_u02_Matrix_powerC(JNIEnv * env, jclass c, jdoubleArray a, jdoubleArray r, jint dimension, jint k){
	jboolean acopy, rcopy;
	jdouble * pa = env->GetDoubleArrayElements(a, &acopy);
	jdouble * pr = env->GetDoubleArrayElements(r, &rcopy);
	if (k == 0){
		//Neutral matrix
		for (int y = 0; y < dimension; ++y){
			int index = y * dimension;
			for (int x = 0; x < dimension; ++x, ++index){
				pr[index] = (x == y ? 1.0 : 0.0);
			}
		}
	}
	else {
		memcpy(pr, pa, (dimension*dimension)*sizeof(jdouble));
		stack<bool> s;
		while (k > 1){
			if (k % 2 == 0){
				s.push(true);
				k /= 2;
			} else {
				s.push(false);
				k = (k - 1) / 2;
			}
		}
		bool even;
		jdouble * ptmp = new jdouble[dimension*dimension];
		while (!s.empty())
		{
			even = s.top();
			s.pop();
			multiply(pr, pr, ptmp, dimension, dimension, dimension);
			swap(pr, ptmp);
			if (!even){
				multiply(pr, pa, ptmp, dimension, dimension, dimension);
				swap(pr, ptmp);
			}
		}
	}
	if (acopy == JNI_TRUE){ env->ReleaseDoubleArrayElements(a, pa, JNI_ABORT); }
	env->ReleaseDoubleArrayElements(r, pr, 0);
}
