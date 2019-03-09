TARGET = Tasks
TEMPLATE = lib

DESTDIR = $$OUT_PWD/../bin
#DLLDESTDIR = $$DESTDIR

include(Tasks.pri)

include(../pri/Common.pri)

#VERSION=1.0.0
#RC_FILE = Tasks.rc

TasksList.files = ../etc/*.xml
TasksList.path = $$PREFIX/etc/xml
TasksList.CONFIG += no_check_exist

sink.files = Resource/sink/*
sink.path = $$PREFIX/Resource
sink.CONFIG += no_check_exist

target.path = $$PREFIX/bin
INSTALLS += TasksList sink target IncludeFiles
IncludeFiles.path = $$PREFIX/include
IncludeFiles.files = $$HEADERS
INSTALLS += IncludeFiles
