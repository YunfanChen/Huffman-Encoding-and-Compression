subdir('bitStream/input')
subdir('bitStream/output')
subdir('bitStream')
subdir('encoder')

# TODO: Define autocomplete_exe to output executable file named 
#       autocomplete.cpp.executable


compress_exe = executable('compress.cpp.executable', 
    sources: ['compress.cpp'],
    dependencies : [encoder_dep, bitStream_dep, input_dep, output_dep],
    install : true)

uncompress_exe = executable('uncompress.cpp.executable', 
    sources: ['uncompress.cpp'],
    dependencies : [encoder_dep, bitStream_dep, input_dep, output_dep],
    install : true)