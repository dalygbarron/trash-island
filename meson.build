project(
  'Trash',
  'cpp',
  default_options: ['c_std=c11', 'cpp_std=c++20']
)

core_sources = [
  'src/Assets.cc',
  'src/State.cc',
  'src/Input2DState.cc',
  'src/Util.cc',
  'src/Chunk.cc',
  'src/World.cc',
  'src/Dude.cc'
]
test_sources = []

deps = [
  dependency('raylib', version: '>=4.0.0')
]
test_deps = [
  dependency('catch2', version: '>=2.13.0')
]

main = executable(
  'main',
  sources: core_sources + ['src/main.cc'],
  dependencies: deps,
  include_directories: 'lib'
)
tst = executable(
  'tst',
  sources: core_sources + test_sources,
  dependencies: deps + test_deps,
  include_directories: ['src', 'lib']
)

test('Unit Test', tst)

