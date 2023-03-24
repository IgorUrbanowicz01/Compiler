#!/bin/bash


for FILE in $(find test/ | grep ".imp")
do
	FILE_NAME="$( echo "$FILE" | cut -d'.' -f1 )"
	echo TEST FOR $FILE_NAME

    cat $FILE
	OUTPUT_FILE="$( echo $FILE_NAME ).out"
	
	./compiler $FILE $OUTPUT_FILE
	sudo ./maszyna_wirtualna/maszyna-wirtualna $OUTPUT_FILE

done