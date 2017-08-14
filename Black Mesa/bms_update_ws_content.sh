#!/bin/sh

set -e

steamapps="$HOME/.steam/steam/steamapps"
wscontent="$steamapps/workshop/content/362890"
bms="$steamapps/common/Black Mesa/bms"

mkdir -p "$bms/workshop_content"

# delete old links and sound cache
rm -f "$bms/workshop_content"/*.vpk
rm -f "$bms/workshop_content"/*.vpk.sound.cache

# create new links
find "$wscontent"/* -type f -name *.vpk -exec ln -s -v '{}' "$bms/workshop_content/" \;

set +e

# add this searchpath to gameinfo.txt
searchpath='game+mod bms/workshop_content/*'

if ! grep -e "$searchpath" "$bms"/gameinfo.txt >/dev/null; then
  # not elegant, but it works
  tr -d '\r' < "$bms"/gameinfo.txt | \
    sed -e 's|$|<EOL>|g' | \
    tr -d '\n' | \
    sed -e "s|<EOL>[ \t]*SearchPaths[ \t]*<EOL>[ \t]*{[ \t]*<EOL>|<EOL>\t\tSearchPaths<EOL>\t\t{<EOL>\t\t\t$searchpath<EOL><EOL>|" | \
    sed 's|<EOL>|\r\n|g' > "$bms"/gameinfo.txt.new

  if [ "$?" -eq 0 ]; then
    rm -f "$bms"/gameinfo.txt.old
    mv "$bms"/gameinfo.txt "$bms"/gameinfo.txt.old
    mv "$bms"/gameinfo.txt.new "$bms"/gameinfo.txt
  fi
fi

