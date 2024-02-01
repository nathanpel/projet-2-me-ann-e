#!/bin/bash
if [ -e 'temp' ] ;	then
  echo -n `rm -r temp && mkdir temp`
else
  echo -n `mkdir temp`
fi
if [ -e 'image' ] ;	then
  echo -n `rm -r image && mkdir image`
else
  echo -n `mkdir image`
fi

if [ 'data.csv' == $1 ] ; then
  echo `clear`
  for i in $* ; do
    if [ '-h' == $i ] ; then
        echo "L'argument -h ne marche pas, les options disponibles sont:
      option -d1 : conducteurs avec le plus de trajets
      option -d2 : conducteurs et la plus grande distance
      option -l  : les 10 trajets les plus longs 
      option -t  : les 10 villes les plus traversées
      option -s  : statistiques sur les étapes"
      echo -e
      exit
    fi
  done
  for i in $* ; do
      if [ '-d1' == $i ] ; then
        temp_depart=$(date +%s)
        `awk -F";" '$2 == 1 {p=$6} {if($6==p) print ";"$6}' data.csv | sort -r -t';' -k2 | uniq -c > temp/d11.csv`
        `sort -r -n -t';' -k1 temp/d11.csv | head -10 > temp/d1.csv`
        `gnuplot 'd1.gnu'&&convert -rotate 90 image/d11.png image/d1.png&&rm image/d11.png`
        temp_fin=$(date +%s)
        echo "Le temps d'execution est de : "`expr $temp_fin - $temp_depart`" secondes"
        echo -e
      elif [ '-d2' == $i ] ; then
        temp_depart=$(date +%s)
        `awk -F";" '{tab[$6]+=$5} END {for (i in tab) print tab[i]";"i}' data.csv | tail +2 | sort -r -t';' -n -k1 | head -10 > temp/d2.csv`
        `gnuplot 'd2.gnu'&&convert -rotate 90 image/d22.png image/d2.png&&rm image/d22.png`
        temp_fin=$(date +%s)
        echo "Le temps d'execution est de : "`expr $temp_fin - $temp_depart`" secondes"
        echo -e
      elif [ '-l' == $i ] ; then
        temp_depart=$(date +%s)
        `awk -F";" '{tab[$1]+=$5} END {for (i in tab) print i";"tab[i]}' data.csv | sort -t';' -r -n -k2 | head -10 | sort -r -t';' -n -k1 > temp/l.csv`
        `gnuplot 'l.gnu'`
        temp_fin=$(date +%s)
        echo "Le temps d'execution est de : "`expr $temp_fin - $temp_depart`" secondes"
        echo -e
      elif [ '-t' == $i ] ; then
        temp_depart=$(date +%s)
        `gcc t.c -o -t`
        `./-t`
        `gnuplot 't.gnu'`
        temp_fin=$(date +%s)
        echo "Le temps d'execution est de : "`expr $temp_fin - $temp_depart`" secondes"
        echo -e
    fi
  done
else 
  echo "Le fichier data.csv doit être le premier argument"
fi
