project('main', 'cpp', version : '0.1', default_options : ['warning_level=3', 'cpp_std=c++26'])
ftxui = dependency('ftxui')
exe = executable('tst', ['main.cpp', 'elements.cpp', 'logic.cpp', 'misc.cpp'], install : true, dependencies : ftxui)
test('basic', exe)
