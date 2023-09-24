import java.io.*;
import java.util.*;

public class Main {
    static Scanner in = new Scanner(System.in);
    static PrintWriter out = new PrintWriter(System.out);
    static int T, n, x, sum, mx;

    public static void main(String args[]) {
        for(T = in.nextInt(); T != 0; T--) {
            sum = mx = 0;
            for(n = in.nextInt(); n != 0; n--) {
                x = in.nextInt();
                sum += x;
                mx = Math.max(mx, x);
            }
            if((sum & 1) == 1 || 2 * mx > sum) out.println("T");
            else out.println("HL");
        }
        in.close();
        out.close();
    }
}