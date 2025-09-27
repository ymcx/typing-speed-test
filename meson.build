project('typing-speed-test', 'cpp', default_options : ['cpp_std=c++26'])

ftxui_dep = dependency('ftxui', modules : [ 'ftxui::dom', 'ftxui::component' ])

src_files = files('src/elements.cpp', 'src/logic.cpp', 'src/main.cpp', 'src/misc.cpp')

executable('typing-speed-test', src_files, dependencies : [ftxui_dep])
