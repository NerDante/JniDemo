
build:
	gcc -shared -I $(JAVA_HOME)/include -I $(JAVA_HOME)/include/linux JniDemo.c -o libJniDemo.so

clean:
	rm -f *.class *.so
