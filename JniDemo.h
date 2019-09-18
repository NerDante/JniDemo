/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class JniDemo */

#ifndef _Included_JniDemo
#define _Included_JniDemo
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     JniDemo
 * Method:    print
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_JniDemo_print
  (JNIEnv *, jobject);

/*
 * Class:     JniDemo
 * Method:    getLine
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_JniDemo_getLine
  (JNIEnv *, jobject, jstring);

/*
 * Class:     JniDemo
 * Method:    sumArray
 * Signature: ([I)I
 */
JNIEXPORT jint JNICALL Java_JniDemo_sumArray
  (JNIEnv *, jobject, jintArray);

/*
 * Class:     JniDemo
 * Method:    initInt2DArray
 * Signature: (I)[[I
 */
JNIEXPORT jobjectArray JNICALL Java_JniDemo_initInt2DArray
  (JNIEnv *, jclass, jint);

/*
 * Class:     JniDemo
 * Method:    accessFiled
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_JniDemo_accessFiled
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
