# For autocompiling qm-files.
#qthelp://org.qt-project.qmake.5120/qmake/qmake-variable-reference.html
CONFIG *= lrelease embed_translations
QM_FILES_RESOURCE_PREFIX = Translations
QM_FILES_INSTALL_PATH = $$OUT_PWD/Translations
TRANSLATIONS = \
    $$PWD/app_zh_CN.ts \
    $$PWD/app_zh_TW.ts 
