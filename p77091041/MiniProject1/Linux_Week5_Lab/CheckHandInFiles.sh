#!/bin/bash
mainFolder=`pwd`/
missingListFile=./missing_list
wrongListFile=./wrong_list
zipFolder=./compressed_files/zip/
rarFolder=./compressed_files/rar/
tarFolder=./compressed_files/tar.gz/
unknownFolder=./compressed_files/unknown/

mkdir $zipFolder
mkdir $rarFolder
mkdir $tarFolder
mkdir $unknownFolder

#> $missingListFile

for id in `cat student_id`;
do
	fileName=`find ./compressed_files/ -maxdepth 1 -name "$id*"`
	#echo "$fileName"
	if test -z "$fileName";
	then
		echo "$id" >> "$missingListFile"
	else
		extension=`echo "$fileName" | cut -d '.' -f 3`
		#echo "$extension"
		#echo "$fileName"

		case $extension in
			"zip")
				mv $fileName $zipFolder
				;;
			"rar")
				mv $fileName $rarFolder
				;;
			"tar")
				mv $fileName $tarFolder
				;;
			*)
				mv $fileName $unknownFolder
				echo "$id" >> "$wrongListFile"
				;;
		esac
	fi
done

cd $zipFolder
unzip '*.zip'
cd $mainFolder

cd $rarFolder
for rarFile in *.rar; do unrar e "$rarFile"; done
cd $mainFolder

cd $tarFolder
for tarFile in *.tar.gz; do tar xvzf "$tarFile"; done
cd $mainFolder

cd ..
zip -r Linux_Week5_Lab.zip Linux_Week5_Lab

exec bash

