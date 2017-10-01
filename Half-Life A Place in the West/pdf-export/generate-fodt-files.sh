#!/bin/bash
set -e

# generate OpenDocument files; use LibreOffice for manual PDF export

apw_root="$HOME/.local/share/Steam/steamapps/common/Half-Life A Place in the West"

TOP="$(cd "$(dirname "$0")" && pwd)"

function gen_fodt() {
  if [ -d "$1" ]; then
    local doc="$2"
    cat "$TOP/01-header.xml" "$TOP/02-settings.xml" "$TOP/03-body.xml" > $doc
    n=1
    for f in "$1"/*.jpg ; do
      sed "s,@NUMBER@,$n,g; s,@IMAGE@,$f,g" "$TOP/04-draw-template.xml" >> $doc
      n=$(($n + 1))
    done
    cat "$TOP/05-end.xml" >> $doc
  fi
}

function extract_asar() {
  if [ -e "$1" ]; then
    "$TOP/../asar-extract.sh" extract "$1" "$2" >/dev/null
  fi
}

mkdir output
cd output

echo "extract archives"
for n in 2 3 4; do
  extract_asar "$apw_root/issue$n/issue${n}.asar" issue_$n
done

echo "copy files"
dist="$apw_root/resources/app/dist/comic"
cp -r "$dist/issue_1" .
cp -r "$dist/issue_charnel" .
cp -r "$dist/issue_nal" .

echo "generate documents"
issues=$(ls -d issue_*/ | sed 's|issue_||g; s|/||g')
for i in $issues; do
  locales=$(ls -d issue_$i/*/ 2>/dev/null | cut -d'/' -f2)
  for l in $locales; do
    gen_fodt issue_$i/$l issue-${i}-${l,,}.fodt
  done
done

echo "done"

