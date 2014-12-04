#include "ch_fhnw_prcpp_u02_Test.h"
#include <iostream>

using namespace std;

JNIEXPORT jint JNICALL Java_ch_fhnw_prcpp_u02_Test_increment(JNIEnv * env, jclass c, jint i){
	return ++i;
}

JNIEXPORT void JNICALL Java_ch_fhnw_prcpp_u02_Test_display(JNIEnv * env, jclass c){
	cout << "c++ hello world" << endl;
}
