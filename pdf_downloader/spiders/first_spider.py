# -*- coding: utf-8 -*-
#define list of urls, how to follow links, and parse contents of page
#to extract items
import scrapy
import urllib
import re
import target
import urlparse

from pdf_downloader.items import PdfDownloaderItem



parsed_url = urlparse.urlparse(target.TARGET_URL)
class FirstSpiderSpider(scrapy.Spider):
	name = "first_spider"
	allowed_domains = [parsed_url.netloc]
	start_urls = (
			target.TARGET_URL,
	)

	def parse(self, response):
		link_prefix = parsed_url.scheme + '://' + parsed_url.netloc
		for l in response.xpath('//a/@href').re('(.+\.pdf)'):
			item = PdfDownloaderItem()
			item['link'] =  link_prefix + l
			m = re.search('([^\/]+\.pdf)$',l)
			if m:
				item['name'] = m.group(1)
				item['local_location'] = target.TARGET_DEST+'/'+m.group(1)
				d = urllib.urlretrieve(item['link'],filename=item['local_location'])
				yield item
	pass
