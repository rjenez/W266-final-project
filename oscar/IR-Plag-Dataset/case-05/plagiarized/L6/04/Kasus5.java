/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author C166AB8FBBBE55174E16A67530426A8A 19011F43894F06E2BA0CA74061427469
 */
public class Kasus5 {
    
    public static void reverse(int number) {
        if(number>0) {
            System.out.print(number%10);
            reverse(number/=10);
        }
    }
    
    public static void main(String[] args) {
        System.out.print("Enter an integer: ");
        java.util.Scanner input = new java.util.Scanner(System.in);
        int number = input.nextInt();
        
        reverse(number);
        System.out.println("");
    }
}
