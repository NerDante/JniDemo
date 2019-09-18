#include <stdio.h>
#include "JniDemo.h"
#include "jni.h"

JNIEXPORT void JNICALL Java_JniDemo_print(JNIEnv *env, jobject obj)
{
    printf("hello JniDemo\n");
}

JNIEXPORT jstring JNICALL Java_JniDemo_getLine(JNIEnv *env, jobject obj, jstring prompt)
{
   char buf[128];
   const jbyte *str;

   str = (*env)->GetStringUTFChars(env, prompt,NULL);
   if (str == NULL) {
       return NULL;
   }

   printf("%s\n", str);
   (*env)->ReleaseStringUTFChars(env,prompt,str);

   //assume user does not type more than 127 characters
   scanf("%s", buf);
   return (*env)->NewStringUTF(env, buf);
}

JNIEXPORT jint JNICALL Java_JniDemo_sumArray(JNIEnv *env, jobject obj, jintArray arr)
{
    jint len, i, sum = 0;
    jint *carr;

    len = (*env)->GetArrayLength(env, arr);
    printf("len = %d\n", len);

    carr = (*env)->GetIntArrayElements(env, arr, NULL);
    if(carr == NULL)
    {
        return 0; // exception occurred
    }

    for(i= 0; i < len; i++)
    {
        sum += carr[i];
    }
    
    (*env)->ReleaseIntArrayElements(env, arr, carr, 0);

    return sum;
}

JNIEXPORT jobjectArray JNICALL Java_JniDemo_initInt2DArray(JNIEnv *env, jclass cls, jint size)
{
    jobjectArray result;
    int i;
    jclass intArrCls;

    intArrCls = (*env)->FindClass(env, "[I");
    if(intArrCls == NULL)
    {
        return NULL;
    }

    result = (*env)->NewObjectArray(env, size, intArrCls, NULL);
    if(result == NULL)
    {
        return NULL;
    }

    for (i = 0; i < size; i++)
    {
        jint tmp[256]; // make sure it is large enough
        int j;
        jintArray iarr = (*env)->NewIntArray(env, size);
        if(iarr == NULL)
        {
            return NULL;
        }

        for(j = 0; j < size; j++)
        {
            tmp[j] = i + j;
        }

        (*env)->SetIntArrayRegion(env, iarr, 0, size, tmp);
        (*env)->SetObjectArrayElement(env, result, i, iarr);

        (*env)->DeleteLocalRef(env, iarr);
    }

    return result;
}
