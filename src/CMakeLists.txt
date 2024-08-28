project(aesydict_src)

set(
    aesydict_SRCS
    main.cpp
    database.cpp
    dictindex.cpp
    dict.cpp
    dictinfo.cpp
    dictcenter.cpp
    dictdatablock.cpp
    youdaoapi.cpp
    )

add_executable(${EXEC}
    ${aesydict_SRCS}
    )

qt5_use_modules(${EXEC} Core Qml Quick Gui Sql Network)

install(TARGETS ${EXEC} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
