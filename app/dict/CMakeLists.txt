# Searches for all qml and javascript files in the current directory
# to add them to the project, if you add new files in the directory
# rerun cmake to make sure they show up in the project tree
file(GLOB QML_JS_FILES_dict *.qml *.js)

# Make the files visible in qtcreator
add_custom_target(aesydict_QMlFiles_dict ALL SOURCES ${QML_JS_FILES_dict})

install(FILES ${QML_JS_FILES_dict} DESTINATION ${AESYDICT_DIR}/dict)
