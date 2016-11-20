#!/bin/bash

# 	
#	Script que monta la base de datos pasándole el nombre como primer argumento del fichero sin .sql
#
#	Ejemplo: Si queremos montar la base de datos usando el fichero baseDeDatos.sql tendrá que existir
#			 la base de datos "baseDeDatos" e invocar este script de la siguiente manera
#
#					./mountBD.sh baseDeDatos		
#


echo Montando base de datos...

NAME=$1
FULLNAME=${NAME}.sql 


sudo cp $FULLNAME /usr/local/mysql/bin
echo Fichero copiado a /usr/local/mysql/bin...

cd /usr/local/mysql/bin
mysql -u root -p $NAME < $FULLNAME
echo Base de datos montada 
echo FIN