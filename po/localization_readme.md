Localization
============

To generate the `.pot` file, run this command:

    xgettext -C --qt --keyword=tr --add-comments=TRANSLATORS app.qml -p locale -o <pot_file>.pot

To create a new `.po` file, run this command in `locale` directory:

    msginit -i <pot_file>.pot -o <LANG>.po

To update existing `.po` file, run this command in `locale` directory:

    msgmerge -U <LANG>.po <pot_file>.pot

To build a `.po` file, run these commands in `locale` directory:

    mkdir -p <LANG>/LC_MESSAGES
    msgfmt <LANG>.po -o <LANG>/LC_MESSAGES/<pot_file>.mo