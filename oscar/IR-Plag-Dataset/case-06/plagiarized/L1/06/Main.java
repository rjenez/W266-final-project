/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author E3AFED0047B08059D0FADA10F400C1E5
 */
public class Main {

    public static void main(String[] args) {
        java.util.Scanner input = new java.util.Scanner(System.in);
        int[] num = new int[10];
        for (int i = 0; i < 10; i++) {
            // Input angka pada bagian ini
            System.out.print(
                    "Read a number: ");
            num[i] = input.nextInt();
        }
        // Menampilkan array
        for (int i = 9; i >= 0; i--) {
            System.out.println(num[i]);
        }
    }
}
