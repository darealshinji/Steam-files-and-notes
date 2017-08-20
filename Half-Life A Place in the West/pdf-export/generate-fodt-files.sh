#!/bin/bash

# Usage: gen_fodt path output
function gen_fodt()
{
  local doc="$2"
  cat "01-header.xml" "02-settings.xml" "03-body.xml" > $doc
  n=1
  for f in "$1"/*.jpg ; do
    sed "s,@NUMBER@,$n,g; s,@IMAGE@,$f,g" "04-draw-template.xml" >> $doc
    n=$(($n + 1))
  done
  cat "05-end.xml" >> $doc
}

# Use asar to extract .asar files:
# npm install asar
# ./node_modules/.bin/asar extract issue2.asar issue_2
# ./node_modules/.bin/asar extract issue3.asar issue_3

gen_fodt issue_1/EN issue-1-en.fodt
gen_fodt issue_1/RU issue-1-ru.fodt
gen_fodt issue_2/EN issue-2-en.fodt
gen_fodt issue_2/RU issue-2-ru.fodt
gen_fodt issue_3/EN issue-3-en.fodt
gen_fodt issue_3/RU issue-3-ru.fodt
gen_fodt issue_charnel/EN issue-charnel-en.fodt
gen_fodt issue_charnel/RU issue-charnel-ru.fodt

