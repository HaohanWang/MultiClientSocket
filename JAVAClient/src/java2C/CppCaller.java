package java2C;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Platform;

public class CppCaller {
	// This is the standard, stable way of mapping, which supports extensive
    // customization and mapping of Java to native types.

    public interface CLibrary extends Library {
        CLibrary INSTANCE = (CLibrary)
            Native.loadLibrary((Platform.isWindows() ? "msvcrt" : "c"),
                               CLibrary.class);

        void printf(String format, Object... args);
    }

    public static void main(String[] args) {
        CLibrary.INSTANCE.printf("Hello, World\n");
        String [] input = {"abc", "456"};
        for (int i=0;i < input.length;i++) {
            CLibrary.INSTANCE.printf("Argument %d: %s\n", i, input[i]);
        }
    }
}
