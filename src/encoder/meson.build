encoder = library('encoder', sources : ['HCNode.hpp', 'HCTree.cpp','HCTree.hpp'], dependencies: [input_dep, output_dep, bitStream_dep])
inc = include_directories('.')

encoder_dep = declare_dependency(include_directories : inc,
  link_with : encoder)
  