# My Templates for Competitive Programming
## Contents
```
├── basic 
│   ├── heap.cc 
│   └── sortings.cc
├── bit_span.cc
├── bitwise.cc
├── dp
│   ├── convex_hull_optimization.cc
│   ├── longest_arithmetic_series.cc
│   ├── quadrangle_optimization.cc
│   └── single_cycle_tree.cc
├── ds
│   ├── dsu.cc # union-find set
│   ├── dsu_pst.cc # persistent union-find set, implemented by persistent segment tree
│   ├── dsu_rope.cc # persistent union-find set, implemented by rope, slower
│   ├── exact_cover.cc # X problem and dancing links
│   ├── fenwick_tree # binary indexed trees
│   │   ├── fenwick2d.cc 
│   │   ├── fenwick.cc
│   │   ├── range_fenwick2d.cc 
│   │   ├── range_fenwick.cc
│   │   ├── range_single_fenwick2d.cc
│   │   └── range_single_fenwick.cc
│   ├── implicit_treap.cc # treap with implicit key
│   ├── matrix.cc # multiplication and power of matrix
│   ├── persistent_array.cc 
│   ├── ptreap.cc # persistent treap
│   ├── rope.cc # demo code for rope data structure
│   ├── segment_tree
│   │   ├── range_cover.cc
│   │   ├── range_pst.cc # persistent segment tree, with range modification
│   │   ├── range_st.cc
│   │   ├── single_pst.cc # persistent segment tree, single point modification
│   │   └── single_st.cc
│   ├── sparse_table.cc
│   └── treap.cc
├── flows
│   ├── max_flow.cc
│   └── min_cost_flow.cc
├── geometry.cc
├── graphs
│   ├── bcc_edge.cc # binary connected component, by edge
│   ├── bcc_vertex.cc # binary connected component, by vertex
│   ├── dominator_tree.cc # "dominator" tree of directed graph
│   ├── maximum_clique.cc # can also solve maximum-independent set
│   ├── scc.cc # strong connected component of directed graph
│   └── topo_sort.cc # topo sort of (un)directed graph
├── inverse_pair.cc # number of inverse pairs, by merge sort
├── matchings
│   └── hungary.cc # hungary matching of bipartite graph
├── math
│   ├── combine_big.cc # combination for large N by Lucas
│   ├── combine_log.cc # combination with O(N) preprocessing and O(log N) computation
│   ├── combine_small.cc # combination with O(N^2) preprocessing and O(1) computation
│   ├── crt.cc # Chinese remainder theorem solving congruence equation
│   ├── d_func.cc # calculate the number of divisors of a number by O(sqrt(N))
│   ├── euler_sieve.cc # O(N) sieve for prime numbers, euler function and lowest prime divisor
│   ├── exgcd.cc # extended gcd, and solution for ax + by = c
│   ├── fft.cc # normal fft for floating numbers
│   ├── fft_mod.cc # fft for arbitrary moduler
│   ├── inv_n.cc # moduler inverse precaculation O(N)
│   ├── josephus.cc # josephus cycle problem
│   ├── kth_fib.cc # find k-th fibonacci number by O(log N)
│   ├── lagrange.cc # lagrange sieve O(N^2)
│   ├── mu_n.cc # O(N) sieve for mu array
│   ├── newton_sqrt_root.cc # newton's method for calculation sqrt
│   ├── ntt.cc # number theory transform (moduler fft)
│   ├── number_divide.cc # the number of ways to divide a positive integer number to sum of smaller numbers
│   ├── phi_func.cc # calculate euler function by O(sqrt(N))
│   ├── phi_n.cc # precaculate euler function array by O(N)
│   ├── polynomial_inv.cc # moduler inverse of polynomial
│   ├── primality.cc # primality check, miller-robin and pollard-rho
│   ├── prime_n.cc # O(N) sieve for prime numbers
│   ├── s_func.cc # calculate sum of divisors of a number by O(sqrt(N))
│   └── young_tableaus.cc
├── partial_order.cc # divide-and-conquer solving partial order problems
├── strings
│   ├── aho_corasick.cc # aho-corasick automaton
│   ├── bkdr_hash.cc
│   ├── expression.cc # math equation evaluation
│   ├── hash_1.cc # hashing a string with one prime moduler
│   ├── hash_2.cc # hashing a string with two prime modulers
│   ├── manacher.cc # manacher palindrome O(N)
│   ├── p_function.cc # prefix function, kmp
│   ├── p_trie.cc # persistent trie
│   ├── sa.cc # suffix array
│   ├── suffix_automaton.cc
│   ├── trie.cc
│   ├── weight_hash.cc # hashing a multiset by weight
│   └── z_function.cc # suffix function (extended kmp)
└── trees
    ├── centroid.cc # centroid decomposition (divide and conquer)
    └── hld.cc # heavy-light decomposition
```
