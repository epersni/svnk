#!/usr/bin/python

env = Environment(
  CCFLAGS=[
    '--std=c++98',
    '-g',
    '-Wall'
  ],
  CPPDEFINES={'VERSION' : "1.0"},
  SCONS_CXX_STANDARD='c++98',
)

source_files = [
    'main.cpp',
    'view/Frame.cpp',
    'view/FrameManager.cpp',
    'view/ListFrame.cpp',
    'view/ScrollableTextFrame.cpp',
    'view/TestItemProvider.cpp',
    'svn/CommandLineOperator.cpp',
    'RevisionViewController.cpp',
    'ChangedFilesViewController.cpp',
    'svn/XmlElement.cpp',
    'svn/RepositoryInfo.cpp',
    'svn/Revision.cpp',
    'svn/Change.cpp',
]

build = env.Program(
  target = 'svnk',
  source = source_files,
  LIBS = [
    'boost_program_options',
    'ncurses',
    'xerces-c',
  ],
)

Default(build)

