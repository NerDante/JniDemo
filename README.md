## 环境准备
- 安装jdk
- 配置环境变量，JAVA_HOME，将项目目录加入LD_LIBRARY_PATH

## 过程
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

4. 创建本地c文件
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

gcc	-shared -I $(JAVA_HOME)/include -I $(JAVA_HOME)/include/linux HelloWorld.c -o libHelloWorld.so
java HelloJava
```
result:
> hello world!
