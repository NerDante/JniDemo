class JniDemo{
    // native method
    private native void print();
    private native String getLine(String prompt);

    public static void main(String args[]) {
        JniDemo jniDemo = new JniDemo();

        // no parameter
        jniDemo.print();

        // handle string
        String input = jniDemo.getLine("Type a line: ");
        System.out.println("User typed: " + input);
    }

    static {
        System.loadLibrary("JniDemo");
    }
}
