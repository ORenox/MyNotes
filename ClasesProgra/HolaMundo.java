public class HolaMundo {
    public static void main(String[] args) throws InterruptedException{
        System.out.println("Hola mundo");
	int x = 4;

	for( int i = 0 ; i < 10 ; i++){
	 System.out.printf("El número es :%d%n",i+x);
	 Thread.sleep(500);
	}
    }
}
