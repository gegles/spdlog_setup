#!/usr/bin/env sh

set -e

CLANG_FORMAT=mikedld/clang-format

files=$(find \
        include \
        test \
        test_package \
        -type f \( \
                  -iname \*.cpp -o \
                  -iname \*.hpp -o \
                  -iname \*.ipp \
                \) \
       )

if [ -x "$(command -v clang-format)" ] ; then
    clang-format --version
    clang-format -style=file -i ${files}
elif [ -x "$(command -v docker)" ] ; then
    docker run -it --rm ${CLANG_FORMAT} --version
    docker run -it --rm -v "$(pwd)":/workdir -w /workdir  ${CLANG_FORMAT} -style=file -i ${files}
else
    echo "clang-format or docker needed to reformat"
fi

set +e
