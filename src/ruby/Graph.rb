require 'mathn'
require 'matrix'
require 'Markov'

class Graph
	def initialize
		@nodes = Hash.new
	end

	def get_nodes
		@nodes.keys
	end	
			
	def add_node(node)
		@nodes[node] = Hash.new if not @nodes.has_key?(node)
	end
	
	def add_edge (n1, n2, w)
		@nodes[n1][n2] = w
	end
	
	def to_s
		res = ''
		@nodes.each_pair { |node1, value|
			value.each_pair { |node2, weight|
				res += "#{node1}, #{node2}, #{weight}\n" 
			}
		}
		res
	end	

	def all_paths(t, path=[])
		# returns all possible paths of length t
		if t == 0
			return [path]
		end

		res = []
		
		if path.length == 0
			@nodes.keys.each { |node|
				res += self.all_paths(t, [node])
			}
			return res
		end
		
		lastNode = path[-1]
		@nodes[lastNode].keys.each { |node|
			tmp = self.all_paths(t-1, path + [node])
			res += tmp
		}

		res
	end
	
	def path_prob(paths, init_prob)
		# calculate the probability for each path
		paths.map { |path|
			n1 = path[0]			
			prob = init_prob[n1]
			path[1,path.length-1].each { |n2|
				prob *= @nodes[n1][n2]
				n1 = n2
			}
			prob
		}
	end
	
	def hit_count(paths, node)
		# count the number of hits to a node
		# the last node visited on the path is not counted
		paths.map { |path|
			count = 0
			path[0,path.length-1].each { |n|
				count += 1 if n == node
			}
			count
		}
	end


	def calc_variance(i, t, w)
		# calculates the variance from the number of hits to node i for a path of length t
		
		paths = self.all_paths(t)
		probs = self.path_prob(paths, w)
		hits = self.hit_count(paths, i)

		expected_hits = t*w[i]
		
		d2 = hits.map { |hit|
			(hit - expected_hits) ** 2
		}
		
		sum = 0
		d2.zip(probs).each { |(hit,prob)|
			sum += hit*prob
		}

		sum
	end
	
	def to_adjacency_matrix

		n = @nodes.size
		res = (1..n).map { [0.0]*n }
		
		@nodes.each_pair { |n1, value|
			value.each_pair { |n2, prob|
				res[n1][n2] = prob * 1.0
			}
		}
		
		Matrix.rows(res)
	end

end


def print_all_variances(g)
	transition_matrix = g.to_adjacency_matrix
	markov = Markov.new(transition_matrix)

	t = 2

	var1 = g.get_nodes.map { |node|
		g.calc_variance(node, t, markov.stable_vector)
	}
	p var1

#	var2 = g.get_nodes.map { |node|
#		markov.calc_variance(node, t)
#	}
#	p var2

'''
	(0..100).each { |t|
		variances = g.get_nodes.map { |node|
			markov.calc_variance(node, t)
		}
		p variances
	}
'''
end


def lollipop
	g = Graph.new
'''
	(0..2).each { |i| g.add_node(i) }
	g.add_edge(0, 1, 1.0/2)
	g.add_edge(0, 2, 1.0/2)
	g.add_edge(1, 0, 1.0/2)
	g.add_edge(1, 2, 1.0/2)
	g.add_edge(2, 0, 1.0/2)
	g.add_edge(2, 1, 1.0/2)
'''

	(0..3).each { |i| g.add_node(i) }
	
	g.add_edge(0, 1, 1.0/2)
	g.add_edge(0, 2, 1.0/2)	
	g.add_edge(1, 0, 1.0/2)
	g.add_edge(1, 2, 1.0/2)
	g.add_edge(2, 0, 1.0/3)
	g.add_edge(2, 1, 1.0/3)
	g.add_edge(2, 3, 1.0/3)
	g.add_edge(3, 2, 1.0)

	print_all_variances(g)
end


if __FILE__ == $0
	
	lollipop
	
end

