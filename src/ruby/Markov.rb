require 'mathn'
require 'matrix'

class Markov

	attr_reader :transition_matrix, :stable_matrix, :stable_vector

	def initialize(transition_matrix)
		@transition_matrix = transition_matrix
		
		@stable_matrix = @transition_matrix ** 10000
		
		@stable_vector = []
		for i in (0..@stable_matrix.column_size-1)
			@stable_vector << @stable_matrix[0,i]
		end
	end

	def calc_variance(i, t)
		# calculate the variance between the number of stops at i in a walk of length t
		sum = 0
		prob_i = @stable_vector[i]
		for u in (0..(t-1))
			pu = @transition_matrix ** u
			sum +=  2.0*(t-u)*(pu[i,i] - prob_i) - t*(1-prob_i)
		end
		return (sum * prob_i)
	end

end


if __FILE__ == $0

	p = Matrix[[0, 0.5, 0.5, 0], [0.5, 0, 0.5, 0], [1.0/3, 1.0/3, 0, 1.0/3], [0, 0, 1, 0]]
	w = [1.0/4, 1.0/4, 3.0/8, 1.0/8]

	chain = Markov.new(p,w)

	print chain.calc_variance(2,2), "\n"

end

