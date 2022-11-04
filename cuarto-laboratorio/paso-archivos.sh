# @$1 path al archivo
for i in 1 2 3
do
  echo "Pasando el archivo $1 hacia Working Node $i"
  scp $1 wn$i:$1
done
