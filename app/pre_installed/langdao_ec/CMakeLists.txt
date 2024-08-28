
file(GLOB dict *.dict *.idx *.ifo)

# Make the files visible in qtcreator
add_custom_target(file_dict ALL SOURCES ${dict})

install(FILES ${dict} DESTINATION ${AESYDICT_DIR}/pre_installed/langdao_ec)
