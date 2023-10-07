if [ $# -ne 2 ]; then
    echo "Need a string to change from and to"
    return
fi

echo "Changing \""$1"\" to \""$2"\""

sed -i "s/$1/$2/g" tutorial/pages/*.md
