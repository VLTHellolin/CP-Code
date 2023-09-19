import java.io.*;
import java.util.*;

public class Main {
    static Scanner in = new Scanner(System.in);
    static PrintWriter out = new PrintWriter(System.out);
    static int a, b, cnt;
    
    private static void gcd(int x, int y) {
        if(y == 0) {
            --cnt;
            return;
        }
        if(x / y < 2) {
            ++cnt;
            gcd(y, x % y);
        }
    }

    public static void main(String args[]) {
        a = in.nextInt();
        b = in.nextInt();
        while(a != 0 && b != 0) {
            cnt = 0;
            gcd(Math.max(a, b), Math.min(a, b));
            out.println((cnt % 2 == 1 ? "Ollie" : "Stan") + " wins");
            a = in.nextInt();
            b = in.nextInt();
        }
        in.close();
        out.close();
    }
}