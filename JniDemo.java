class JniDemo{
    // native method
    private native void print();
    private native String getLine(String prompt);
    private native int sumArray(int[] array);
    private static native int[][] initInt2DArray(int size);

    public static void main(String args[]) {
        JniDemo jniDemo = new JniDemo();

        // no parameter
        jniDemo.print();

        // handle string
        /* String input = jniDemo.getLine("Type a line: ");
        System.out.println("User typed: " + input); */

        // primiary arrary
        int arr[] = new int[10];
        for (int i = 0; i < 10; i++) {
            arr[i] = i;
        }
        int sum = jniDemo.sumArray(arr);
        System.out.println("sum = " + sum);

        // arrays of object
        int[][] i2arr = initInt2DArray(3);
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                System.out.print(" " + i2arr[i][j]);
            }
            System.out.println();
        }
    }

    static {
        System.loadLibrary("JniDemo");
    }
}
