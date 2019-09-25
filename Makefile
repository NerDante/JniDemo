
build:
	javac TestInfo.java
	javac JniDemo.java
	gcc -shared -I $(JAVA_HOME)/include -I $(JAVA_HOME)/include/linux JniDemo.c -o libJniDemo.so

clean:
	rm -f *.class *.so
