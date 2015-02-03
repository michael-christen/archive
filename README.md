# [PDF Downloader](https://github.com/karatekid/pdf-downloader)

This is a pdf scraper built using python's
[Scrapy](http://scrapy.org/) library.
[exec_pdf_crawl.sh](exec_pdf_crawl.sh) is used to take in 2 command
line arguments:
* -l dictates which link to scrape
* -f dictates where to save the resultant files

## Future work:
* progress bar / display how many you have
* don't save files you already have
  * nice if could check file hash for changes
