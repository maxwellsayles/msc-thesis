
import no.uib.cipr.matrix.*;

public class MarkovTest {
	
	public static void main(String[] args) {
		
		Matrix p = new DenseMatrix (4, 4);
		p.set(0, 0, 0);
		p.set(0, 1, 0.5);
		p.set(0, 2, 0.5);
		p.set(0, 3, 0);
		
		p.set(1, 0, 0.5);
		p.set(1, 1, 0);
		p.set(1, 2, 0.5);
		p.set(1, 3, 0);
		
		p.set(2, 0, 1.0/3.0);
		p.set(2, 1, 1.0/3.0);
		p.set(2, 2, 0);
		p.set(2, 3, 1.0/3.0);
		
		p.set(3, 0, 0);
		p.set(3, 1, 0);
		p.set(3, 2, 1.0);
		p.set(3, 3, 0);
		
		
		System.out.println ((int) Markov.pow(3, 17));
	}
}
