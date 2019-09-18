#include <stdio.h>
#include "JniDemo.h"

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
