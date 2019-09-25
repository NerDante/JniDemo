#include <stdio.h>
#include <string.h>
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

JNIEXPORT void JNICALL Java_JniDemo_nativeMethod(JNIEnv *env, jobject obj)
{
    jclass cls = (*env)->GetObjectClass(env, obj);
    jmethodID mid = (*env)->GetMethodID(env, cls, "callback", "()V");
    if(mid == NULL)
    {
        return; // method not found
    }

    printf("In C:\n");
    (*env)->CallVoidMethod(env, obj, mid);

    mid = (*env)->GetStaticMethodID(env, cls, "callback_static", "()V");
    if(mid == NULL)
    {
        return;
    }

    (*env)->CallStaticVoidMethod(env, cls, mid);
}

// example for return String[] in java
JNIEXPORT jobjectArray JNICALL Java_JniDemo_getFileList(JNIEnv *env, jobject obj)
{
    jobjectArray result;
    jclass cls = (*env)->GetObjectClass(env, obj);
    jclass str_cls = (*env)->FindClass(env, "java/lang/String");
    char *list[5] = {"hallo.mp3", "lydia.mp3", "my love.mp3", "go", "中文测试"}; // fake data

    result = (*env)->NewObjectArray(env, 5, str_cls, NULL); // 注意：此处的jclass 是 str_cls, 而非 cls
    if(result == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < 5; i++)
    {
        (*env)->SetObjectArrayElement(env, result, i, (*env)->NewStringUTF(env, list[i]));
    }

    return result;
}

JNIEXPORT jobject JNICALL Java_JniDemo_handleUserObject(JNIEnv *env, jobject demo, jobject info)
{
    jclass clsIn, clsOut;
    
    clsIn = (*env)->GetObjectClass(env, info);
    if(clsIn == NULL)
    {
        printf("get object class failed\n");
        return NULL;
    }

    //从Java层传递对象到native
    {
        jboolean iscopy;
        jfieldID intId = (*env)->GetFieldID(env, clsIn, "index", "I");
        jfieldID strId = (*env)->GetFieldID(env, clsIn, "name", "Ljava/lang/String;");

        jint index = (*env)->GetIntField(env, info, intId);
        printf("In index = %d\n", index);

        jstring name = (*env)->GetObjectField(env, info, strId);
        const char *locStr = (*env)->GetStringUTFChars(env, name, &iscopy);
        printf("In name = %s\n", locStr);

        (*env)->ReleaseStringUTFChars(env, name, locStr);
    }

    //获取类引用
    clsOut = (*env)->FindClass(env, "TestInfo");
    //获得该类的构造函数
    jmethodID mid = (*env)->GetMethodID(env, clsOut, "<init>", "(ILjava/lang/String;)V");
    jstring s = (*env)->NewStringUTF(env, "c constructed");
    //构造对象，并且传递参数（即 88， str)
    return (*env)->NewObject(env, clsOut, mid, 88, s);
}
