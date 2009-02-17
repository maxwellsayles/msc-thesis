
import no.uib.cipr.matrix.*;


public class Markov
{
	
	private Matrix p;
	
	
	private Matrix pow (Matrix A, int e)
	{
		Matrix r = DenseMatrix.
		return null;
	}
	
	public Markov (Matrix p)
	{
		this.p = p;
	}
	
	public static double pow (double b, int e)
	{
		double r = 1;
		
		while (e > 0)
		{
			if ((e & 1) == 1)
			{
				r *= b;
			}
			e = e >> 1;
			b *= b;
		}
		
		return r;
	}
}


