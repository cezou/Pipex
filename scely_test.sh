#!/bin/bash

make

VFF="valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes"
file_in="in"

if [ ! -e "$file_in" ]; then
	touch "$file_in"
	echo "$file_in was created"
fi

echo "	[1] : Fichier de sorti cree
	[2] : Pas d'environement
	[3] : Commande NULL et avec espace
	[4] : Commande errone
	[5] : Mauvais flag
	[6] : Aucune permission 
	[7] : Aucune permission et pas de flag
	[8] : urandom
	[9] : sans flag
Put a number :" 
read user_input

case "$user_input" in
	"1")
		echo "Fichier de sorti cree"
			$VFF ./pipex /dev/stdin "ls -l" "wc -l" out
			cat out
		;;
	"2")
       echo "Pas d'environement"
			$VFF env -i ./pipex /dev/stdin "ls -l" "wc -l" out
			cat out
		;;
	"3")
		echo "Commande NULL et avec espace"
			$VFF ./pipex /dev/stdin "" "  " out
			cat out
		;;
	"4")
		echo "Commande errone"
			$VFF ./pipex /dev/stdin "ls-la" "wc-l" out
			cat out
		;;
	"5")
		echo "Mauvais flag"
			$VFF ./pipex /dev/stdin "ls ws" "wc po" out
			cat out
		;;
	"6")
		echo "Aucune permission"
			chmod 000 out in
			$VFF ./pipex in "ls -l" "wc -l" out
			chmod 644 out in
		;;
	"7")
		echo "mauvais flag and aucune permission"
			chmod 000 out in
			$VFF ./pipex in "ls ws" "wc po" out
			chmod 644 out in
		;;
	"8")
		echo "urandom"
			$VFF ./pipex /dev/urandom "cat" "cat" /dev/stdout
		;;
	"9")
		echo "sans flag"
			$VFF ./pipex /dev/stdin "ls" "head -32" /dev/stdin
		;;

	*)
		echo "wrong numbers"


esac
