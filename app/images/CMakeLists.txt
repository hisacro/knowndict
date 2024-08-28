# Searches for all image files in the current directory
# to add them to the project, if you add new files in the directory
# rerun cmake to make sure they show up in the project tree
file(GLOB IMAGE_FILES *.jpg *.png *.svg)

# Make the files visible in qtcreator
add_custom_target(aesydict_IMAGE_FILES ALL SOURCES ${IMAGE_FILES})

install(FILES ${IMAGE_FILES} DESTINATION ${AESYDICT_DIR}/images)


