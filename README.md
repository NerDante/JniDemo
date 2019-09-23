
## 环境准备
- 安装jdk
- 配置环境变量，JAVA_HOME，将项目目录加入LD_LIBRARY_PATH

## 过程详解
下面以最简单的HelloWorld为例，介绍JNI的基本开发流程, JniDemo 开发使用流程与下面类似，但涉及更多的JNI知识.
1. 创建HelloWorld.java,内容如下
```java
class HelloWorld {
    private native void print();

    public static void main(String[] args) {
        new HelloWorld().print();
    }

    static {
        System.loadLibrary("HelloWorld");
    }
}
```
2. 编译生成class文件
```shell
javac  HelloWorld.java
```

3. 利用javah生成头文件
```shell
javah -jni HelloWorld
```

4. 创建本地c文件, 实现HelloWorld.h中的本地方法
```c
#include <stdio.h>
#include <jni.h>
#include "HelloWorld.h"

JNIEXPORT void JNICALL Java_HelloWorld_print
  (JNIEnv *env, jobject obj)
{
    printf("hello world!\n");
    return;
}
```

5. 编译运行
```shell
# linux 环境下用gcc编译生成动态库
gcc	-shared -I $(JAVA_HOME)/include -I $(JAVA_HOME)/include/linux HelloWorld.c -o libHelloWorld.so
# 运行
java HelloWorld
```
*result:*
> hello world!

## 参考资料
[Java Programming Tutorial Java Native Interface (JNI)](https://www3.ntu.edu.sg/home/ehchua/programming/java/JavaNativeInterface.html)
