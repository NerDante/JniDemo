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


JNIEXPORT void JNICALL Java_JniDemo_accessFiled(JNIEnv *env, jobject obj)
{
    jfieldID fid_s, fid_si; // store the field ID
    jstring jstr;
    const char *str;
    jint si;

    // get a reference to obj's class
    jclass cls = (*env)->GetObjectClass(env, obj);
    printf("In c:\n");

    // look for thefield in cls
    fid_s = (*env)->GetFieldID(env, cls, "s", "Ljava/lang/String;"); // "Ljava/lang/String" is JNI field descriptors
    if(fid_s == NULL)
    {
        return;
    }
    fid_si = (*env)->GetStaticFieldID(env, cls, "si", "I"); // "Ljava/lang/String" is JNI field descriptors
    if(fid_si == NULL)
    {
        return;
    }

    // read the field
    jstr = (*env)->GetObjectField(env, obj, fid_s);
    str = (*env)->GetStringUTFChars(env, jstr, NULL);
    if(str == NULL) {
        return;
    }
    si = (*env)->GetStaticIntField(env, cls, fid_si);
    
    printf("    jniDemo.s = \"%s\", si = %d\n", str, si);
    (*env)->ReleaseStringUTFChars(env, jstr, str);

    // create a new string and overwrite the instance field
    jstr = (*env)->NewStringUTF(env, "from c 123");
    if(jstr == NULL)
    {
        return;
    }
    (*env)->SetObjectField(env, obj, fid_s, jstr);

    (*env)->SetStaticIntField(env, cls, fid_si, 200);
}
