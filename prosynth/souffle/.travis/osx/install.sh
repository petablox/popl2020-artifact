#!/bin/bash

# Enable debugging and logging of shell operations
# that are executed.
set -e
set -x

# Install requirements of MAC OS X
brew install bison libtool mcpp libffi || echo "brew install failed"
brew link bison --force || echo "brew link bison failed"
brew link libffi --force || echo "brew link libffi failed"

export PATH="/usr/local/opt/bison/bin:$PATH"
export PKG_CONFIG_PATH=/usr/local/opt/libffi/lib/pkgconfig/

rm /Users/travis/Library/Logs/DiagnosticReports/* || true

set +e
set +x
