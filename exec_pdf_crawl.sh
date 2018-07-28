#!/bin/bash

link=''
folder='.'
while getopts ":l:f:" opt; do
	case $opt in
		l)
			link=$OPTARG
			;;
		f)
			folder=$(readlink -f $OPTARG)
			;;
		\?)
			echo "Invalid option: -$OPTARG" >&2
			exit 1
			;;
		:)
			echo "Option -$OPTARG requires an argument." >&2
			exit 1
			;;
	esac
done

#enter working directory
cd $(dirname $(readlink -f $0))
overwrite_file=pdf_downloader/spiders/target.py

# setup the target link and folder
echo "TARGET_URL='$link'" > $overwrite_file 
echo "TARGET_DEST='$folder'" >> $overwrite_file

# perform the crawl
scrapy crawl first_spider -o $folder/items.json
