# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = 9Meow

CONFIG += sailfishapp

SOURCES += src/9Meow.cpp \
    src/category.cpp \
    src/categorylist.cpp \
    src/categorymodel.cpp \
    src/apiclient.cpp \
    src/catimage.cpp \
    src/catimagelist.cpp \
    src/catimagemodel.cpp

DISTFILES += qml/9Meow.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    rpm/9Meow.changes.in \
    rpm/9Meow.changes.run.in \
    rpm/9Meow.spec \
    rpm/9Meow.yaml \
    translations/*.ts \
    9Meow.desktop \
    qml/delegates/DelegateCategory.qml \
    qml/pages/CategoryPage.qml

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/9Meow-de.ts

HEADERS += \
    src/category.h \
    src/categorylist.h \
    src/categorymodel.h \
    src/apiclient.h \
    src/catimage.h \
    src/catimagelist.h \
    src/catimagemodel.h
