for f in *.h; do
    mv -- "$f" "${f%.h}.hpp"
done