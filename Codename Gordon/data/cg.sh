#!/bin/sh

if [ "$(uname -s)" = "Darwin" ]; then
  os="mac"
else
  os="linux"
fi

cd data && ./flashplayer_$os cg.swf

