DIR=`dirname $0`
MAKEFILE=$DIR/build/Makefile
if [ ! -f $MAKEFILE ]; then
  sh $DIR/build.sh
fi
cd $DIR/build
make install
